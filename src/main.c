/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:31:27 by egatien           #+#    #+#             */
/*   Updated: 2025/05/27 17:44:23 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal;

void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	print_prompt_header(void)
{
	char	*cwd;
	char	*home;
	char	*relative;

	cwd = getcwd(NULL, 0);
	home = getenv("HOME");
	relative = NULL;
	if (cwd && home)
	{
		relative = cwd;
		if (!ft_strncmp(cwd, home, ft_strlen(home)))
			relative += ft_strlen(home);
		else
			relative = NULL;
	}
	printf("\033[1;92m╭─[\033[1;35m");
	if (cwd && home && relative)
		printf("~%s", relative);
	else if (cwd)
		printf("%s", cwd);
	else
		printf("unknown");
	printf("\033[1;92m]\033[0m\n");
	free(cwd);
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = 1;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	print_prompt_header();
	rl_redisplay();
}

char	**create_arguments(t_cmd *token)
{ //FONCTION TEMPORAIRE (SERA REMPLACEE PAR LA PARTIE PARSING)
	char	**args;
	char	*temp;
	char	*token_str;
	int		count;

	temp = ft_strdup(token->cmd);
	count = 0;
	token_str = ft_strtok(temp, " ");
	while (token_str && ++count)
		token_str = ft_strtok(NULL, " ");
	free(temp);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	temp = ft_strdup(token->cmd);
	token_str = ft_strtok(temp, " ");
	count = 0;
	while (token_str)
	{
		args[count++] = ft_strdup(token_str);
		token_str = ft_strtok(NULL, " ");
	}
	args[count] = NULL;
	free(temp);
	return (args);
} //FONCTION TEMPORAIRE (SERA REMPLACEE PAR LA PARTIE PARSING)

static void	execute_command(t_data *data)
{
//	printf("ENTRY EXECUTE_COMMAND\n");
	pid_t		pid;
	char		*cmd_path;
	extern char	**environ;
	int			status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!data->cmd->args || !data->cmd->args[0])
		{
			data->return_value = 1;
			exit(data->return_value);
		}
		cmd_path = find_command_path(data->cmd->args[0]);
		if (!cmd_path)
		{
			msg_error("\033[1;31mcommand not found: \033[0m");
			ft_putendl_fd(data->cmd->args[0], 2);
			ft_free_array(data->cmd->args);
			data->return_value = 127;
			exit(data->return_value);
		}
		execve(cmd_path, data->cmd->args, environ);
		free(cmd_path);
		if (errno == EACCES)
			data->return_value = 126;
		else if (errno == ENOENT)
			data->return_value = 127;
		else
			data->return_value = 1;
		perror("\033[1;31mError\033[0m");
		ft_free_array(data->cmd->args);
		data->return_value = 1;
		exit(data->return_value);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, sigint_handler);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			data->return_value = 130;
		}
		else if (WIFEXITED(status))
			data->return_value = WEXITSTATUS(status);
	}
}

void	select_builtin(t_data *data)
{
	if (!data->cmd || !data->cmd->cmd)
		msg_error("Invalid command.\n");
	if (ft_strncmp(data->cmd->cmd, "cd", 2) == 0)
		handle_cd(data);
	if (ft_strncmp(data->cmd->cmd, "echo", 4) == 0)
		handle_echo(data);
	if (ft_strncmp(data->cmd->cmd, "env", 3) == 0)
		handle_env(data);
	if (ft_strncmp(data->cmd->cmd, "export", 6) == 0)
		handle_export_var(data);
	if (ft_strncmp(data->cmd->cmd, "pwd", 3) == 0)
		handle_pwd(data);
	if (ft_strncmp(data->cmd->cmd, "unset", 5) == 0)
		handle_unset(data);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char		*input;
	t_data		*data;

//	Deplacer dans init_data()
//	int saved_stdin = dup(STDIN_FILENO);
//	int saved_stdout = dup(STDOUT_FILENO);

	g_signal = 0;
	disable_echoctl();
	data = init_data(envp);
	init_history(data);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		input = NULL;
		if (!g_signal)
		{
			print_prompt_header();
			input = readline("\033[1;92m╰─➤ \033[0m");
		}
		data->saved_stdin = dup(STDIN_FILENO);
		data->saved_stdout = dup(STDOUT_FILENO);
		g_signal = 0;
		if (ft_strcmp(input, "test") == 0)
		{
			// Exemple : cat << EOF
			data->cmd = init_cmd(data->cmd, "echo");
			data->cmd->has_redir = true;
			data->cmd->redir = malloc(sizeof(t_redir));
			data->cmd->redir->filename = strdup("EOF"); // Le délimiteur
			data->cmd->redir->type = HEREDOC;
			data->cmd->redir->next = NULL;
			handle_redir(data->cmd);
		}
		else
			data->cmd = init_cmd(data->cmd, input);
		// print_data(data);
		if (input && ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		// print_data(data);
		handle_exit(data, input);
		if (data->cmd->is_builtin
			&& ft_strncmp(data->cmd->cmd, "exit", 4) != 0)
			select_builtin(data);
		else
			execute_command(data);
		reset_fd(data);
		if (ft_strlen(input) > 0)
			add_to_history(data, input);
		print_data(data);
		print_data(data);
		free_tokens(data->cmd);
		free(input);
//		dup2(saved_stdin, STDIN_FILENO);
//		dup2(saved_stdout, STDOUT_FILENO);
//		close(saved_stdin);
//		close(saved_stdout);
	}
	free_history(data);		// !!!!! DATA EST FREE DANS LE EXIT ICI !!!!!
	return (0);
}

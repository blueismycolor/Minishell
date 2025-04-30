/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:38:12 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/04/26 17:33:55 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Verifier et ajouter la mise à jour du code d'erreur à renvoyer
** lors de l'execution de cette fonction.
*/

#include "../includes/minishell.h"

typedef enum e_type
{
	INPUT = 1,
	HEREDOC,
	TRUNC,
	APPEND,
	PIPE,
	CMD
}	e_type;

typedef struct s_redir
{
	char	*filename;
	e_type	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;
	bool			is_builtin;
	char			**args;
	int				nb_params;
	bool			has_redir;
	struct s_redir	*redir;
}	t_cmd;

typedef struct s_data
{
	struct s_cmd	*cmd;
	char			**env;
	char			*pwd;
	char			*old_pwd;
	int				return_value;
}	t_data;

/* Permet d'obtenir la taille de **env. */
int	get_env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/* Compare deux chaine de caracteres. */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

/* Print les variables d'environnement correctement. */
void	print_export(char **env)
{
	int		i;
	char	*equal;

	i = 0;
	while (env[i])
	{
		equal = ft_strchr(env[i], '=');
		if (equal)
			printf("export %.*s=\"%s\"n", (int)(equal - env[i]),
				env[i], equal + 1);
		else
			printf("export %s\n", env[i]);
		i++;
	}
}

/* Free un tableau deux dimensions. */
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

/* Cherche l'index en comparant le nom de celle recherchée avec celles dans env. */
int	var_index(char *var_name, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j]
			&& (env[i][j] == var_name[j])
			&& (var_name[j] != '\0' && var_name != '=')
			&& (env[i][j] != '\0' && env[i][j] != '='))
			j++;
		if ((env[i][j] == '\0' || env[i][j] == '=')
			&& (var_name[i] == '\0' || var_name[j] == '='))
			return (i);
	}
	return (-1);
}

/* Remplace les paramètres de la variable par les nouveaux. */
void	replace_var(char *new_var, int var_index, char **env)
{
	if (ft_strchr(new_var, '='))
		env[var_index] = ft_strdup(new_var);
	return ;
}

/* Tri les variables d'environnement pour les print dans l'ordre alphabetique comme bash. */
void	export_sorted_var(char **env)
{
	int		i;
	int		j;
	int		env_len;
	char	*to_swap;
	char	**tmp_env;

	i = 0;
	env_len = get_env_len(env);
	tmp_env = ft_memmove(tmp_env, env, env_len);
	while (tmp_env[i + 1])
	{
		j = i + 1;
		if (ft_strcmp(tmp_env[i], tmp_env[j]) != 0)
		{
			to_swap = tmp_env[j];
			tmp_env[j] = tmp_env[i];
			tmp_env[i] = to_swap;
			i = 0;
		}
		else
			i++;
	}
	print_export(tmp_env);
	free_tab(tmp_env);
}

/* Exporte toutes les variables d'environnement (ex : "export"). */
char	**add_var_env(char **env, char *new_var)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (get_env_len(env) + 1));
	if (!new_env)
		msg_error(ERR_MALLOC);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	free_tab(env);
	new_env[i] = ft_strdup(new_var);
	new_env[i++] = NULL;
	return (new_env);
}

/* Permet de gérer l'export des variables d'environnement. */
void	handle_export_var(char **args, char **env)
{
	int		i;
	char	*var_name;

	i = 0;
	if (args[2])
		msg_error("export: too many arguments.\n");
	if (!args[1])
	{
		export_sorted_var(env);
		print_export(env);
	}
	if (ft_strchr(args[1], '='))
	{
		var_name = ft_strnstr(args[i], args[0], ft_strlen(args[0]));
		replace_var(var_name, get_env_len(env), env);
		export_sorted_var(env);
		print_export(env);
	}
	else
	{
		var_name = ft_strnstr(args[i], args[0], ft_strlen(args[0]));
		add_var_env(env, var_name);
		export_sorted_var(env);
		print_export(env);
	}
}

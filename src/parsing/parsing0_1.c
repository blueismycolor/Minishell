/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:43:27 by aeudes            #+#    #+#             */
/*   Updated: 2025/05/28 14:42:35 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_input(char *input)
{
	if (!validate_input(input))
		return (ERROR);
	return (SUCCESS);
}

bool	validate_input(char *input)
{
	if (!check_pipe_syntax(input, 0))
		return false;
	if (check_quote_syntax(input, 0) == ERROR)
		return false;
	if (!check_redirection_syntax(input, 0, 0))
		return false;
	return true;
}

bool	check_pipe_syntax(char *input, int i)
{
	int		j;
	char	quote;

	quote = 0;
	i = skip_space(input, 0);
	if (input[i] == '|')
		return (ft_putstr_fd(ERR_SYN, STDERR_FILENO), false);
	while (input[i])
	{
		if((input[i] == '\'' || input[i] == '\"') && quote == 0)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		if (quote == 0 && input[i] =='|')
		{
			j = i + 1;
			j = skip_space(input, j);
			while (input[j] == '|' || input[j] == '\0')
				return (ft_putstr_fd(ERR_SYN, STDERR_FILENO), false);
		}
		i++;
	}
	return (true);
}

int	check_quote_syntax(char *input, int i)
{
	while (input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<')
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (!input[i])
				return (ft_putstr_fd(OPEN_SNG_QUOTE, STDERR_FILENO), ERROR);
		}
		else if (input[i] == '\"')
		{
			i++;
			while (input[i] && input[i] != '\"')
				i++;
			if (!input[i])
				return (ft_putstr_fd(OPEN_DBL_QUOTE, STDERR_FILENO), ERROR);
		}
		i++;
	}
	return (i);
}

bool	check_redirection_syntax(char *input, int i, int j)
{
	
	while (input[i])
	{
		if ((input[i] == '<' || input[i] == '>') &&
			!is_in_quotes(input, i) && !is_in_double_quotes(input, i))
		{
			if ((input[i] == '<' && input[i + 1] == '>') ||
				(input[i] == '>' && input[i + 1] == '<') ||
				(input[i] == '<' && input[i + 1] == '<' &&
					(input[i + 2] == '<' || input[i + 2] == '>')) ||
				(input[i] == '>' && input[i + 1] == '>' &&
					(input[i + 2] == '<' || input[i + 2] == '>')))
				return (ft_putstr_fd(ERR_SYN, STDERR_FILENO), false);
			if (input[i + 1] == '<' || input[i + 1] == '>')
				i++;
			j = i + 1;
			while (input[j] && input[j] == ' ')
				j++;
			if (!input[j] || input[j] == '<' ||
				input[j] == '>' || input[j] == '|')
				return (ft_putstr_fd(ERR_SYN, STDERR_FILENO), false);
		}
		i++;
	}
	return (true);
}

// bool	check_redirection_syntax(char *input, int i)
// {
// 	int	j;
// 	int	len;

// 	len = ft_strlen(input);
// 	while (input[i])
// 	{
// 		if ((input[i] == '<' || input[i] == '>') &&
// 			!is_in_quotes(input, i) && !is_in_double_quotes(input, i))
// 		{
// 			if (input[i + 1] && (input[i + 1] == '<' || input[i + 1] == '>'))
// 				i++;
// 			j = i + 1;
// 			while (input[j] && input[j] == ' ')
// 				j++;
// 			if (!input[j] || input[j] == '<' || input[j] == '>' || input[j] == '|')
// 				return (ft_putstr_fd(ERR_SYN, STDERR_FILENO), false);
// 		}
// 		i++;
// 	}
// 	return (true);
// }



/*
	eger  < veya > tirnak icinde ise redirection degil "x > y"
	eger  < veya > tirnak icinde degilse redirection.  x > y
	karsilikli olanlar hatali <> ><
	<<< <<> hatali
	>>> >>< hatali
	j redirectiondan hemen sonraki karaktere isaret eder,
	bu bir bosluk ise atlanir
	ornegin echo > gibi bir girdi var ise >den sonra gelen bosluklar burada gecerlidir.
	

	echo > ---> >'den sonra hicbir sey yok bu hata
	echo > ---> sadece bosluk var yine hicbir sey yok bu hata
	echo > > file bu hata
	echo > file.txt bu dogru
	cat < input.txt bu hata

*/


/*
	acilan tirnak kapanmamissa hata

	ic ice tirnak kullanimi hata
	
	tirnak acildiginda icerigi bir butun olarak kabul edilmeli split yapilmamali

	baslangic ve sondaki tirnaklar dogru bir sekilde eslesmeli
	
	tirnak icinde | < > vs var ise yok sayilmali (ancak "tirnak arasi $USER" var ise expansion)
	
*/


/* PIPE KONTROLU 

Başta pipe var mı diye kontrol ettik. Başta pipe kesinlikle hata.

Pipe sonda mı diye kontrol ettik. Sonunda pipe varsa hata.

Pipe arka arkaya var mı diye kontrol ettik. Arka arkaya || olursa hata.

Pipe tırnak içinde ise görmezden gelindi. (quote değişkeni ile)

Pipe'dan sonra boşluklar varsa geçildi, sonra kontrol yapıldı.

*/

/*
Si un pipe est au début :
	Ex : | ls → erreur
Si un pipe est à la fin :
	Ex : ls | → erreur
S’il y a un espace vide entre deux pipes :
	Ex : ls | | wc → erreur
S’il y a plusieurs pipes consécutifs :
	Ex : ls || wc → erreur (tu l’as déjà vérifié)
Les pipes à l’intérieur des guillemets doivent être ignorés.
	Ex : "echo | test" → valide, car le | est entre guillemets
*/
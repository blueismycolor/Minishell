/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:50:36 by egatien           #+#    #+#             */
/*   Updated: 2025/05/19 14:01:18 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_for_expansion(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

t_token	*get_token(char *str)
{
	t_token	*head; // tete de la liste au'on va renvoyer
	t_token	*node; // t_token temporaire qui sert a initialiser les noeuds de la liste
	char	**cut_str; // tableau de chaine de caracteres qui sert a recuperer les tokens dans str
	int		i; // variable pour defiler dans cut_str

	i = 0;
	head = NULL;
	cut_str = put_token_in_tabstr(str); // on recupere les tokens et on les place dans le tableau
	head = create_token(&head, cut_str[i], get_token_type(cut_str[i]), get_quote_type(cut_str[i])); // on cree le premier noeud de la liste
	head->has_expansion = check_for_expansion(head->str); // on regarde si le token contient une expansion
	node = head->next;
	free(cut_str[i]);
	i++;
	while (cut_str[i]) //boucle qui va creer la liste chainee
	{
		node = create_token(&head, cut_str[i], get_token_type(cut_str[i]), get_quote_type(cut_str[i]));
		node->has_expansion = check_for_expansion(node->str);
		node = node->next;
		free(cut_str[i]);
		i++;
	}
	free(cut_str);
	return (head);
}

t_cmd	*tcmd_init(char *input)
{
	t_token	*arg_tokens;
	t_cmd	*result;

	if (process_input(input) == -1)
		return (NULL);
	arg_tokens = get_token(input);
	give_expansion(arg_tokens); // partie qui va changer les variables d'env
	result = create_list_tcmd(arg_tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:09:01 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/25 18:12:08 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// PRINTS token_list (binary tree)
/*  if (!token)
		return ; */
void	print_token_list(t_token_tree *token)
{
	t_token_tree	*temp;

	temp = token;
	ft_printf("-----------------\n");
	while (temp)
	{
		ft_printf("Token: {%s}\n", temp->token_list);
		if (temp->type == PIPE)
			ft_printf("Type : PIPE\n");
		else
			ft_printf("Type : EXEC\n");
		if (temp->left == NULL)
			ft_printf("Left : %s\n", temp->left);
		else
			ft_printf("Left : {%s}\n", temp->left->token_list);
		if (temp->right == NULL)
			ft_printf("Right: %s\n", temp->right);
		else
			ft_printf("Right: {%s}\n", temp->right->token_list);
		if (temp->left)
			print_token_list(temp->left);
		temp = temp->right;
		ft_printf("-----------------\n");
	}
}

/* 
void	print_token_list_simple(t_token_tree *token)
{
	t_token_tree	*temp;

	if (!token)
		return ;
	temp = token;
	ft_printf("Tokens: [\"%s\"", temp->token_list);
	temp = temp->right;
	while (temp)
	{
		ft_printf(", \"%s\"", temp->token_list);
		temp = temp->right;
	}
	ft_printf("]\n");
} */

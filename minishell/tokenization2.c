/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:35:59 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/13 17:36:34 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_index	max_files_args(char **s_command)
{
	t_index	index;

	index.i = 0;
	index.j = 1;
	index.k = 0;
	while (s_command[index.j])
	{
		if (s_command[index.j] &&(!strcmp(s_command[index.j], "<") || !strcmp(s_command[index.j], ">") 
			|| !strcmp(s_command[index.j], "<<") || !strcmp(s_command[index.j], ">>")))
		{
			index.i++;
			index.j++;	
		}
		else if (s_command[index.j])
			index.k++;
		if (s_command[index.j])
			index.j++;	
	}
	return (index);
}

void	check_quotes(char c, bool in_quotes, bool in_single_quotes)
{
	if (!in_quotes && c == '\'')
			in_single_quotes = !in_single_quotes;
	else if (!in_single_quotes && c == '\"')
		in_quotes = !in_quotes;
}
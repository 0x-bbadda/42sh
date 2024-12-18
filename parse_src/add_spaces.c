/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:26:36 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/08 15:44:24 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_spaces(char *cmd)
{
	bool	in_quotes;
	bool	in_single_quotes;
	char	*new_cmd;
	int		i;
	int		j;

	if (cmd == NULL)
		return (NULL);
	in_single_quotes = false;
	in_quotes = false;
	i = 0;
	j = 0;
	new_cmd = malloc(parse_strlen(cmd) * 3);
	if (new_cmd == NULL)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			quotes_status(cmd, &i, &in_single_quotes, &in_quotes);
		if ((cmd[i] == '>' && cmd[i + 1] == '>') 
			|| (cmd[i] == '<' && cmd[i + 1] == '<'))
		{
			if (i > 0 && cmd[i - 1] != ' ' && (!in_single_quotes && !in_quotes))
				new_cmd[j++] = ' ';
			new_cmd[j++] = cmd[i++];
			new_cmd[j++] = cmd[i];
			if (cmd[i + 1] && cmd[i + 1] != ' ' 
				&& (!in_single_quotes && !in_quotes))
				new_cmd[j++] = ' ';
		}
		else if (cmd[i] == '>' || cmd[i] == '<')
		{
			if (i > 0 && cmd[i - 1] != ' ' && (!in_single_quotes && !in_quotes))
				new_cmd[j++] = ' ';
			new_cmd[j++] = cmd[i];
			if (cmd[i + 1] && cmd[i + 1] != ' ' 
				&& (!in_single_quotes && !in_quotes) && !__is_redir(cmd[i + 1]))
				new_cmd[j++] = ' ';
		}
		else
			new_cmd[j++] = cmd[i];
		i++;
	}
	new_cmd[j] = '\0';
	return (new_cmd);
}

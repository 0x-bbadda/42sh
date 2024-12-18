/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:12:57 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/10 19:54:09 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_all_thing(char *command, int *i, int *j)
{
	(*i)++;
	if (check_end_of_command(*i, *j))
	{
		return (1);
	}
	if (command[*i] && command[*i] == '>' && command[*i] != command[*i - 1])
		return (__error(command[*i], 1), 1);
	if (command[*i] && command[*i] == command[(*i) - 1])
	{
		if (redir_error_check(command, i, j))
			return (1);
	}
	if (command[*i] == ' ')
	{
		while (command[*i] == ' ')
			(*i)++;
		if (check_end_of_command(*i, *j))
			return (1);
		if (__is_redir(command[*i]))
			return (__error(command[*i], 1), 1);
	}
	return (0);
}

int	redir_error(char *command)
{
	bool	in_quotes;
	bool	in_single_quotes;
	int		i;
	int		j;

	in_quotes = false;
	in_single_quotes = false;
	j = parse_strlen(command);
	i = -1;
	while (++i < j)
	{
		if (!in_quotes && command[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && command[i] == '\"')
			in_quotes = !in_quotes;
		if (__is_redir(command[i]) && !in_quotes && !in_single_quotes)
		{
			if (check_all_thing(command, &i, &j))
				return (1);
		}
	}
	return (0);
}

int	pipe_error(char *command, int j)
{
	bool	in_quotes;
	bool	in_single_quotes;
	int		i;

	in_quotes = false;
	in_single_quotes = false;
	i = -1;
	while (command[i] && command[i] == ' ')
		i++;
	if (command[i] && command[i] == '|')
		return (__error('|', 1), 1);
	else
	{
		while (++i < j)
		{
			quotes_status(command, &i, &in_single_quotes, &in_quotes);
			if (command[i] == '|')
			{
				i++;
				while (command[i] && command[i] == ' ')
					i++;
				if ((command[i] == '|' || i >= j) && !in_single_quotes && !in_quotes)
					return (__error('|', 1), 1);
			}
		}
	}
	return (0);
}

int	qoutes_error(char *command)
{
	bool	in_quotes;
	bool	in_single_quotes;
	int		i;
	int		j;

	in_single_quotes = false;
	in_quotes = false;
	j = parse_strlen(command);
	i = -1;
	while (++i < j)
	{
		if (!in_quotes && command[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && command[i] == '\"')
			in_quotes = !in_quotes;
	}
	if (in_single_quotes)
		return (__error('\'', 1), 1);
	if (in_quotes)
		return (__error('\"', 1), 1);
	return (0);
}

int	syntax_error(char *command, t_env *env)
{
	if (qoutes_error(command))
	{
		env->exit_status = 258;
		return (1);
	}
	if (redir_error(command))
	{
		env->exit_status = 258;
		return (1);
	}
	return (0);
}

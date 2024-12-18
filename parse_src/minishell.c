/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:08 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/12 02:36:45 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool g_signal = false;

t_index	max_files_args(char **s_command)
{
	t_index	index;
	int		i;

	index.i = 0;
	index.j = 0;
	index.k = 0;
	i = 0;
	while (s_command[i])
	{
		if (cmp(s_command[i], "<<"))
			index.j++;
		else if (s_command[i] && (cmp(s_command[i], "<")
				|| cmp(s_command[i], ">") || cmp(s_command[i], ">>")))
			index.i++;
		else if (s_command[i])
			index.k++;
		i++;
	}
	return (index);
}

void	allocate_for_me(t_index index, t_token *token)
{
	if (index.j > 0)
	{
		token->herdoc = malloc(index.j * sizeof(t_herdoc));
		token->herdoc->del = NULL;
		token->herdoc->herdoc = NULL;
		token->herdoc->expend = 1;
	}
	if (index.i > 0)
	{
		token->file = malloc(index.i * sizeof(t_opr));
		token->file->file_name = NULL;
		token->file->opr = NULL;
	}
	if (index.k > 0)
		token->arg = malloc((index.k + 1) * sizeof(char *));
}

int	fill_token(char	*command, t_token *token, t_env *e)
{
	char		*s;
	t_index		index;
	char		**s_command;
	int			i;

	i = 0;
	token->file = NULL; 
	token->herdoc = NULL;
	token->arg = NULL;
	s = add_spaces(command);
	if (syntax_error(s, e))
		return (1);
	s_command = parse_split(s, ' ');
	free(s);
	index = max_files_args(s_command);
	allocate_for_me(index, token);
	if (!__is_herdoc(s_command[0]))
		token->command = __env(s_command[0], e);
	else
		token->command = NULL;
	__token(token, s_command, e);
	simple_free(s_command);
	return (0);
}

t_lst	*toke_lexer(char **command, t_env *e)
{
	t_token		*token;
	t_lst		*lst;
	int			i;
	int			size;

	lst = NULL;
	i = -1;
	while (command[++i])
	{
		token = malloc(sizeof(t_token));
		if (fill_token(command[i], token, e))
			return (NULL);
		__ft_lstadd_back(&lst, token);
	}
	return (lst);
}
void f()
{
	system("leaks minishell");
}
int	main(int ac, char *av[], char **env)
{
	t_lst		*lst;
	t_env		*my_env;
	char		**command;
	char		*full_command;
	char		*line;

	(void)av;
	(void)ac;
	my_env = NULL;
	my_env = get_env(env);
	// atexit(f);
	while (1)
	{
		handler_signal(1);
		line = readline("\033[1;31m-\033[0m  \033[1;32mminishell-0.1$\033[0m ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			exit(my_env->exit_status);
			break ;
		}
		add_history(line);
		full_command = parse_strtrim(line, " ");
		if (!full_command)
			continue ;
		free(line);
		if (pipe_error(full_command, parse_strlen(full_command)))
			continue ;
		command = parse_split(full_command, '|');
		free(full_command);
		lst = toke_lexer(command, my_env);	
		simple_free(command);
		if (lst)
			ft_execute(lst, &my_env);
		// priiint(lst);
		remove_file();
		free_lst(lst);
	}
	free_env(&my_env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:08 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/13 18:56:41 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env(char *cmd)
{
	int i;

	i = 0;
	
	if (cmd[i] == '$')
	{
		if (cmd[i])
			i++;
		if (cmd[i] == '$')
			return (0);
		if (is_digit(cmd[i]))
			return (2);
		if (cmd[i] == '\'' || cmd[i] == '\"')
			return (3);
		return (1);
	}
	return (-1);
}

char	*replace_env(t_env *e, char *s)
{
	while (e)
	{
		if (cmp(e->content->var, s))
			return (strdup(e->content->value));
		e = e->next;
	}
	return (NULL);
}

char	*check_and_replace_env(char *s_command, t_env *e)
{
	int i;
	if (s_command)
	{
		if (check_env(s_command) == 1)
			s_command = parse_strdup(replace_env(e, s_command + 1));
		if (check_env(s_command) == 0)
			s_command = parse_strdup(s_command + 1);
		if (check_env(s_command) == 2)
			s_command = parse_strdup(s_command + 2);
		if (check_env(s_command) == 3)
			printf("baaad env \n");
	}
	return (s_command);
}

void	__token(char **s_command, t_con *c, t_env *e)
{
	t_index	index;

	index.i = 0;
	index.j = 0;
	index.k = 0;
	while (s_command[index.j])
	{
		s_command[index.j] = check_and_replace_env(s_command[index.j], e);
		if (s_command[index.j] &&(!strcmp(s_command[index.j], "<") || !strcmp(s_command[index.j], ">") 
			|| !strcmp(s_command[index.j], "<<") || !strcmp(s_command[index.j], ">>")))
		{
			c->file[index.i].opr = parse_strdup(s_command[index.j]);
			index.j++;
			s_command[index.j] = check_and_replace_env(s_command[index.j], e);
			if (s_command[index.j])
				c->file[index.i].file_name = parse_strdup(s_command[index.j]);
			index.i++;
		}
		else if (s_command[index.j])
		{
			c->arg[index.k]=  parse_strdup(s_command[index.j]);
			index.k++;
		}
		if (s_command[index.j])
			index.j++;	
	}
	c->file[index.i].opr = NULL;
	c->arg[index.k] = NULL;
}

// char	*get_without_q(char *cmd)
// {
// 	int i;

// 	i = 0;
// 	while (cmd[i])
// 	{
		
// 	}
// }
t_token	*toke_lexer(char **command, t_token *token, t_env *e)
{
	int		i;
	t_con	c;
	char	**s_command;
	char	*s;
	t_index	index;
	
	token = NULL;
	i = -1;
	while (command[++i])
	{
		s = add_spaces(command[i]);
		syntax_error(s);
		s_command = parse_split(s, ' ');
		free(s);
		// s_command = get_without_q(s_command);
		index = max_files_args(s_command);
		c.file = malloc(index.i * sizeof(t_opr));
		c.arg = malloc(index.k *sizeof(char *));
		c.file[0].opr = NULL;
		c.arg[0] = NULL;
		if (!__is_herdoc(s_command[0]))
			c.command = s_command[0];
		__token(s_command, &c, e);
		add_list_back(&token, &c);
	}
	return (token);
}

void	priiint(t_token *token)
{
	while (token)
	{
		int i = 0;
		printf("command : %s\n", token->command);
		while (token->arg[i])
		{
			printf("arg[%d] : %s\n", i, token->arg[i]);
			// if (token->prev)
			// 	printf("prev arg[%d] : %s\n", i, token->prev->arg[i]);
			i++;
		}
		int j = 0;
		while (token->file[j].opr)
		{
			printf("file name[%d] : %s\n", j, token->file[j].file_name);
			printf("opr[%d] : %s\n", j, token->file[j].opr);
			// if (token->prev)
			// 	printf("prev namefile[%d] : %s\n", j, token->prev->file[j].file_name);
			j++;
		}
		token = token->next;
	}
}

// tokenization
// check syntax error
// expended
// change $user by user define
// move "" and ''
int main (int ac, char *av[], char **env)
{
	char		**command;
	char		*full_command;
	t_token		*token;
	t_con		*c;
	t_env		*e;

	e = NULL;
	e = (t_env *)malloc(sizeof(t_env));
	token = (t_token *)malloc(sizeof(t_token));
	c = (t_con *)malloc(sizeof(t_con));
	while (1)
	{
		e = get_env(env);
		full_command = readline("⑉➤minishell-$");
		add_history(full_command);
		if (pipe_error(full_command, parse_strlen(full_command)))
			continue ;
		command = parse_split(full_command, '|');
		token = toke_lexer(command, token, e);
		priiint(token);
	}
	return (0);
}
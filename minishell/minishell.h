/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:11 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/13 18:59:22 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

# define ARGS_ERROR  "number of arguments"

typedef struct s_index
{
	int	i;
	int	j;
	int	k;
}t_index;

enum e_token_type
{
	CMD = 1,
	ARG = 2,
	SPACE = 3,
	NEW_LINE = 4,
	QUOTES = 5,
	DOUBLE_QUOTES = 6,
	ENV = 7,
	PIPE = 8,
	REDIR_IN = 9,
	REDIR_OUT = 10,
	HERE_DOC = 11,
	DREDIR_OUT = 12,
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct s_opr
{
	char	*opr;
	char	*file_name;
	// char	*del;
	// next;
}t_opr;

typedef struct s_con 
{	
	char	*command;
	char	**arg;
	t_opr	*file;
}t_con;


typedef struct s_token
{
	char				*command;
	char				**arg;
	t_opr				*file;
	struct s_token		*next;
	struct s_token		*prev;
}t_token;




// workiingg

typedef struct s_minishell
{
	char	**cmd;
	t_opr	opr;
}t_minishell;
// workiingg

// for env
typedef struct s_content 
{
	char *var;
	char *value;
}t_content;

typedef struct s_env 
{
	t_content *content;
	struct s_env *next;
}t_env;
// for env
typedef struct s_split
{
	char	**list;
	char		c;
}t_split;

typedef struct s_list
{
	t_token			*content;
	struct s_list	*next;
	struct s_list	*prev;
}t_list;


int			cmp(const char *s1, const char *s2);
char		*get_pipe(char *line);
int			is_special_char(char c);
t_token		*creat_list(char *command, char **arg, t_opr *file);
void		add_list_back(t_token **token, t_con *c);
void	    __error(char c, int i);
void		*__calloc(size_t count, size_t size);
int			is_special_char(char c);
void		check_quotes(char c, bool in_quotes, bool in_single_quotes);
// --------------------tokenization_functions-----------------//
t_index		max_files_args(char **s_command);

// --------------------syntax_error_functions-----------------//
int			syntax_error(char *command);
int			qoutes_error(char *command);
void		__free(t_list **lst);
// ---------------------get_env_function----------------------//
t_env   	*get_env( char **env);

// --------------------add_spaces----------------------------//
char		*add_spaces(char *cmd);
int 		__is_redir(char c);
int 		__is_herdoc(char *s);
int			is_print(int p);
int			is_digit(int nb);
int			is_print(int p);
int			pipe_error(char *command, int j);
// -------------------libft-----------------------------------//
int			parse_strlen(const char *str);
char		*parse_substr(char const *str, unsigned int start, size_t len);
char		**parse_split(char const *s, char c);;
char		*parse_strtrim(char const *str, char const *set);
char		*parse_strdup(const char *src);
char		*parse_strjoin(char const *s1, char const *s2);


void 		print_full_command(int j, t_token *token);
#endif
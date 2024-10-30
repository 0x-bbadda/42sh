/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:51:37 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/30 01:14:44 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*__creat_list(t_content *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (node)
	{
		node->content = content;
		node->next = NULL;
	}
	return (node);
}

static void	__add_list_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

static char	*get_var(char *str, int size)
{
	int		i;
	char	*p;

	i = -1;
	p = malloc(size + 1);
	while (++i < size)
		p[i] = str[i];
	p[i] = '\0';
	return (p);
}

static char	*__strchr(char *str, int c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i++])
	{
		size = i;
		if (str[i] == (char)c)
			return (get_var(str, size));
	}
	return (0);
}

int	__lstsize(t_env *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_env	*get_env( char **env)
{
	t_content	*content;
	t_env		*re;
	int			i;

		
	re = NULL;
	if (!*env)
	{
		content = (t_content *)malloc(sizeof(t_content));
		content->var = ft_strdup("test");
		content->value = ft_strdup("test/test/test");
		__add_list_back(&re, __creat_list(content));
	}
	i = -1;
	while (env[++i])
	{
		content = (t_content *)malloc(sizeof(t_content));
		content->var = __strchr(env[i], '=');
		content->value = getenv(content->var);
		__add_list_back(&re, __creat_list(content));
	}
	return (re);
}

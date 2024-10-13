/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:34:50 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/13 17:35:14 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*result;
	int		len;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = parse_strlen(s1) + parse_strlen(s2);
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
		result[i++] = s2[j++];
	result[len] = '\0';
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:12:50 by asalmi            #+#    #+#             */
/*   Updated: 2024/09/18 20:00:53 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			n;
	long		r;

	n = 1;
	r = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		n = 1 - 2 * (*str == '-');
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		if ((r > 922337203685477580
				|| r == 922337203685477580) && *str - 48 > 7)
		{
			if (n == 1)
				return (-1);
			return (0);
		}
		r = (r * 10) + *str - 48;
		str++;
	}
	return (n * r);
}
int main()
{
	printf("%d\n", ft_atoi("9223372036854775808"));
	printf("%d", atoi("9223372036854775808"));
}

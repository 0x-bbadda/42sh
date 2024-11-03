/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 06:45:43 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/02 18:15:57 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_ctrl_c_parent()
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_ctrl_c_nor()
{
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
}

void	handler_signal(int mode)
{
	if (mode == 1)
		signal(SIGINT, handle_ctrl_c_parent);
	else
		signal(SIGINT, handle_ctrl_c_nor);
	signal(SIGQUIT, SIG_IGN);
}

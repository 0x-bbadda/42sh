/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 00:05:51 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/20 00:54:13 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_builtin(const char *cmd)
{
    if (!strcmp(cmd, "echo"))
        return (1);
    if (!strcmp(cmd, "cd"))
        return (1);
    if (!strcmp(cmd, "pwd"))
        return (1);
    if (!strcmp(cmd, "env"))
        return (1);
    if (!strcmp(cmd, "export"))
        return (1);
    return (0);
}

int execute_builtin(t_token *cmd, t_env *env)
{
    if (!strcmp(cmd->command, "echo"))
        ft_echo(cmd);
    if (!strcmp(cmd->command, "cd"))
        ft_cd(cmd, env);
    if (!strcmp(cmd->command, "pwd"))
        ft_pwd(cmd);
    if (!strcmp(cmd->command, "env"))
        ft_env(env);
    if (!strcmp(cmd->command, "export"))
        ft_export(cmd, env);
    return (0);
}

// int elemnt_exist(t_env *env, char *var)
// {
//     int i;
//     char *value;

//     i = 0;
//     while (env)
//     {
//         if (!ft_strncmp(var->content->var, env->content->var, ft_strlen(var->content->var)))
//         {
//             if (var->content->value)
//                 env->content->value = var->content->value;
//             return (1);
//         }
//         env = env->next;
//     }
//     return (0);
// }
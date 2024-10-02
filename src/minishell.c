/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/02 16:13:36 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command *test_token(char *input_line)
{
    t_command *cmd;
    char *token;
    int i = 0;
    
    cmd = malloc(sizeof(t_command));
    cmd->args = malloc(sizeof(char *) * 10);
    if (cmd == NULL || cmd->args == NULL)
        exit(EXIT_FAILURE);
    token = strtok(input_line, " ");
    cmd->command = token;
    cmd->type = CMD;
    while (token != NULL)
    {
        if (strcmp(token, "|") == 0)
        {
            cmd->args[i] = NULL;
            cmd->next = malloc(sizeof(t_command));
            if (cmd->next == NULL)
                exit(EXIT_FAILURE);
            cmd->next->prev = cmd;
            cmd->next->type = PIPE;
            cmd->next->next = test_token(NULL);
            return cmd;
        }
        cmd->args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    cmd->args[i] = NULL;
    cmd->next = NULL;
    return cmd;
}

int main(int ac, char **av, char **env)
{
    t_command *cmd;
    t_env *my_env;
    pid_t pid;
    char *input_line;
    int status;

    while (1)
    {
        input_line = readline("\033[1;31m-\033[0m  \033[1;32mminishell-0.1$\033[0m ");
        if (input_line == NULL)
        {
            free(input_line);
            exit(EXIT_FAILURE);
        }
        cmd = test_token(input_line);
        execute_piped_commands(cmd, env);
        free(input_line);
    }
    return EXIT_SUCCESS;
}

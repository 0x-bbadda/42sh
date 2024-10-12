/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/12 16:40:44 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_command *fill_cmd(void)
// {
//     t_command *cmd;
//     t_command *cmd2;
//     // t_command *cmd3;
//     t_redirection *redirection;
//     t_redirection *redirection2;
    
//     cmd = malloc(sizeof(t_command));
//     cmd2 = malloc(sizeof(t_command));
//     // cmd3 = malloc(sizeof(t_command));
//     if (!cmd || !cmd2)
//         exit(EXIT_FAILURE);
//     cmd->command = "ls";
//     cmd->args = malloc(sizeof(char *) * 2);
//     if (!cmd->args)
//         exit(EXIT_FAILURE);
//     cmd->args[0] = "ls";
//     cmd->args[1] = NULL;
//     cmd->next = NULL;
//     // cmd->args[2] = NULL;
//     // cmd->type = CMD;

//     // cmd3->command = "wc";
//     // cmd3->args = malloc(sizeof(char *) * 2);
//     // if (!cmd3->args)
//     //     exit(EXIT_FAILURE);
//     // cmd3->args[0] = "wc";
//     // cmd3->args[1] = NULL;
//     // cmd3->type = CMD;
//     // cmd3->next = NULL;
    
//     cmd2->command = "ls";
//     cmd2->args = malloc(sizeof(char *) * 3);
//     if (!cmd2->args)
//         exit(EXIT_FAILURE);
//     cmd2->args[0] = "ls";
//     cmd2->args[1] = "-l";
//     cmd2->args[2] = NULL;
//     // cmd2->type = PIPE;
//     cmd2->next = NULL;

    
//     redirection = malloc(sizeof(t_redirection));
//     if (!redirection)
//         exit(EXIT_FAILURE);
//     redirection->file_name = "file";
//     redirection->opr = ">";
//     redirection->delimiter = NULL;
//     redirection->next = NULL;

//     // redirection2 = malloc(sizeof(t_redirection));
//     // if (!redirection2)
//     //     exit(EXIT_FAILURE);
//     // redirection2->file_name = NULL;
//     // redirection2->opr = "<<";
//     // redirection2->delimiter = "B";
//     // redirection2->next = NULL;
    
//     redirection->next = NULL;
    
//     cmd->redirection = redirection;
//     cmd->next = NULL;

//     return (cmd);
// }

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
        // cmd = fill_cmd();
        if (cmd->redirection->delimiter != NULL && !ft_strncmp(cmd->redirection->opr, "<<", ft_strlen(cmd->redirection->opr)))
			handle_heredoc(cmd);
        execute_piped_commands(cmd, env);
        free(input_line);
    }
    return EXIT_SUCCESS;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:46 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/31 01:43:27 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_piped_commands(t_token *cmd, t_env **env)
{
    int fd[2];
    int pipeLine;
	char *path;
	char *executable_path;
	int status;
	t_env *my_env;
	t_token *head;

	head = cmd;
	pipeLine = -1;

    while (cmd)
    {
		if (cmd->next != NULL)
			pipe(fd);
		handler_signal(0);
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			if (pipeLine != -1)
			{
				dup2(pipeLine, STDIN_FILENO);
				close(pipeLine);
			}
			if (cmd->next != NULL)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			close(fd[0]);
			close(fd[1]);
			// if (cmd->redirection)
			// 	redirection_handler(cmd);
			if (is_builtin(cmd->command))
			{
				execute_builtin(cmd, env);
				exit(EXIT_SUCCESS);
			}
			executable_path = check_path(cmd, *env);
			if (!executable_path)
				exit((*env)->exit_status);
			if (execve(executable_path, cmd->arg, copy_env(*env)) == -1)
			{
				// should free(array in copy_env if execve is faild)
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else if (cmd->pid > 0)
		{
			if (pipeLine != -1)
				close(pipeLine);
			pipeLine = dup(fd[0]);
			close(fd[0]);
			close(fd[1]);
		}
        cmd = cmd->next;
    }
	cmd = head;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			handler_signal(1);
			if (WIFEXITED(status))
				(*env)->exit_status = WEXITSTATUS(status);
		}
		cmd = cmd->next;
	}
	
}


#include "../includes/minishell.h"

char *find_executable_file(char *command, char *path)
{
    char *executable_path;
    char **dirs;
    int i;

    dirs = ft_split(path, ':');
    i = 0;
    while (dirs[i])
    {
        executable_path = ft_strjoin(ft_strjoin(dirs[i], "/"), command);
        if (access(executable_path, F_OK | X_OK) == 0)
            return (executable_path);
        free(executable_path);
        i++;
    }
    return (NULL);
}

// int *execute_external_command(t_command *cmd, char **env)
// {
//     t_env *my_env;
//     pid_t pid;
//     char *path;
//     char *executable_path;
//     int status;

//     my_env = copy_env(env);
//     path = find_path(my_env);
//     executable_path = find_executable_file(cmd->args[0] ,path);
//     pid = fork();
//     if (pid == 0)
//     {
//         if (executable_path)
//         {
//             execve(executable_path, cmd->args, NULL);
//         }
//         else
//         {
//             printf("command not found\n");
//             exit(EXIT_FAILURE);
//         }
//     }
//     else if (pid > 0)
//         waitpid(pid, &status, 0);
//     return (0);
// }

void execute_piped_commands(t_command *cmd, char **env)
{
    int fd[2];
    int pipeLine;
    pid_t pid;
	char *path;
	char *executable_path;
	int status;
	t_env *my_env;

	my_env = copy_env(env);
	pipeLine = -1;
    while (cmd)
    {
		if (cmd->type == PIPE)
			cmd = cmd->next;
		if (cmd->next != NULL)
			pipe(fd);
		pid = fork();
		if (pid == 0)
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
			path = find_path(my_env);
			executable_path = find_executable_file(cmd->command, path);
			if (execve(executable_path, cmd->args, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (pipeLine != -1)
				close(pipeLine);
			pipeLine = dup(fd[0]);
			close(fd[0]);
			close(fd[1]);
		}
        cmd = cmd->next;
    }
}

// void ft_execute(t_command *cmd, char **env)
// {
// 	printf("----- start -----\n");
// 	execute_piped_commands(cmd, env);
// 	printf("----- end -----\n");
// }

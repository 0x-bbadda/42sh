#include "../includes/minishell.h"

void redirection_handler(t_command *cmd)
{
    t_command *cmd1;
    int fd;

    cmd1 = cmd;
    while (cmd1->redirection)
    {
        if (!ft_strncmp(cmd->redirection->opr, ">", ft_strlen(cmd->redirection->opr)))
        {
            fd = open(cmd1->redirection->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd < 0)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            if (cmd1->redirection->next == NULL)
                dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        if (!ft_strncmp(cmd->redirection->opr, "<", ft_strlen(cmd->redirection->opr)))
        {
            fd = open(cmd1->redirection->file_name, O_RDONLY);
            if (fd < 0)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            if (cmd1->redirection->next == NULL)
                dup2(fd, STDIN_FILENO);
            close(fd);
        }
        if (!ft_strncmp(cmd->redirection->opr, ">>", ft_strlen(cmd->redirection->opr)))
        {
            fd = open(cmd1->redirection->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
            if (fd < 0)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            if (cmd1->redirection->next == NULL)
                dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        cmd1->redirection = cmd1->redirection->next;
    }
}

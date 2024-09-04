/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosgor <hosgor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:18:11 by fhosgor           #+#    #+#             */
/*   Updated: 2024/09/05 00:02:57 by hosgor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pipe(t_mini *mini, char **command, int i)
{
	int	pipe[2];

	if (g_global_exit == 130)
		return ;
	pipe_checker(pipe);
	mini->pid = fork();
	if (mini->pid == 0)
	{
		ft_signal_regulator(CHILD_P);
		close(pipe[0]);
		output_input_regulator(mini, i, pipe);
		check_builtin_status(mini);
		if (mini->status != BUILTIN)
			run_cmd(mini, command);
		else
			check_builtin(mini, i);
		exit (g_global_exit);
	}
	close(pipe[1]);
	dup2(pipe[0], 0);
	close(pipe[0]);
}

char	**execve_command(t_mini *mini, char **temp2)
{
	char	**ret;
	int		i;

	i = 0;
	if (mini->flag_arg)
	{
		temp2 = ft_split(mini->flag_arg, ' ');
		while (temp2[i])
			i++;
	}
	if (mini->cmd != NULL)
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	if (mini->cmd != NULL)
		ret[0] = ft_strdup(mini->cmd);
	i = 0;
	while (temp2 && temp2[i] && ++i)
		ret[i] = ft_strdup(temp2[i - 1]);
	if (i == 0 && mini->cmd == NULL)
		ret[0] = NULL;
	else
		ret[i + 1] = NULL;
	return (ft_free_dp(temp2), ret);
}

int	status_check(t_mini *temp)
{
	if (temp->status == PIPE || temp->status == PIPEAPPEND)
		return (1);
	else if (temp->status == HEREDOC || temp->status == HEREDOCAPPEND \
	|| temp->status == PIPEHEREDOC || temp->status == PIPEHEREDOCAPPEND)
		return (2);
	else
		return (3);
}

int	ft_executer(t_mini *mini, char **command, int i, int fd[2])
{
	if (status_check(mini) == 1)
	{
		if (mini->heredoc && mini->heredoc[0])
			heredoc_pipe(mini, fd, command);
		if (g_global_exit == 130)
			return (0);
		execute_pipe(mini, command, i);
	}
	else if (status_check(mini) == 2)
	{
		heredoc_pipe(mini, fd, command);
		if (g_global_exit == 130)
			return (0);
		execute_pipe(mini, command, i);
	}
	else
	{
		if (mini->heredoc && mini->heredoc[0])
			heredoc_pipe(mini, fd, command);
		if (g_global_exit == 130)
			return (0);
		child_procces(mini, command, i);
	}
	return (1);
}

void	read_and_exec(t_mini *mini, int i)
{
	t_mini	*temp;
	char	**command;
	int		fd[2];

	temp = mini;
	duplicate_default_fd(fd);
	g_global_exit = 0;
	while (temp)
	{
		command = execve_command(temp, NULL);
		if (!ft_executer(temp, command, i, fd))
			break ;
		ft_free_dp(command);
		temp = temp->next;
	}
	close_duplicate_fd(fd);
	wait_and_status(mini, i);
	ft_free_struct(mini);
}

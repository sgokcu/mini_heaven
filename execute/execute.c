/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:10:04 by fhosgor           #+#    #+#             */
/*   Updated: 2024/08/23 14:29:12 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(t_mini *cmd)
{
	int	i;

	i = 0;
	while (cmd->env && cmd->env[i])
	{
		if (ft_strnstr(cmd->env[i], "PATH=", 5))
		{
			return (ft_split(ft_strchr(cmd->env[i], '/'), ':'));
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_mini *cmd, char **command, char **path, char *temp)
{
	char	*temp2;
	int		i;

	i = -1;
	path = get_path(cmd);
	if (!path)
	{
		printf("PATH ERROR\n");
		exit(1);
	}
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		temp2 = ft_strjoin(temp, command[0]);
		if (!access(temp2, X_OK))
		{
			free(temp);
			return (temp2);
		}
		free(temp);
		free(temp2);
	}
	printf("minishell: %s: command not found\n", command[0]);
	exit(127);
	return (NULL);
}

void	run_cmd(t_mini *mini, char **command)
{
	char	*path;

	if (!command[0])
		return ;
	if (check_same(command[0], "") == 0)
	{
		printf("minishell: %s: No such file or directory\n", command[0]);
		g_global_exit = 127;
		return ;
	}
	if (strchr(command[0], '/'))
	{
		if (access(command[0], X_OK))
		{
			printf("minishell: %s: No such file or directory\n", command[0]);
			g_global_exit = 127;
			exit(127);
		}
		path = command[0];
	}
	else
		path = get_cmd_path(mini, command, NULL, NULL);
	execve(path, command, mini->env);
}

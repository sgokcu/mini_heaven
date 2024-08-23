/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:27:36 by fhosgor           #+#    #+#             */
/*   Updated: 2024/08/23 18:39:10 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	duplicate_default_fd(int fd[2])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
}

void	close_duplicate_fd(int fd[2])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

void	pipe_checker(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe error");
		exit(127);
	}
}

int	check_same(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0 \
	&& ft_strncmp(s2, s1, ft_strlen(s2)) == 0)
		return (0);
	return (1);
}

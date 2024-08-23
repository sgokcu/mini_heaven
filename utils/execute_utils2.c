/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:15:10 by fhosgor           #+#    #+#             */
/*   Updated: 2024/08/23 18:41:33 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_list_count(t_mini *mini)
{
	int		i;
	t_mini	*temp;

	i = 0;
	temp = mini;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	ft_main_signal2(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_global_exit = 1;
	}
}

void	ft_main_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global_exit = 1;
	}
}

void	ft_heredoc_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_global_exit = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ft_signal_regulator(int status)
{
	if (status == MAIN_P)
	{
		signal(SIGINT, &ft_main_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == CHILD_P)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (status == HEREDOC_P)
	{
		signal(SIGINT, &ft_heredoc_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == MAIN_P2)
	{
		signal(SIGINT, &ft_main_signal2);
		signal(SIGQUIT, SIG_IGN);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:31:48 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/06 16:49:44 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_struct(t_mini *mini)
{
	while (mini)
	{
		if (mini->cmd)
			free(mini->cmd);
		if (mini->flag_arg && mini->flag_arg[0])
			free(mini->flag_arg);
		if (mini->input)
			ft_free_dp(mini->input);
		if (mini->append)
			ft_free_dp(mini->append);
		if (mini->output)
			ft_free_dp(mini->output);
		if (mini->heredoc)
			ft_free_dp(mini->heredoc);
		if (mini->arg)
		{
			free(mini->arg);
			mini->arg = NULL;
		}
		if (mini->redirect)
		{
			free (mini->redirect);
			mini->redirect = NULL;
		}
		if (mini->utils)
		{
			free (mini->utils);
			mini->utils = NULL;
		}
		mini = mini->next;
	}
}

int	status_check2(t_mini *mini)
{
	t_mini	*temp;
	
	temp = mini;
	while (temp)
	{
		if (status_check(temp) == 2)
			return (1);
		temp = temp->next;
	}
	return (0);
}
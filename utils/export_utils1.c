/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:46:32 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/05 16:20:10 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	take_name_for_export(char *str, t_mini *mini)
{
	int	i;

	i = 0;
	mini->redirect->start += i;
	mini->redirect->len = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			mini->redirect->len += 1;
			break ;
		}
		i++;
		mini->redirect->len += 1;
	}
	free(str);
}

int	does_env_have(char *str, t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (!ft_strncmp(str, mini->env[i], ft_strlen(str)))
			return (i);
		i++;
	}
	return (0);
}

int	export_unset_control(int *control)
{
	if ((*control) == 1)
	{
		(*control) = 0;
		return (1);
	}
	else
		return (0);
}

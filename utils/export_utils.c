/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:41:59 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/04 19:43:22 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*export_business(char *str, t_mini *mini)
{
	char	*hold;

	take_name_for_export(delete_quotes(ft_strdup(str), mini, 0, 0), mini);
	hold = ft_substr(delete_quotes(ft_strdup(str), mini, 0, 0),
		mini->redirect->start, mini->redirect->len);
	return (hold);
}
void	env_recent(char **envi, t_mini *mini)
{
	int	i;

	mini->env = malloc(sizeof(char *) * (count_environ(mini->env) + 2));
	i = 0;
	while (envi[i]) 
	{
		mini->env[i] = ft_strdup(envi[i]);
		i++;
	}
	mini->env[i] = NULL;
	free_env(envi);
}

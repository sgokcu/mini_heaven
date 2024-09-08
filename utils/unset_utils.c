/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:49:52 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/08 15:36:38 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_typo(char **keep, int *i, int j, int *control)
{
	while (keep[(*i)][j])
	{
		if (!(ft_isalnum(keep[(*i)][j])) && keep[(*i)][j] != '#'
			&& keep[(*i)][j] != '_')
		{
			printf("unset: '%s': not a valid identifier\n", keep[(*i)]);
			(*i)++;
			(*control) = 1;
			break ;
		}
		j++;
	}
}

int	count_unsets(char **str, t_mini *mini, int i)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (mini->env[i])
	{
		while (str[j])
		{
			if (mini->env[i]
				&& !ft_strncmp(mini->env[i], str[j], ft_strlen(str[j])))
			{
				count++;
				i++;
				j = 0;
			}
			else
				j++;
		}
		if (mini->env[i] != NULL)
			i++;
		j = 0;
	}
	return (count);
}

void	find_match(char **str, char **envi, int *control, int *i)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (!ft_strncmp(envi[(*i)], str[j], ft_strlen(str[j])))
		{
			(*i)++;
			j = 0;
			(*control) = 1;
			break ;
		}
		j++;
	}
}

void	to_make_it_shorter(t_mini *mini, char **valid, int *k)
{
	valid[(*k)] = NULL;
	(*k) = 0;
	cmp_env(valid, mini->env, mini, count_unsets(valid, mini, 0));
}

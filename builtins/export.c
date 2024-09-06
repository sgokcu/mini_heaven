/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:24:07 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/06 14:53:57 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exp_control(char **keep, int *i)
{
	if (keep[0][0] == '-')
	{
		printf("export: invalid option\n");
		return (0);
	}
	if (((keep[(*i)][0] >= '0' && keep[(*i)][0] <= '9') \
	|| keep[(*i)][0] == '='))
	{
		printf("export: '%s': not a valid identifier\n", keep[(*i)]);
		(*i)++;
		return (1);
	}
	if (!ft_strchr(keep[(*i)], '='))
	{
		(*i)++;
		return (1);
	}
	return (-1);
}

void	exp_contains_equal(char **keep, int *i, int j, int *control)
{
	while (keep[(*i)][j] != '=')
	{
		if (!(ft_isalnum(keep[(*i)][j])) && keep[(*i)][j] != '_' \
		&& keep[(*i)][j] != 34 && keep[(*i)][j] != 39)
		{
			printf("export: '%s': not a valid identifier\n", keep[(*i)]);
			(*i)++;
			(*control) = 1;
			break ;
		}
		j++;
	}
}

void	exp_putting(t_mini *mini, char **keep, int *i)
{
	char	*hold;

	hold = export_business(keep[(*i)], mini);
	if (does_env_have(hold, mini))
	{
		free(mini->env[does_env_have(hold, mini)]);
		mini->env[does_env_have(hold, mini)] = \
		delete_quotes(ft_strdup(keep[(*i)]), mini, 0, 0);
	}
	else
	{
		put_env(delete_quotes(ft_strdup(keep[(*i)]), mini, 0, 0), mini);
	}
	free(hold);
	(*i)++;
}

void	ft_start_exp(t_mini *mini)
{
	char	**keep;
	int		i;
	int		d;
	int		control;

	i = 0;
	control = 0;
	keep = mm_split(mini->flag_arg, ' ');
	while (keep[i])
	{
		d = exp_control(keep, &i);
		if (d == 0)
		{
			free_env(keep);
			return ;
		}
		else if (d == 1)
			continue ;
		exp_contains_equal(keep, &i, 0, &control);
		if (export_unset_control(&control) == 1)
			continue ;
		else
			exp_putting(mini, keep, &i);
	}
	free_env(keep);
}

void	ft_export(t_mini *mini)
{
	if (mini->flag_arg && mini->flag_arg[0])
	{
		ft_start_exp(mini);
		
	}
	else
		ft_env(mini, 1);
}

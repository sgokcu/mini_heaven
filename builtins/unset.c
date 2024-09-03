/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:24:12 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/03 20:00:57 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int unset_check(char **keep, int *i)
{
	if(keep[0][0] == '-')
	{
		printf("unset: invalid option\n");
		return (0);
	}
	if((keep[(*i)][0] >= '0' && keep[(*i)][0] <= '9'))
	{
		printf("unset: '%s': not a valid identifier\n", keep[(*i)]);
		(*i)++;
		return (1);
	}
	return (-1);
}

void unset_typo(char **keep, int *i, int j, int *control)
{
	while(keep[(*i)][j])
	{
		if(!(ft_isalnum(keep[(*i)][j])) && keep[(*i)][j] != '#' && keep[(*i)][j] != '_')
		{
			printf("unset: '%s': not a valid identifier\n", keep[(*i)]);
			(*i)++;
			(*control) = 1;
			break ;
		}
		j++;
	}
}



void ft_start_unset(t_mini *mini)
{
	int i;
	int k;
	int d;
	char **keep;
	char **valid;
	int control;
	int s;

	i = 0;
	k = 0;
	control = 0;
	keep = mm_split(mini->flag_arg, ' ');
	valid = NULL;
	valid = malloc(sizeof(char *) * (count_environ(keep)) + 1);
	while(keep[i])
	{
		s = unset_check(keep, &i);
		if(s == 0)
			return ;
		else if(s == 1)
			continue ;
		unset_typo(keep, &i, 0, &control);
		if(control == 1)
		{
			control = 0;
			continue;
		}
		else
			valid[k++] = ft_strjoin(keep[i++], "=");
	}
	valid[k] = NULL;
	k = 0;
	cmp_env(valid, mini->env, mini, count_unsets(valid, mini));
}

int count_unsets(char **str, t_mini *mini)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	j = 0;
	while(mini->env[i])
	{
		while(str[j])
		{
			if(mini->env[i] && !ft_strncmp(mini->env[i], str[j], ft_strlen(str[j])))
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

void cmp_env(char **str, char **envi, t_mini *mini, int count)
{
	int i;
	int j;
	int e;
	int control;

	mini->env = malloc(sizeof(char *) * (count_environ(mini->env) - count + 1));
	i = 0;
	j = 0;
	e = 0;
	control = 0;
	while(envi[i])
	{
		while(str[j])
		{
			if(!ft_strncmp(envi[i], str[j], ft_strlen(str[j])))
			{
				i++;
				j = 0;
				control = 1;
				break ;
			}
			j++;
		}
		if(control == 0)
		{
			mini->env[e++] = ft_strdup(envi[i]);
			i++;
			j = 0;
		}
		else
			control = 0;
	}
	mini->env[e] = NULL;
	free_env(envi);
}

void	ft_unset(t_mini *mini)
{
	if (mini->flag_arg && mini->flag_arg[0])
		ft_start_unset(mini);
}

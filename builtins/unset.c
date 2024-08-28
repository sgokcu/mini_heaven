#include "../minishell.h"
//exportta bi yerde int index döndürüyorum ya 0 olursa ona bak.
//$0 $?

void ft_start_unset(t_mini *mini)
{
	int i;
	int j;
	int k;
	int d;
	char **keep;
	char **valid;
	int control;

	i = 0;
	j = 0;
	k = 0;
	control = 0;
	valid =  NULL;
	keep = mm_split(mini->flag_arg, ' ');
	valid = malloc(sizeof(char *) * (count_environ(keep)) + 1);
	while(keep[i])
	{
		if(keep[0][0] == '-')
		{
			printf("unset: invalid option\n");
			return ;
		}
		if((keep[i][0] >= '0' && keep[i][0] <= '9'))
		{
			printf("unset: '%s': not a valid identifier\n", keep[i]);
			i++;
			continue ;
		}
		while(keep[i][j])
		{
			if(!(ft_isalnum(keep[i][j])) && keep[i][j] != '#' && keep[i][j] != '_')
			{
				printf("unset: '%s': not a valid identifier\n", keep[i]);
				i++;
				control = 1;
				break ;
			}
			j++;
		}
		j = 0;
		if(control == 1)
		{
			control = 0;
			continue;
		}
		else
		{
			valid[k] = ft_strjoin(keep[i], "=");
			k++;
			i++;
		}
	}
	valid[k] = NULL;
	k = 0;
	d = count_unsets(valid, mini);
	cmp_env(valid, mini->env, mini, d);
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

#include "../minishell.h"


void	start_exp(t_mini *mini)
{
	char **keep;
	int i;
	int j;
	int control;

	i = 0;
	j = 0;
	control = 0;
	keep = mm_split(mini->flag_arg, ' ');
	while(keep[i])
	{
		if(keep[0][0] == '-')
		{
			printf("export: invalid option\n");
			return ;
		}
		if((keep[i][0] >= '0' && keep[i][0] <= '9'))
		{
			printf("export: '%s': not a valid identifier\n", keep[i]);
			i++;
			continue ;
		}
		if(!ft_strchr(keep[i], '='))
		{
			i++;
			continue ;
		}
		while(keep[i][j] != '=')
		{
			if(keep[i][j] == '-' || keep[i][j] == '?')
			{
				printf("export: '%s': not a valid identifier\n", keep[i]);
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
			put_env(keep[i], mini);
			i++;
		}
	}
	print_env(mini, 8);
}

void put_env(char *str, t_mini *mini)
{
	int d;

	take_env(mini);
	d = env_count_full(mini);
	mini->env[d] = ft_strdup(str);
	mini->env[d + 1] = NULL;
}

int env_count_full(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i] && mini->env[i][0])
		i++;
	return (i);
}


void	ft_export(t_mini *mini)
{
	if (mini->flag_arg && mini->flag_arg[0])
	{
		start_exp(mini);
	}
	else
		print_env(mini, 1);
}

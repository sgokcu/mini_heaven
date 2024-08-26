#include "../minishell.h"

void	start_exp(t_mini *mini)
{
	char	**keep;
	int		i;
	int		j;
	int		control;
	char	*hold;

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
			hold =  export_business(keep[i], mini);
			if(does_env_have(hold, mini))
			{
				free(mini->env[does_env_have(hold, mini)]);
				mini->env[does_env_have(hold, mini)] = delete_quotes(ft_strdup(keep[i]), mini);
			}
			else
			{
				put_env(delete_quotes(ft_strdup(keep[i]), mini), mini);
			}
			i++;
		}
	}
}

int does_env_have(char *str, t_mini *mini)
{
	int i;

	i = 0;
	while (mini->env[i])
    {
        if(!ft_strncmp(str, mini->env[i], ft_strlen(str)))
			return (i);
		i++;
    }
	return (0);
}

void	take_name_for_export(char *str, t_mini *mini)
{
    int i;

    i = 0;
	mini->redirect->start += i;
	mini->redirect->len = 0;
    while (str[i])
    {
        if(str[i] == '=')
		{
			mini->redirect->len += 1;
            break ;
		}
        i++;
		mini->redirect->len += 1;
    }
	free(str);
}

char *export_business(char *str, t_mini *mini)
{
	char *hold;

    take_name_for_export(delete_quotes(ft_strdup(str), mini), mini);
    hold = ft_substr(delete_quotes(ft_strdup(str), mini), mini->redirect->start, mini->redirect->len);
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

void free_env(char **envi)
{
	int i;

	i = 0;
	while(envi[i])
	{
		free(envi[i]);
		envi[i] = NULL;
		i++;
	}
	free(envi);
}
void put_env(char *str, t_mini *mini)
{
	int d;

	env_recent(mini->env, mini);
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


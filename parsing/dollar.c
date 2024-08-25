#include "../minishell.h"


char *is_dollar_exist_and_valid(char *str, t_mini *mini)
{
    int i;
    int sq;
    int dq;
    char *hold;
    char *s1;
    char *s2;
	char *line;
	char *val;
    char *value;



    sq = 0;
    dq = 0;
    i = 0;
	struct_business(mini);
    while(str[i] && (quote_check(str[i], &sq, &dq), 1))
    {
        if (str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0'))
            i++;
        else if(str[i] == '$' && (str[i + 1] == 34 || str[i + 1] == 39))
        {
            fill_space(str, i, 1);
            hold = delete_quotes(str, mini);
        }
        else if(str[i] == '$' && sq % 2 == 0)
        {
            hold = dollar_business(str, mini, &i);
            s1 = ft_substr(str, 0, i);
            s2 = ft_substr(str, i + mini->redirect->len + 1, ft_strlen(str + (i + mini->redirect->len)));
            val = env_contains(hold, mini);
            if (!val)
            {
            	line = ft_strjoin(s1, s2);
            }
            else
			{
                value = val_redirect(val, mini);
                free(val);
				hold = ft_strjoin(s1, value);
				line = ft_strjoin(hold, s2);
                free(hold);
			}
			free(str);
			str = line;
            printf("str: %s\n", str);
			free(s1);
			free(s2);
			i = 0;
			continue ;
        }
        i++;
    }
	return(str);
}

char    *val_redirect(char *str, t_mini *mini)
{
    int i;
    int j;
    int redirect;
    char *val;

    i = 0;
    j = 0;
    redirect = 0;
    mini->utils->sq = 0;
    mini->utils->dq = 0;
    while(str[i] && (quote_check(str[i], &mini->utils->sq, &mini->utils->dq), 1))
    {
        if(str[i] == '<' && mini->utils->sq % 2 == 0)
            redirect++;
        if(str[i] == '>' && mini->utils->sq % 2 == 0)
            redirect++;
        if(str[i] == '|' && mini->utils->sq % 2 == 0)
            redirect++;
        i++;
    }
    val = malloc((ft_strlen(str) + (redirect * 2) + 1));
    i = 0;
    mini->utils->sq = 0;
    mini->utils->dq = 0;
    while(str[i] && (quote_check(str[i], &mini->utils->sq, &mini->utils->dq), 1))
    {
        if(str[i] == '<' && mini->utils->sq % 2 == 0)
        {
            val[j++] = 34;
            val[j++] = str[i];
            val[j++] = 34;
        }
        else if(str[i] == '>' && mini->utils->sq % 2 == 0)
        {
            val[j++] = 34;
            val[j++] = str[i];
            val[j++] = 34;
        }
        else if(str[i] == '|' && mini->utils->sq % 2 == 0)
        {
            val[j++] = 34;
            val[j++] = str[i];
            val[j++] = 34;
        }
        else
            val[j++] = str[i];
        i++;
    }
    val[j] = '\0';
    return (val);
}

char	*env_contains(char *str, t_mini *mini)
{
    int i;
    char *value;
    char *tmp;

    i = 0;
    tmp = ft_strjoin(str, "=");
    value = NULL;
    while (mini->env[i])
    {
        if(!ft_strncmp(tmp, mini->env[i], ft_strlen(tmp)))
            value = ft_substr(mini->env[i], ft_strlen(tmp), (ft_strlen(mini->env[i]) - ft_strlen(tmp)));
        i++;
    }
    free(str);
    free(tmp);
    return (value);
}

void take_name_for_dollar(char *str, t_mini *mini)
{
    int i;

    i = 0;
	mini->redirect->start += i;
	mini->redirect->len = 0;
    while (str[i])
    {
        if(!(ft_isalnum(str[i]) || str[i] == '_')) //$1a örneğinde çalışmıyor.
            break ;
        i++;
		mini->redirect->len += 1;
    }
}

char *dollar_business(char *str, t_mini *mini, int *i)
{
    char *hold;

    mini->redirect->start = (*i) + 1;
	take_name_for_dollar(str + ((*i) + 1), mini);
    hold = delete_quotes(ft_substr(str, mini->redirect->start, mini->redirect->len), mini);
    return (hold);
}

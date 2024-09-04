/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:23:47 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/04 18:43:13 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void dollar_zero_question_free(char **str, char *hold, char *s1, char *s2)
{
	char *line;

	line = ft_strjoin(hold, s2);
	free(hold);
	free(*str);
	*str = line;
	free(s1);
	free(s2);
}

int dollar_check(char	**str, int *i, t_mini *mini, int sq)
{
	char *hold;

	if ((*str)[(*i)] == '$' && ((*str)[(*i) + 1] == ' '
		|| (*str)[(*i) + 1] == '\t' || (*str)[(*i) + 1] == '\0'))
		(*i)++;
	else if((*str)[(*i)] == '$' && ((*str)[(*i) + 1] == 34 || (*str)[(*i) + 1] == 39))
	{
		fill_space(*str, (*i), 1);
		hold = dollar_business(*str, mini, &(*i));
	}
	else if((*str)[(*i)] == '$' && sq % 2 == 0)
	{
		dollar_working(mini, str, &(*i));
		return (1);
	}
	return (0);
}
void dollar_zero_question(char	**str, int *i)
{
	char *hold;
	char *val;
	char *s1;
	char *s2;

	s1 = ft_substr(*str, 0, (*i));
	s2 = ft_substr(*str, (*i) + 2, ft_strlen((*str) + (*i) + 2));
	if((*str)[(*i) + 1] == '0')
		hold = ft_strjoin(s1, "./minishell");
	else
	{
		val = ft_itoa(g_global_exit);
		hold = ft_strjoin(s1, val);
		free(val);
	}
	dollar_zero_question_free(str, hold, s1, s2);
	(*i) = 0;
}

char *dollar_line(char *val, char *s1, char *s2, t_mini *mini)
{
	char *line;
	char *value;
	char *hold;

	if (!val)
		line = ft_strjoin(s1, s2);
	else
	{
		value = val_redirect(val, mini, 0, 0);
		free(val);
		hold = ft_strjoin(s1, value);
		line = ft_strjoin(hold, s2);
		free(hold);
	}
	return (line);
}
void dollar_working(t_mini *mini, char **str, int *i)
{
	char *hold;
	char *val;
	char *line;
	char *s1;
	char *s2;

	hold = dollar_business(*str, mini, &(*i));
	s1 = ft_substr(*str, 0, (*i));
	s2 = ft_substr(*str, (*i) + mini->redirect->len + 1, ft_strlen(*str + ((*i) + mini->redirect->len)));
	val = env_contains(hold, mini);
	line = dollar_line(val, s1, s2, mini);
	free(*str);
	*str = line;
	free(s1);
	free(s2);
	(*i) = 0;
}

char *is_dollar_exist_and_valid(char *str, t_mini *mini)
{
	int i;
	int sq;
	int dq;

	sq = 0;
	dq = 0;
	i = 0;
	struct_business(mini);
	while(str[i] && (quote_check(str[i], &sq, &dq), 1))
	{
		if(str[i] == '$' && (str[i + 1] == '0' || str[i + 1] == '?')
			&& (str[i + 2] == ' ' || str[i + 2] == '\t'
			|| str[i + 2] == '\0' || str[i + 2] == '$'))
		{
			dollar_zero_question(&str, &i);
			continue ;
		}
		if(dollar_check(&str, &i, mini, sq) == 1)
			continue ;
		i++;
	}
	return(str);
}
void put_quotes(char *val, int *j, char *str, int *i)
{
	val[(*j)++] = 34;
	val[(*j)++] = str[(*i)];
	val[(*j)++] = 34;
}

void count_redirect(char *str, t_mini *mini, int *redirect, int *i)
{
	if(str[(*i)] == '<' && mini->utils->sq % 2 == 0)
		(*redirect)++;
	if(str[(*i)] == '>' && mini->utils->sq % 2 == 0)
		(*redirect)++;
	if(str[(*i)] == '|' && mini->utils->sq % 2 == 0)
		(*redirect)++;
	(*i)++;
}

char	*val_redirect(char *s, t_mini *mini, int i, int j)
{
	int redirect;
	char *val;

	redirect = 0;
	mini->utils->sq = 0;
	mini->utils->dq = 0;
	while(s[i] && (quote_check(s[i], &mini->utils->sq, &mini->utils->dq), 1))
		count_redirect(s, mini, &redirect, &i);
	val = malloc((ft_strlen(s) + (redirect * 2) + 1));
	i = 0;
	while(s[i] && (quote_check(s[i], &mini->utils->sq, &mini->utils->dq), 1))
	{
		if(s[i] == '<' && mini->utils->sq % 2 == 0)
			put_quotes(val, &j, s, &i);
		else if(s[i] == '>' && mini->utils->sq % 2 == 0)
			put_quotes(val, &j, s, &i);
		else if(s[i] == '|' && mini->utils->sq % 2 == 0)
			put_quotes(val, &j, s, &i);
		else
			val[j++] = s[i];
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
		if (ft_isdigit(str[0]))
		{
			mini->redirect->len += 1;
			break ;
		}
		if((ft_isalnum(str[i]) == 0 && str[i] != '_'))
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
	hold = delete_quotes(ft_substr(str, mini->redirect->start, mini->redirect->len), mini, 0, 0);
	return (hold);
}

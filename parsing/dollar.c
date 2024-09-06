/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:23:47 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/06 15:46:28 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int dollar_check(char	**str, int *i, t_mini *mini, int sq)
{
	//char *hold;

	if ((*str)[(*i)] == '$' && ((*str)[(*i) + 1] == ' '
		|| (*str)[(*i) + 1] == '\t' || (*str)[(*i) + 1] == '\0'))
		(*i)++;
	else if((*str)[(*i)] == '$' && ((*str)[(*i) + 1] == 34 || (*str)[(*i) + 1] == 39))
		fill_space(*str, (*i), 1);
	else if((*str)[(*i)] == '$' && sq % 2 == 0)
	{
		dollar_working(mini, str, &(*i));
		return (1);
	}
	return (0);
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

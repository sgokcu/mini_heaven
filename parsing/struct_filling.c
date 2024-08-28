#include "../minishell.h"

void	find_num_redirect(char *args, t_mini *mini, int dq, int sq)
{
	int	i;

	i = 0;
	while (args[i] && (quote_check(args[i], &sq, &dq), 1))
	{
		if (args[i] == '<' && (dq % 2 == 0) && (sq % 2 == 0)
			&& args[i + 1] != '<')
			mini->redirect->input += 1;
		if (args[i] == '>' && (dq % 2 == 0) && (sq % 2 == 0)
			&& args[i + 1] != '>')
			mini->redirect->output += 1;
		if (args[i] == '<' && (dq % 2 == 0) && (sq % 2 == 0)
			&& args[i + 1] == '<')
		{
			mini->redirect->heredoc += 1;
			i++;
		}
		if (args[i] == '>' && (dq % 2 == 0) && (sq % 2 == 0)
			&& args[i + 1] == '>')
		{
			mini->redirect->append += 1;
			i++;
		}
		i++;
	}
}

void	struct_business(t_mini *mini)
{
	mini->redirect = malloc(sizeof(t_redirect));
	mini->redirect->output = 0;
	mini->redirect->input = 0;
	mini->redirect->heredoc = 0;
	mini->redirect->append = 0;
	mini->utils = malloc(sizeof(t_utils));
	mini->utils->d = 0;
	mini->utils->k = 0;
	mini->utils->z = 0;
	mini->utils->l = 0;
	mini->append = NULL;
	mini->output = NULL;
	mini->input = NULL;
	mini->heredoc = NULL;
	mini->cmd = NULL;
	mini->flag_arg = NULL;
	mini->status = NONE;
}

void	take_name(char *args, t_mini *mini)
{
	int	i;

	i = 0;
	mini->redirect->len = 0;
	mini->utils->j = 0;
	mini->utils->dq = 0;
	mini->utils->sq = 0;
	while (args[i] && (args[i] == ' ' || args[i] == '\t'))
	{
		i++;
		mini->utils->j++;
	}
	mini->redirect->start += i;
	while (args[i]
		&& (quote_check(args[i], &mini->utils->sq, &mini->utils->dq), 1))
	{
		if ((mini->utils->dq % 2 == 0 && mini->utils->sq % 2 == 0)
			&& ((args[i] == ' ' || args[i] == '\t')
				|| (args[i] == '<' || args[i] == '>' || args[i] == '|' || args[i] == '$')))
			break ;
		i++;
		mini->utils->j++;
		mini->redirect->len += 1;
	}
}

void	taking_arg_redirect(char *str, t_mini *mini, int sq, int dq)
{
	int	i;

	i = 0;
	struct_business(mini);
	find_num_redirect(str, mini, 0, 0);
	allocate(mini);
	while (str[i] && (quote_check(str[i], &sq, &dq), 1))
	{
		if (str[i] == '<' && str[i + 1] != '<'
			&& (dq % 2 == 0) && (sq % 2 == 0))
			imp(mini, &i, str, 1);
		else if (str[i] == '>' && str[i + 1] != '>'
			&& (dq % 2 == 0) && (sq % 2 == 0))
			imp(mini, &i, str, 2);
		else if (str[i] == '<' && str[i + 1] == '<'
			&& (dq % 2 == 0) && (sq % 2 == 0))
			imp2(mini, &i, str, 3);
		else if (str[i] == '>' && str[i + 1] == '>'
			&& (dq % 2 == 0) && (sq % 2 == 0))
			imp2(mini, &i, str, 4);
		i++;
	}
}

void	imp(t_mini *mini, int *i, char *str, int n)
{
	if (n == 1)
	{
		mini->redirect->start = (*i) + 1;
		take_name(str + ((*i) + 1), mini);
		mini->input[mini->utils->z++] = delete_quotes(ft_substr(str, mini->redirect->start, mini->redirect->len), mini);
		fill_space(str, (*i), mini->utils->j + 1);	
	}
	if (n == 2)
	{
		mini->redirect->start = (*i) + 1;
		take_name(str + ((*i) + 1), mini);
		mini->output[mini->utils->d++] = delete_quotes(ft_substr(str, mini->redirect->start, mini->redirect->len), mini);
		fill_space(str, (*i), mini->utils->j + 1);
	}
}

void	imp2(t_mini *mini, int *i, char *str, int n)
{
	if (n == 3)
	{
		mini->redirect->start = (*i) + 2;
		take_name(str + ((*i) + 2), mini);
		mini->heredoc[mini->utils->k++] = delete_quotes(ft_substr(str, mini->redirect->start, mini->redirect->len), mini);
		fill_space(str, (*i), mini->utils->j + 2);
		i++;
	}
	if (n == 4)
	{
		mini->redirect->start = (*i) + 2;
		take_name(str + ((*i) + 2), mini);
		mini->append[mini->utils->l++] = delete_quotes(ft_substr(str, mini->redirect->start, mini->redirect->len), mini);
		fill_space(str, (*i), mini->utils->j + 2);
		i++;
	}
}
void	fill_space(char *str, int start, int len)
{
	int	s;

	s = 0;
	while (len > s)
	{
		str[start] = ' ';
		start++;
		s++;
	}
}

void	allocate(t_mini *mini)
{
	if (mini->redirect->input != 0)
	{
		mini->input = malloc(sizeof(char *) * (mini->redirect->input + 1));
		mini->input[mini->redirect->input] = NULL;
		if (!mini->input)
			perror ("Malloc!\n");
	}
	if (mini->redirect->output != 0)
	{
		mini->output = malloc(sizeof(char *) * (mini->redirect->output + 1));
		mini->output[mini->redirect->output] = NULL;
		if (!mini->output)
			perror ("Malloc!\n");
	}
	allocate_continue(mini);
}

void allocate_continue(t_mini *mini)
{
	if (mini->redirect->heredoc != 0)
	{
		mini->heredoc = malloc(sizeof(char *) * (mini->redirect->heredoc + 1));
		mini->heredoc[mini->redirect->heredoc] = NULL;
		if (!mini->heredoc)
			perror ("Malloc!\n");
	}
	if (mini->redirect->append != 0)
	{
		mini->append = malloc(sizeof(char *) * (mini->redirect->append + 1));
		mini->append[mini->redirect->append] = NULL;
		if (!mini->append)
			perror ("Malloc!\n");
	}
}

char	*delete_quotes(char *str, t_mini *mini)
{
	int		i;
	int		j;
	char	*hold;

	i = 0;
	mini->utils->dq = 0;
	mini->utils->sq = 0;
	while (str[i] && (quote_check(str[i], &mini->utils->sq, &mini->utils->dq), 1))
		i++;
	j = ft_strlen(str) - (mini->utils->sq + mini->utils->dq);
	hold = malloc(sizeof(char) * (j + 1));
	if (!hold)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i] && (quote_check(str[i], &mini->utils->sq, &mini->utils->dq), 1))
	{
		if ((str[i] == 39 && mini->utils->dq % 2 == 0) || (str[i] == 34 && mini->utils->sq % 2 == 0))
			i++;
		else
			hold[j++] = str[i++];
	}
	hold[j] = '\0';
	free(str);
	return (hold);
}

void	print_arg(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->arg)
		printf("arg:-%s-\n", mini->arg);
	while (mini->input && mini->input[i])
	{
		printf("input:-%s-\n", mini->input[i]);
		i++;
	}
	i = 0;
	while (mini->output && mini->output[i])
	{
		printf("output:-%s-\n", mini->output[i]);
		i++;
	}
	i = 0;
	while (mini->heredoc && mini->heredoc[i])
	{
		printf("heredoc:-%s-\n", mini->heredoc[i]);
		i++;
	}
	i = 0;
	while (mini->append && mini->append[i])
	{
		printf("append:-%s-\n", mini->append[i]);
		i++;
	}
	printf("status: -%d-\n", mini->status);
	printf("command: -%s-\n", mini->cmd);
	printf("flag_arg: -%s-\n", mini->flag_arg);
}

int is_quotes_closed(char *str)
{
	int i;
	int sq;
	int dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i] && (quote_check(str[i], &sq, &dq), 1))
		i++;
	if(sq % 2 != 0 || dq % 2 != 0)
	{
		printf("dquotes!\n");
		g_global_exit = 258;
		return (0);
	}
	return (1);
}

int is_valid_name(char *str, t_mini *mini)
{
	int i;
	int sq;
	int dq;
	char *tmp;

	sq = 0;
	dq = 0;
	i = 0;
	while (str[i] && (quote_check(str[i], &sq, &dq), 1))
	{
		if (str[i] == '<' && str[i + 1] != '<'
			&& (dq % 2 == 0) && (sq % 2 == 0))
			{
				mini->redirect->start = i + 1;
				take_name(str + i + 1, mini);
				tmp =  ft_substr(str, mini->redirect->start, mini->redirect->len);
				if(tmp[0] == '\0')
				{
					free(mini->redirect);
					free(mini->utils);
					free(tmp);
					printf("minishell: syntax error near unexpected token `newline'\n");
					return (0);
				}
			}
		else if (str[i] == '>' && str[i + 1] != '>'
			&& (dq % 2 == 0) && (sq % 2 == 0))
			{
				mini->redirect->start = i + 1;
				take_name(str + i + 1, mini);
				tmp =  ft_substr(str, mini->redirect->start, mini->redirect->len);
				if(tmp[0] == '\0')
				{
					free(mini->redirect);
					free(mini->utils);
					free(tmp);
					printf("minishell: syntax error near unexpected token `newline'\n");
					return (0);
				}
			}
		else if (str[i] == '<' && str[i + 1] == '<'
			&& (dq % 2 == 0) && (sq % 2 == 0))
			{
				mini->redirect->start = i + 2;
				take_name(str + i + 2, mini);
				tmp =  ft_substr(str, mini->redirect->start, mini->redirect->len);
				if(tmp[0] == '\0')
				{
					free(mini->redirect);
					free(mini->utils);
					free(tmp);
					printf("minishell: syntax error near unexpected token `newline'\n");
					return (0);
				}
			}
		else if (str[i] == '>' && str[i + 1] == '>'
			&& (dq % 2 == 0) && (sq % 2 == 0))
			{
				mini->redirect->start = i + 2;
				take_name(str + i + 2, mini);
				tmp =  ft_substr(str, mini->redirect->start, mini->redirect->len);
				if(tmp[0] == '\0')
				{
					free(mini->redirect);
					free(mini->utils);
					free(tmp);
					printf("minishell: syntax error near unexpected token `newline'\n");
					return (0);
				}
			}
		i++;
	}
	return (1);
}

int pipe_check(char *str)
{
	int i;
	int control;
	i = 0;
	control = 0;
	while(str[i])
	{
		while (str[i] && str[i] != '|')
		{
			if(str[i] == '<' || str[i] == '>')
				control = 0;
			else if(str[i] != ' ' && str[i] != '\t' )
				control = 1;
			i++;
		}
		if(str[i] == '|' && control == 0)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			g_global_exit = 258;
			return (0);
		}
		else if(str[i] == '|' && str[i + 1] != '\0')
		{
			i++;
			control = 0;
			continue ;
		}
		else if(str[i] == '\0' && control == 1)
			return (1);
		else
		{
			g_global_exit = 258;
			printf("minishell: syntax error near unexpected token `|'\n");
			return (0);
		}
	}
	return (1);
}

void take_cmd(char *str, t_mini *mini)
{
	mini->redirect->start = 0;
	take_name(str , mini);
	mini->cmd = delete_quotes(ft_substr(str, mini->redirect->start, mini->redirect->len), mini);
	fill_space(str, mini->redirect->start, mini->redirect->len);
}


void	placing(char **args, t_mini *mini)
{
	int		i;
	t_mini	*temp;

	i = 0;
	temp = mini;
	while (args[i])
	{
		if (!args[i][0])
			return ;
		mini->arg = ft_strdup(args[i]);
		taking_arg_redirect(args[i], mini, 0, 0);
		take_cmd(args[i], mini);
		if (check_same(mini->cmd, "export") && check_same(mini->cmd, "unset"))
			args[i] = delete_quotes(args[i], mini);
		take_flag_arg(mini, args[i]);
		status_regulator(mini, 0, 0, 0);
		//print_arg(mini);
		if (args[i + 1])
		{
			status_regulator_pipe(mini);
			mini->next = malloc(sizeof(t_mini));
			mini->next->env = mini->env;
			mini = mini->next;
		}
		mini->next = NULL;
		i++;
	}
	mini = temp;
}

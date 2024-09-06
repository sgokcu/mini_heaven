/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:23:49 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/06 17:01:47 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int pipe_control(char *str, int *i, int *control)
{
	if(str[(*i)] == '|' && (*control) == 0)
	{
		g_global_exit = 258;
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	else if(str[(*i)] == '|' && str[(*i) + 1] != '\0')
	{
		(*i)++;
		(*control) = 0;
		return (2);
	}
	else if(str[(*i)] == '\0' && (*control) == 1)
		return (1);
	else
	{
		g_global_exit = 258;
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
}

int pipe_check(char *str)
{
	int i;
	int control;
	int s;

	i = 0;
	control = 0;
	while(str[i])
	{
		pipe_while(str, &i, &control);
		s = pipe_control(str, &i, &control);
		if (s == 0)
			return (0);
		else if(s == 2)
			continue ;
		else if(s == 1)
			return (1);
	}
	return (1);
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
			args[i] = delete_quotes(args[i], mini, 0, 0);
		take_flag_arg(mini, args[i]);
		status_regulator(mini, 0, 0, 0);
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

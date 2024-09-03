/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:23:54 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/03 19:03:19 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global_exit;

int	main()
{
	char	**args;
	char	*temp;
	char	*temp2;
	char	*temp3;
	t_mini	mini;

	mini.env = 0;
	g_global_exit = 0;
	take_env(&mini);
	while (1)
	{
		ft_signal_regulator(MAIN_P);
		temp = readline("minishell> ");
		if (!temp)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(temp);
		temp2 = ft_strtrim(temp, " \t");
		free(temp);
		if (!temp2[0])
			continue;
		if (!is_quotes_closed(temp2))
			continue ;
		ft_signal_regulator(MAIN_P2);
		if (!pipe_check(temp2))
			continue ;
		if (!is_valid_name(temp2, &mini))
			continue ;
		temp3 = is_dollar_exist_and_valid(temp2, &mini);
		if (!temp3 || !temp3[0])
		{
			free (temp3);
			continue;
		}
		args = mm_split(temp3, '|');
		placing(args, &mini);
		read_and_exec(&mini, command_list_count(&mini));
	}
}

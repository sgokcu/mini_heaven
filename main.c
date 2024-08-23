#include "minishell.h"

int	g_global_exit;

int	main()
{
	char	**args;
	char	*temp;
	char	*temp2;
	t_mini	mini;

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
		ft_signal_regulator(MAIN_P2);
		if (!is_quotes_closed(temp2))
			continue ;
		is_dollar_exist_and_valid(temp2, &mini);
		if (!pipe_check(temp2))
			continue ;
		if (!is_valid_name(temp2, &mini))
			continue ;
		args = mm_split(temp2);
		placing(args, &mini);
		read_and_exec(&mini, command_list_count(&mini));
	}
}

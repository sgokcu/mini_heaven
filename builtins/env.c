#include "../minishell.h"

void	print_env(t_mini *mini, int status)
{
	int	i;

	i = 0;
	if (!mini->env)
		return ;
	while (mini->env[i])
	{
		if (status == 1)
			printf("declare -x ");
		printf("%s\n", mini->env[i]);
		i++;
	}
}

#include "minishell.h"

int	count_environ(char **environ)
{
	int	i;

	i = 0;
	if (!environ)
		return (0);
	while (environ[i])
		i++;
	return (i);
}

void	take_env(t_mini *mini)
{
	extern char	**environ;
	int			i;

	mini->env = malloc(sizeof(char *) * (count_environ(environ) + 1));
	i = 0;
	while (environ[i])
	{
		mini->env[i] = ft_strdup(environ[i]);
		i++;
	}
}

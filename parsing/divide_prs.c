#include "../minishell.h"

void	quote_check(char temp, int *squotes, int *dquotes)
{
	if (temp == 34 && *squotes % 2 == 0)
		(*dquotes)++;
	if (temp == 39 && *dquotes % 2 == 0)
		(*squotes)++;
}

int	pp_counter(char *temp, int squotes, int dquotes, char c)
{
	int	i;
	int	d;

	d = 0;
	i = -1;
	while (temp[++i] && (quote_check(temp[i], &squotes, &dquotes), 1))
		if (temp[i] == c && (dquotes % 2 == 0 && squotes % 2 == 0))
			d++;
	d++;
	return (d);
}

void	sub(char *temp,char ***ret, char c)
{
	int		i;
	int		j;
	int		d;
	int		squotes;
	int		dquotes;
	char	*tmp;

	i = 0;
	j = 0;
	d = 0;
	squotes = 0;
	dquotes = 0;
	while (temp[i] && (quote_check(temp[i], &squotes, &dquotes), 1))
	{
		if (temp[i] == c && (dquotes % 2 == 0 && squotes % 2 == 0))
		{
			tmp = ft_substr(temp, d, i - d);
			(*ret)[j] = ft_strtrim(tmp, " \t");
			free(tmp);
			j++;
			d = i + 1;
		}
		i++;
	}
	tmp = ft_substr(temp, d, i - d);
	(*ret)[j++] = ft_strtrim(tmp, " \t");
	free(tmp);
	(*ret)[j] = NULL;
}

char	**mm_split(char *temp, char c)
{
	char	**ret;

	ret = malloc(sizeof(char *) * (pp_counter(temp, 0, 0, c) + 1));
	if (!ret)
		return (NULL);
	sub(temp, &ret, c);
	free(temp);
	return (ret);
}

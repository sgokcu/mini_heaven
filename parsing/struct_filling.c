
#include "../minishell.h"

/*

< a.txt < b.txt ls > c.txt >> d.txt -l arg

ls -l arg


< a.txt < b.txt -l

a.txt -l

*/

void find_num_redirect(char *args, t_mini   *mini, int dq, int sq)
{
    int i;
   
    i = 0;
    mini->redirect = malloc(sizeof(t_redirect));
    mini->redirect->output = 0;
    mini->redirect->input = 0;
    mini->redirect->heredoc = 0;
    mini->redirect->append = 0;
    while(args[i] && (quote_check(args[i], &sq, &dq), 1))
    {
        if(args[i] == '<' && (dq % 2 == 0) && (sq % 2 == 0) && args[i + 1] != '<')
            mini->redirect->input += 1;
        if(args[i] == '>' && (dq % 2 == 0) && (sq % 2 == 0) && args[i + 1] != '>')
            mini->redirect->output += 1;
        if(args[i] == '<' && (dq % 2 == 0) && (sq % 2 == 0) && args[i + 1] == '<')
        {
            mini->redirect->heredoc += 1;
            i++;
        }
        if(args[i] == '>' && (dq % 2 == 0) && (sq % 2 == 0) && args[i + 1] == '>')
        {
            mini->redirect->append += 1;
            i++;
        }
        i++;
    }
}
//ls < "a.t>xt" > b.txt!!!!!!!!!

void take_name(char *args, t_mini *mini)
{
    int i;
	int j;
	
    i = 0;
	j = 0;
    mini->redirect->len = 0;
    while(args[i] && (args[i] == ' ' || args[i] == '\t'))
	{
        i++;
		j++;
	}
    mini->redirect->start += i;
    while(args[i] && args[i] != ' ' && args[i] != '\t' && args[i] != '<' && args[i] != '>')
    {
        i++;
		j++;
        mini->redirect->len += 1;
    }
}

void taking_arg_redirect(char *str, t_mini *mini)
{
    int i;
    
	i = 0;
    mini->utils = malloc(sizeof(t_utils));
	mini->utils->d = 0;
	mini->utils->k = 0;
	mini->utils->z = 0;
	mini->utils->l = 0;

    find_num_redirect(str, mini, 0, 0);
    allocate(mini);
    while(str[i] && (quote_check(str[i], 0, 0), 1))
    {
        if(str[i] == '<' && str[i + 1] != '<')
        {
            mini->redirect->start = i + 1;
            take_name(str + (i + 1), mini);
            mini->input[mini->utils->z++] = ft_substr(str, mini->redirect->start, mini->redirect->len);
			fill_space(str, i, mini->redirect->len + 1);
        }
        else if(str[i] == '>' && str[i + 1] != '>')
        {
            mini->redirect->start = i + 1;
            take_name(str + (i + 1), mini);
            mini->output[mini->utils->d++] = ft_substr(str, mini->redirect->start, mini->redirect->len);
			fill_space(str, i, mini->redirect->len + 1);

        }
        else if(str[i] == '<' && str[i + 1] == '<')
        {
            mini->redirect->start = i + 2;
            take_name(str + (i + 2), mini);
            mini->heredoc[mini->utils->k++] = ft_substr(str, mini->redirect->start, mini->redirect->len);
			fill_space(str, i, mini->redirect->len + 2);
            i++;
        }
        else if(str[i] == '>' && str[i + 1] == '>')
        {
            mini->redirect->start = i + 2;
            take_name(str + (i + 2), mini); //burada ayarlanmış ismin içerisinde tırnaklar da olabileceği için, tırnak silme fonksiyonunu çalıştırdıktan sonra struct yapısına o ismi atamak gerekiyor.
            mini->append[mini->utils->l++] = ft_substr(str, mini->redirect->start, mini->redirect->len);
			fill_space(str, i, mini->redirect->len + 2);
            i++;
        }
		printf("%s\n", str);
        i++;
    }
}

void fill_space(char *str, int start, int len)
{
	int s;
	
	s = 0;
	while(len > s)
	{
		str[start] = ' ';
		start++;
		s++;
	}
}



void allocate(t_mini *mini)
{
    if (mini->redirect->input != 0)
    {
        mini->input = malloc(sizeof(char *) * (mini->redirect->input + 1));
        if (!mini->input)
            perror ("Malloc!\n");
    }
    if (mini->redirect->output != 0)
    {
        mini->output = malloc(sizeof(char *) * (mini->redirect->output + 1));
        if(!mini->output)
            perror ("Malloc!\n");
    }
    if (mini->redirect->heredoc != 0)
    {
        mini->heredoc = malloc(sizeof(char *) * (mini->redirect->heredoc + 1));
        if(!mini->heredoc)
            perror ("Malloc!\n");
    }
    if (mini->redirect->append != 0)
    {
        mini->append = malloc(sizeof(char *) * (mini->redirect->append + 1));
        if(!mini->append)
            perror ("Malloc!\n");
    }
}
void placing(char **args, t_mini *mini)
{
    int i;
    t_mini *temp;

    i = 0;

    temp = mini;
    while(args[i])
    {
        taking_arg_redirect(args[i], mini);
        if (args[i + 1])
        {
            mini->next = malloc(sizeof(t_mini));
            mini = mini->next;
        }
        mini->next = NULL;
        i++;
    }
    mini = temp;
}

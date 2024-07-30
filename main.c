#include "minishell.h"

int main()
{
    char    **args;
    char    *temp;
    char    *temp2;
    t_mini  mini;

    take_env(&mini);
    while(1)
    {
        temp = readline("minishell> ");
        add_history(temp);
        temp2 = ft_strtrim(temp, " \t");
        free(temp);
        args = mm_split(temp2);
        placing(args, &mini);
       
    }
}

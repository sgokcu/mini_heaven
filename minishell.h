#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"


typedef struct s_redirect
{
    int input;
    int output;
    int heredoc;
    int append;
    int start;
    int len;
}   t_redirect;

typedef struct s_mini
{
    char *arg;
    char **env;
    char **input;
    char **output;
    char **heredoc;
    char **append;
    struct s_mini *next;
    struct s_redirect *redirect;
}   t_mini;

void    take_env(t_mini *mini);
char    **mm_split(char *temp);
void    placing(char **args, t_mini *mini);
void    print_env(t_mini *mini, int status);
void    quote_check(char temp, int *squotes, int *dquotes);



#endif
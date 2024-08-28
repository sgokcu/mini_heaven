#include "../minishell.h"

void    ft_free_struct(t_mini *mini)
{
    while (mini)
    {
        if (mini->cmd)
            free(mini->cmd);
        if (mini->flag_arg)
            free(mini->flag_arg);
        if (mini->input)
            ft_free_dp(mini->input);
        if (mini->append)
            ft_free_dp(mini->append);
        if (mini->output)
            ft_free_dp(mini->output);
        if (mini->heredoc)
            ft_free_dp(mini->heredoc);
        if (mini->arg)
        {
            free(mini->arg);
            mini->arg = NULL;
        }
        struct_business(mini);
        mini = mini->next;
    }
}

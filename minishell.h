#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "lib/libft/libft.h"

# define NONE 0
# define HEREDOC 1
# define APPEND 2
# define HEREDOCAPPEND 3
# define PIPE 4
# define PIPEHEREDOC 5
# define PIPEAPPEND 6
# define PIPEHEREDOCAPPEND 7
# define BUILTIN 8
# define CHILD_P 9
# define MAIN_P 10
# define HEREDOC_P 11
# define MAIN_P2 12

extern int	g_global_exit;

typedef struct s_redirect
{
	int	input;
	int	output;
	int	heredoc;
	int	append;
	int	start;
	int	len;
}	t_redirect;

typedef struct s_utils
{
	int	dq;
	int	sq;
	int	z;
	int	d;
	int	k;
	int	l;
	int	j;
}	t_utils;

typedef struct s_mini
{
	int					status;
	pid_t				pid;
	char				*cmd;
	char				*flag_arg;
	char				*arg;
	char				**env;
	char				**input;
	char				**output;
	char				**heredoc;
	char				**append;
	struct s_mini		*next;
	struct s_redirect	*redirect;
	struct s_utils		*utils;
}	t_mini;

void		take_env(t_mini *mini);
char		**mm_split(char *temp, char c);
void		placing(char **args, t_mini *mini);
void		quote_check(char temp, int *squotes, int *dquotes);
void		allocate(t_mini *mini);
void		allocate_continue(t_mini *mini);
void		fill_space(char *str, int start, int len);
char		*delete_quotes(char *str, t_mini *mini, int i, int j);
char		**ft_split(char const *s, char c);
void		imp2(t_mini *mini, int *i, char *str, int n);
void		imp(t_mini *mini, int *i, char *str, int n);
int			is_quotes_closed(char *str);
int			is_valid_name(char *str, t_mini *mini, int sq, int dq);
int			pipe_check(char *str);
char		*is_dollar_exist_and_valid(char *str, t_mini *mini);
void		take_name(char *args, t_mini *mini);
char		*dollar_business(char *str, t_mini *mini, int *i);
void		take_name_for_dollar(char *str, t_mini *mini);
void		struct_business(t_mini *mini);
char		*env_contains(char *str, t_mini *mini);
char		*val_redirect(char *str, t_mini *mini, int i, int j);
void		ft_export(t_mini *mini);
int			count_environ(char **environ);
void		put_env(char *str, t_mini *mini);
int			env_count_full(t_mini *mini);
void		free_env(char **envi);
void		take_name_for_export(char *str, t_mini *mini);
char		*export_business(char *str, t_mini *mini);
int			does_env_have(char *str, t_mini *mini);
void		ft_env(t_mini *mini, int status);
void		ft_unset(t_mini *mini);
void		ft_start_exp(t_mini *mini);
int			count_unsets(char **str, t_mini *mini, int i);
void		cmp_env(char **str, char **envi, t_mini *mini, int count);
void		dollar_working(t_mini *mini, char **str, int *i);







//benim eklediklerim
void		take_flag_arg(t_mini *mini, char *str);
void		status_regulator(t_mini *mini, int i, int sq, int dq);
void		status_regulator_pipe(t_mini * mini);
void		append_status_regulator(t_mini *mini, int type);
void		heredoc_status_regulator(t_mini *mini, int type);
void		run_cmd(t_mini *mini, char **command);
char		*get_cmd_path(t_mini *mini, char **command, char **path, int i);
void		heredoc_status_regulator(t_mini *mini, int type);
void		append_status_regulator(t_mini *mini, int type);
void		ft_executer(t_mini *mini, char **command, int i, int fd[2]);
void		read_and_exec(t_mini *mini, int i);
char		**execve_command(t_mini *temp, char **temp2);
void		child_procces(t_mini *mini, char **command, int i);
void		wait_child(t_mini *mini);
void		execute_pipe(t_mini *mini, char **command, int i);
void		ft_free_dp(char **str);
void		duplicate_default_fd(int fd[2]);
void		close_duplicate_fd(int fd[2]);
void		pipe_checker(int fd[2]);
int			command_list_count(t_mini *mini);

void		onecommand_output_input_regulator(t_mini *mini, int i, int sq, int dq);
void		output_input_regulator(t_mini *mini, int i, int fd[2]);
int			output_input(t_mini *mini, int i, int sq, int dq);
int			output_append_checker(t_mini *mini);
int			if_input(t_mini *mini, int j, int sq, int dq);
int			if_heredoc(t_mini *mini, int j, int sq, int dq);
int			if_output(t_mini *mini, int j, int sq, int dq);
int			if_append(t_mini *mini, int j, int sq, int dq);
int			ft_open_output(t_mini *mini, int i);
int			ft_open_append(t_mini *mini, int i);
int			ft_open_input(t_mini *mini, int i);

int			status_check(t_mini *temp);
void		heredoc_pipe(t_mini *mini, int fd[2]);
void		ft_heredoc(int fd[2], t_mini *mini, int fd_2[2], int i);
int			check_same(char *s1, char *s2);
void		fderror_1(char *str);
void		fderror_2(char *str);
int			ft_isdirectory(const char *str);
int			is_fileordirectory(const char *str);

void		ft_signal_regulator(int status);
void		ft_main_signal(int signal);
void		ft_main_signal2(int signal);
void		ft_heredoc_signal(int signal);

char		*make_lower(char *str);
int			builtin_strcmp(char *s1, char *s2);
void		check_builtin_status(t_mini *mini);
void		check_builtin(t_mini *mini, int i);
void		cd(t_mini *mini, char *newlocation);
int			cd_case1(t_mini *mini, char **newlocation, char **newpwd, char *oldpwd);
void		set_newlocation(char *oldpwd, char **newpwd, char *newlocation);
char		*get_oldpwd(t_mini *mini);
int			cd_case2(t_mini *mini, char **newpwd, char **newlocation, char *oldpwd);
char		*get_home(t_mini *mini);
int			chdir_situation(char *newpwd, char *newlocation, char *oldpwd);
void		set_pwd(t_mini *mini, char *oldpwd, char *newpwd);
void		set_newpwd2(char *newpwd, char **newpwd2);
void		set_newpwd(t_mini *mini, char *newpwd, char *newpwd2, int i);
void		set_oldpwd(t_mini *mini, char *oldpwd, int i);
void	    pwd();
void    	ft_exit(t_mini *mini, int i);
int			ft_isnumeric(char *str);
int			ft_arg_count(char **str);
int			exit_with_arg(t_mini *mini, int j, char **arg);
void		exit_with_error(t_mini *mini, char **arg);
void		ft_echo(t_mini *mini);
void		echo_with_arg(t_mini *mini);
void		echo_flag_control(char **arg, int *i);
int			flag_control(char *arg);
int			execute_error(char *command, int i);
void		ft_free_struct(t_mini *mini);



#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:46:15 by tacarlen          #+#    #+#             */
/*   Updated: 2021/10/27 20:30:28 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "libft/libft.h"

typedef struct s_vector
{
	int	x1;
	int	x2;
}				t_vector;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}				t_env_list;

typedef struct s_redirect
{
	char		*file;
	int			type;
}				t_redirect;

typedef struct s_command_block
{
	t_redirect	*redirects;
	char		**narg;
	char		*last_left_redir;
	char		*last_right_redir;
	int			close_fd1;
	int			close_fd2;
}				t_command_block;

typedef struct s_command_line
{
	int				num_pipes;
	int				**pipes_fd;
	t_command_block	*block;
	char			**path;
	char			**envp;
	t_env_list		*env;
	char			*home;
	int				fd1;
	int				fd0;
	int				error;
	int				mystery;
	char			*dol_que;
}				t_command_line;

void		ft_creat_redirects(t_command_line *all, int index);
int			ft_parser(char *line, t_command_line *all);
char		*ft_start_parser(char *line, t_command_line *all);
int			ft_count_char(const char *str, char c);
int			ft_count_str(char **tmp);
int			ft_parse_block(char *block, t_command_line *all, int index);
int			ft_count_redirs(char **tmp);
void		ft_parse_redirs(char **tmp, t_command_line *all, int index);
void		ft_parse_env(t_command_line *all, char **envp);
void		ft_shlvl(t_env_list *shl);
char		**ft_split_path(char **envp);
void		ft_pro_redirs(t_command_line *all, int index);
int			ft_free_tmp(char **tmp);

int			ft_minishell(t_command_line *all);
int			ft_start_fork(t_command_line *all);
int			ft_command_block(t_command_line *all, int index);
int			ft_make_command(t_command_line *all, t_command_block *block);
void		ft_dup_or_close_pipes(t_command_line *all, int index);
void		ft_close_pipe_fds(t_command_line *all, int index);
int			ft_create_redir_files(t_command_block *block);
int			ft_open(t_command_block *block, int i, char *file);
int			ft_unlink(char *name);
int			ft_redirect2(char *key, char *index);
int			ft_last_redir(t_redirect redirect, int type, \
								t_command_block *block);
void		ft_exec(char **path, char **narg, char **envp, t_command_line *all);
void		ft_just_do_it(char **narg, char **envp);
int			ft_one_time_cmd(t_command_line *all, t_command_block *block);
char		*ft_strcat(char *dest, const char *src);
int			ft_error(char *str1, char *str2, char *str3);
int			ft_last_len(char *str);
int			ft_fd_error(char *filename);

int			ft_crutch(char **tmp);
int			ft_zero(char *buffer, int i);
void		ft_free(char ***remain);
int			ft_result(int status);
int			ft_check_remain(char ***line, char **remain);
int			get_next_line(int fd, char **line);
void		*ft_calloc(size_t number, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_dup(const char *str);
int			ft_nsymbol(char *str);
char		*ft_strjon(char *s1, char *s2);

int			ft_check_for_ft_hand(char *tmp);
int			ft_exit(t_command_line *all, t_command_block *block);
void		ft_exit0(t_command_line *all);
int			ft_exit_status(char *str);
int			ft_digit(char *str);
int			ft_pwd(void);
void		ft_echo(t_command_block *block);

int			ft_cd(t_command_line *all, t_command_block *block);
int			ft_oldpwd(t_command_line *all);
int			ft_home(t_command_line *all, t_env_list *home);
t_env_list	*ft_find_env(t_command_line *all, char *str);
int			ft_minus(t_command_line *all, t_env_list *old);
char		*ft_copy(char *path);
int			ft_change_pwd(t_command_line *all);
int			ft_change_dir(t_command_line *all, char *path);
void		ft_free_unlink(t_command_line *all);
int			ft_findarg(char **str, t_env_list *tmp);
void		ft_env(t_command_line *all, t_command_block *block);
void		ft_print_env(t_env_list *env);
int			ft_find_sym(char *str, char c);

int			ft_unset(t_command_line *all, t_command_block *block);
int			ft_delete(char *var, t_command_line *all, int cmp, char *var1);
int			ft_del1(t_command_line *all);

int			ft_strcmp(const char *s1, const char *s2);
int			ft_check_export(char *str);
char		**ft_vk(char *str);
void		ft_append_env(t_command_line *all, char *str);
char		*ft_export_val(char *str);
int			ft_export(t_command_line *all, t_command_block *block);
void		ft_navi(t_command_line *all, char *str);
t_env_list	*ft_find_export(t_command_line *all, char *str);
void		ft_change_env(t_env_list *tmp, char *str);
void		ft_export_print(t_env_list *env);
t_env_list	*ft_dup_env(t_env_list *env);
void		ft_env_sort(t_env_list *env);
void		ft_free_env(t_env_list *env);
int			ft_add_export(char *str);

void		ft_free_all(t_command_line *all);

int			ft_pipes_count(char *line);
int			ft_iterations(char *str, char c);
int			ft_find_end_block(char *line, int index);
char		**ft_split_line(char *line, t_command_line *all);
int			ft_count_args(char *s, int i);
int			ft_skip_redirs(char *s, int *count);
int			ft_skip_spaces(char *s);
int			ft_start_count_args(char *s);
int			ft_find_end_arg(char *s, int i, int count, int index);
char		**ft_split_block(char *block, t_command_line *all);
void		ft_update_shlvl(char **envp);
void		ft_parse_envp(t_command_line *all, char **en);

void		rl_replace_line(const char *text, int clear_undo);
t_env_list	*ft_find_export(t_command_line *all, char *str);
char		*ft_preparser(char *line);
int			ft_check_quote(char *line, char sym, int i);
int			ft_free_buf(int er, int *buf_pid);

char		**ft_hand_redirs(char **tmp);

int			ft_ft(char **str, t_command_line *all);
int			ifkey(char c);
int			ft_dollar(char **line, int *i, t_command_line *all);

void		sig(int signum);

#endif
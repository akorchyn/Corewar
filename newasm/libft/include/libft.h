/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:21:05 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/23 17:37:12 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** Inclusions of the standart libraries.
*/

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

/*
** BUFF_SIZE macro(for get_next_line).
*/

# define BUFF_SIZE 256

/*
** Defines for standart output modification.
*/

# define BOLD "\x1b[1m"
# define UNDERLINED "\x1b[4m"
# define BLINK "\x1b[5m"
# define INVERT "\x1b[7m"
# define BLACK "\x1b[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define PINK "\x1b[35m"
# define AQUA "\x1b[36m"
# define WHITE "\x1b[37m"

/*
** Macro for end of standart output modification.
*/

# define EOM "\x1b[0m"

/*
** Some usefull macros.
*/

# define ABS(x) (((x) < 0) ? (-(x)) : (x))
# define MAX(x1, x2) (x1 > x2) ? x1 : x2
# define MIN(x1, x2) (x1 > x2) ? x2 : x1
# define ULL unsigned long long

/*
** Data conversion types.
*/

# define CHAR 0
# define STRING 1
# define POINTER 2
# define DECIMAL 3
# define OCTAL 4
# define UINT 5
# define SMALL_HEX 6
# define BIG_HEX 7
# define PERCENTAGE 8
# define BINARY 9
# define FLOAT 10
# define NO_TYPE 11

/*
** Universal list structure.
*/

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

/*
** List-structure and structure with variable for get_next_line.
*/

typedef struct			s_vars
{
	int					i;
	int					ret;
	char				*buf;
	char				*new_buf;
	char				*endl;
}						t_vars;

typedef struct			s_gnlist
{
	char				*buff;
	char				*ret_buf;
	int					fd;
	struct s_gnlist		*next;
}						t_gnlist;

/*
** Structure t_flags for flags in ft_printf.
*/

typedef struct			s_flags
{
	unsigned int		sharp : 1;
	unsigned int		space : 1;
	unsigned int		plus : 1;
	unsigned int		minus : 1;
	unsigned int		big_longness : 1;
}						t_flags;

/*
** Structure t_printf for modificators inf ft_printf.
*/

typedef	struct			s_printf
{
	int					width;
	int					accurace;
	int					size;
	char				zero;
	unsigned int		type;
	t_flags				*flags;
}						t_printf;

/*
** Libft functions' prototypes.
*/

t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst,
							void (*del)(void *, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstadd_sorted(t_list **alst, t_list *new,
	int (*cmp)(t_list *lst, t_list *new));
void					ft_lstadd_end(t_list **head, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memccpy(void *dst, const void *src,
							int c, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memchr(const void *s, int c, size_t n);
size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *s1);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strncpy(char *dst, const char *src, size_t len);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
char					*ft_strncat(char *s1, const char *s2, size_t n);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strrchr(const char *s, int c);
char					*ft_strchr(const char *s, int c);
char					*ft_strnchr(const char *s, int c, size_t n);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
char					*ft_stralloc(size_t size);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *str);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s,
							char (*f)(unsigned int, char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1,
							char const *s2, size_t n);
char					*ft_strsub(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, char c);
char					*ft_itoa(int n);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
char					*ft_itoa10(__uint128_t nb);
void					ft_putnbr_fd(int n, int fd);
int						ft_is_whitespace(const char *str);
int						ft_list_size(t_list *begin_list);
void					ft_cycle_move(void *content, size_t content_size,
							int size, int distance);
void					ft_reverse(void *content, size_t content_size,
							size_t size);
t_list					*ft_lstfind(t_list *head, void *data,
							int (*content_cmp)(void*, void*));
int						ft_isnumeric(char *str);

/*
** get_next_line's function prototype.
*/

int						get_next_line(const int fd, char **line);

/*
** ft_printf functions' prototypes;
*/

void					parse_flag(t_printf *info, char **pointer);
void					parse_size(t_printf *info, char **pointer);
void					parse_type(t_printf *info, char **pointer);
void					parse_nbr(t_printf *info, char **p, va_list *ap);
int						stop_conversion(char c);
int						is_conversion_type(char c);
char					*ft_itoa_for_printf(char *base,
							__int128 nb, t_printf *info);
int						print_char(t_printf *info, void *data);
int						print_percent(t_printf *info);
int						print_pointer(t_printf *info, void *data);
int						print_string(t_printf *info, void *data);
int						print_decimal(t_printf *info, void *data);
int						print_numeric(t_printf *info, void *data);
int						print_float(t_printf *info, float data);
int						print_double(t_printf *info, long double data);
int						ft_printf(const char *format, ...);

#endif

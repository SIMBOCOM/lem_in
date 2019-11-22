/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:28:09 by flogan            #+#    #+#             */
/*   Updated: 2019/11/19 19:02:01 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "get_next_line.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

char				*ft_strlowcase(char *str);
char				*ft_strupcase(char *str);
int					ft_isspace(int ch);
int					ft_islower(int ch);
int					ft_isupper(int ch);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr(int n);
void				ft_putendl(char const *s);
void				ft_putstr(char const *s);
void				ft_putchar(char c);
char				*ft_itoa(int n);
char				**ft_strsplit(char const *s, char c);
char				*ft_strtrim(char const *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strmap(char const *s, char (*f)(char));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
void				ft_striter(char *s, void (*f)(char *));
void				ft_strclr(char *s);
void				ft_strdel(char **as);
char				*ft_strnew(size_t size);
void				ft_memdel(void **ap);
void				*ft_memalloc(size_t size);
int					ft_tolower(int ch);
int					ft_toupper(int ch);
int					ft_isprint(int ch);
int					ft_isascii(int ch);
int					ft_isalnum(int chr);
int					ft_isdigit(int chr);
int					ft_isalpha(int chr);
int					ft_strncmp(const char *string1,
		const char *string2, size_t num);
char				*ft_strnstr(const char *big,
		const char *little, size_t len);
char				*ft_strstr(const char *string1, const char *string2);
char				*ft_strrchr(const char *string, int symbol);
char				*ft_strchr(const char *string, int symbol);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strncat(char *destptr, const char *srcptr, size_t num);
char				*ft_strcat(char *destptr, const char *srcptr);
char				*ft_strncpy(char *destptr, const char *srcptr, size_t num);
int					ft_memcmp(const void *memptr1,
		const void *memptr2, size_t num);
void				*ft_memchr(const void *memptr, int val, size_t num);
void				*ft_memmove(void *destptr,
		const void *srcptr, size_t num);
void				*ft_memccpy(void *destination,
		const void *source, int c, size_t n);
void				*ft_memcpy(void *destination, const void *source, size_t n);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *src);
char				*ft_strcpy(char *dest, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
void				*ft_memset(void *destination, int c, size_t n);
int					ft_atoi(const char *str);

#endif

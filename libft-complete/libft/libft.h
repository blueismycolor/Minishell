/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:47:34 by aeudes            #+#    #+#             */
/*   Updated: 2025/05/12 15:34:20 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include <ctype.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void	*content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_atoi(const char *str);
int		ft_isalpha(int verif);
int		ft_isprint(int verif);
void	*ft_memset(void *pointeur, int value, size_t count);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *arr, int value);
char	*ft_strrchr(const char *str, int searchedChar);
void	ft_bzero(void *s, size_t n);
int		ft_isascii(int verif);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *str);
int		ft_tolower(int letter);
int		ft_isalnum(int verif);
int		ft_isdigit(int verif);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
int		ft_toupper(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp( const void *s1, const void *s2, size_t size );
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	*ft_calloc( size_t elementcount, size_t elementsize );
char	*ft_strdup( const char *str);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strpbrk(const char *s, const char *charset);
char	*ft_strtok(char *str, const char *delim);
char	**ft_extend_array(char **array, const char *new_str);

#endif
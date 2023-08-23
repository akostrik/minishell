/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalimol <akalimol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 12:34:56 by akalimol          #+#    #+#             */
/*   Updated: 2023/05/28 18:04:04 by akalimol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <limits.h>

/* ------------------------------------------------------------------------- */
/* ----------------------- String functions -------------------------------- */
/* ------------------------------------------------------------------------- */

size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *s, const char *need, size_t len);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		**ft_split(char const *s, char c);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));

/* ------------------------------------------------------------------------- */
/* -------------------------------- is checkers ----------------------------- */
/* ------------------------------------------------------------------------- */

int			ft_atoi(const char *str);
char		*ft_itoa(int n);
int			ft_isalpha(int c);
int			ft_isprint(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_isascii(int c);
int			ft_isspace(char c);

/* ------------------------------------------------------------------------- */
/* ---------------------------- Memory allocations ------------------------- */
/* ------------------------------------------------------------------------- */

void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);

/* ------------------------------------------------------------------------- */
/* -------------------------------- Printf --------------------------------- */
/* ------------------------------------------------------------------------- */

int			ft_printf(const char *s, ...);
int			ft_printf2(const char *s, ...);
int			ft_putunbr(unsigned int nbr, int std);
int			ft_putptr(long unsigned int nbr, int std);
int			ft_puthex(unsigned int nbr, char c, int std);
int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(char *s, int fd);
int			ft_putendl_fd(char *s, int fd);
int			ft_putnbr_fd(int n, int fd);

/* ------------------------------------------------------------------------- */
/* ----------------------------- get next line ----------------------------- */
/* ------------------------------------------------------------------------- */

char		*get_next_line(int fd, int to_free);
void		ft_free_array(char **array);

#endif

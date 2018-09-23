#ifndef LIC_H
# define LIC_H

# include <stdio.h>
# include "types.h"
# include "malloc.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_dlist
{
	void			*content;
	size_t			content_size;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

int		atoi(const char *str);
void	bzero(void *s, size_t n);
int		isprint(int c);
int		isascii(int c);
int		isalnum(int c);
int		isdigit(int c);
int		isalpha(int c);
int		iswhitespace(char c);

// unsuported __moddi3 __divd3
// char				*ft_itoa(int n);

void	*memalloc(size_t size);
void	*memchr(const void *s, int c, size_t n);
int		memcmp(const void *s1, const void *s2, size_t n);
void	*memcpy(void *dest, const void *src, size_t n);
void	*memccpy(void *dest, const void *src, int c, size_t n);
void	memdel(void **ap);
void	*memmove(void *dest, const void *src, size_t n);
void	*memset(void *s, int c, size_t n);
char	*strcat(char *dest, const char *src);
char	*strchr(const char *s, int c);
void	strclr(char *s);
int		strcmp(const char *str1, const char *str2);
char	*strcpy(char *dest, const char *src);
void	strdel(char **as);
char	*strdup(const char *s);
int		strequ(char const *s1, char const *s2);
int		strhas(const char *str, char c);
void	striter(char *s, void (*f)(char *));
void	striteri(char *s, void (*f)(unsigned int, char *));
char	*strjoin(char const *s1, char const *s2);
size_t	strlen(const char *s);
size_t	strlcat(char *dest, const char *src, size_t size);
char	*strmap(char const *s, char (*f)(char));
char	*strmapi(char const *s, char (*f)(unsigned int, char));
char	*strncat(char *dest, const char *src, size_t n);
int		strncmp(const char *str1, const char *str2, size_t num);
char	*strncpy(char *dest, const char *src, size_t n);
int		strnequ(const char *s1, const char *s2, size_t n);
char	*strnew(size_t size);
char	*strnstr(const char *haystack, const char *needle, size_t n);
char	*strrchr(const char *s, int c);
char	*strstr(const char *haystack, const char *needle);
char	*strsub(char const *s, unsigned int start, size_t len);
char	*strtrim(const char *s);
char	**strsplit(const char *s, char c);
char	**strssplit(char const *s, const char *sep);
int		tolower(int c);
int		toupper(int c);

t_list	*lstnew(void const *content, size_t content_size);
t_list	*lstnew_nocopy(void *content, size_t content_size);
void	lstdelone(t_list **alst, void (*del)(void *, size_t));
void	lstdel(t_list **alst, void (*del)(void *, size_t));
void	lstadd(t_list **alst, t_list *new_node);
void	lstaddend(t_list **end_node, t_list *new_node);
void	lstaddafter(t_list *node, t_list *new_node);
void	lstiter(t_list *lst, void (*f)(t_list *elem));
t_list	*lstmap(t_list *lst, t_list *(*f)(t_list *elem));

t_dlist	*dlist_new(void const *content, size_t content_size);
t_dlist	*dlist_new_no_copy(void *content, size_t content_size);
void	dlist_delete(t_dlist **node, void (*del)(void *, size_t));
void	dlist_delete_more(t_dlist **node, void (*del)(void *, size_t));
void	dlist_add(t_dlist **start_node, t_dlist *new_node);
void	dlist_add_end(t_dlist **end_node, t_dlist *new_node);
void	dlist_add_after(t_dlist *node, t_dlist *new_node);
void	dlist_add_before(t_dlist *node, t_dlist *new_node);
void	dlist_iter(t_dlist *start_node, void (*f)(t_dlist *elem));
void	normal_delete(void *ptr, size_t mem_size);
t_dlist	*dlist_map(t_dlist *lst, t_dlist *(*f)(t_dlist *elem));
void	dlist_ptr_swap(t_dlist **first, t_dlist **second);
void	dlist_swap(t_dlist *first, t_dlist *second);

#endif

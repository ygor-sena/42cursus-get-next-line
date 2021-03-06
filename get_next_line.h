/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:12:25 by yde-goes          #+#    #+#             */
/*   Updated: 2022/07/08 21:41:14 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_line
{
	char			*content;
	int				length;
	struct s_line	*next;
}					t_line;

char	*get_next_line(int fd);

t_line	*ft_lstnew(char *content);

t_line	*ft_lstlast(t_line *lst);

void	ft_lstadd_back(t_line **lst, t_line *new);

void	ft_lstclear(t_line **lst, void (*del)(void *));

void	*ft_calloc(size_t nmemb, size_t size);
#endif

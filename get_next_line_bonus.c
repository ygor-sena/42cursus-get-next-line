/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:12:21 by yde-goes          #+#    #+#             */
/*   Updated: 2022/07/08 20:04:30 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	read_line(t_line **cache, int fd);
static int	is_new_line(t_line *cache);
static void	create_line(t_line *cache, char **line);
static void	refactor_line(t_line **cache);

char	*get_next_line(int fd)
{
	static t_line	*cache[MAX_FD] = {NULL};
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_line(&cache[fd], fd);
	if (!cache[fd])
		return (NULL);
	create_line(cache[fd], &line);
	refactor_line(&cache[fd]);
	return (line);
}

void	read_line(t_line **cache, int fd)
{
	int		output;
	char	*buffer;
	t_line	*new_node;

	output = 0;
	while (!is_new_line(*cache))
	{
		buffer = NULL;
		new_node = ft_lstnew(buffer);
		new_node->content = ft_calloc(sizeof(*buffer), (BUFFER_SIZE + 1));
		output = read(fd, new_node->content, BUFFER_SIZE);
		if (output == 0 || output == -1)
		{
			free(new_node->content);
			free(new_node);
			return ;
		}
		new_node->content[BUFFER_SIZE] = '\0';
		ft_lstadd_back(cache, new_node);
	}
}

int	is_new_line(t_line *cache)
{
	int		i;

	cache = ft_lstlast(cache);
	if (!cache)
		return (0);
	i = 0;
	while (cache->content[i] != '\0')
	{
		if (cache->content[i] == '\n')
		{
			cache->length = ++i;
			return (1);
		}
		i++;
	}
	cache->length = i;
	return (0);
}

void	create_line(t_line *cache, char **line)
{
	int		ln_size;
	int		i;
	t_line	*temp;

	temp = cache;
	ln_size = 0;
	while (temp)
	{
		ln_size = ln_size + temp->length;
		temp = temp->next;
	}
	if (!ln_size)
		return ;
	*line = malloc(sizeof(**line) * (ln_size + 1));
	if (!line)
		return ;
	ln_size = 0;
	while (cache && cache->content)
	{
		i = 0;
		while (cache->content[i] && i < cache->length)
			(*line)[ln_size++] = cache->content[i++];
		cache = cache->next;
	}
	(*line)[ln_size] = '\0';
}

void	refactor_line(t_line **cache)
{
	t_line	*temp;
	t_line	*new_node;
	char	*content;
	int		i;
	int		size;

	size = 0;
	temp = ft_lstlast(*cache);
	if (!temp)
		return ;
	content = temp->content;
	size = temp->length;
	temp->content = NULL;
	ft_lstclear(cache, free);
	i = 0;
	if (content[size] != '\0')
	{
		while (content[size] != '\0')
			content[i++] = content[size++];
		content[i] = '\0';
		new_node = ft_lstnew(content);
		ft_lstadd_back(cache, new_node);
	}
	else
		free(content);
}

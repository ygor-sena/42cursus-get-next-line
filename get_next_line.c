/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:12:21 by yde-goes          #+#    #+#             */
/*   Updated: 2022/07/08 00:24:12 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	read_line(t_line **cache, int fd);
int		is_new_line(t_line *cache);
void	create_line(t_line *cache, char **line);
void	refactor_line(t_line **cache);

char	*get_next_line(int fd)
{
	static t_line	*cache = NULL;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_line(&cache, fd);
	if (!cache)
		return (NULL);
	create_line(cache, &line);
	refactor_line(&cache);
	//free(cache);
	return (line);
}

void	read_line(t_line **cache, int fd)
{
	int		output;
	char	*buffer;
	t_line	*new_node;

	output = 0;
	/* If funcion is 0, then there is no newline. If 1, there is a new line */
	while (!is_new_line(*cache))
	{
		buffer = ft_calloc(sizeof(*buffer), (BUFFER_SIZE + 1));
		//NULL --> read --> -1 
		if (!buffer)
			return ;
		output = read(fd, buffer, BUFFER_SIZE);
		/* Free if EOF (output == 0) or if an error happenned (output == 1) */
		if (output == 0 || output == -1)
		{
			free(buffer);
			return ;
		}
		/* End read buffer string with '\0' */
		buffer[BUFFER_SIZE] = '\0';
		//new_node = ft_lstlast(*cache);
		new_node = ft_lstnew(buffer);
		ft_lstadd_back(cache, new_node);
	}
}

int	is_new_line(t_line *cache)
{
	int		i;
	//t_line	*temp;

	cache = ft_lstlast(cache);
	/* NOTE: If temp is null, then the list wasn't created */
	if (!cache)
		return (0);
	i = 0;
	while (cache->content[i] != '\0') //why?
	{
		if (cache->content[i] == '\n')
		{
			/* Length of temp is until \n */
			cache->length = ++i;
			return (1);
		}
		i++;
	}
	/* Length equals BUFFER_SIZE, there is no \n */
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
	/* Count line size with content lengths */
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
	/* Refactor BUFFER_SIZE with new line. Example: 0000n111\0 --> 0000n111\0 */
	ln_size = 0;
	while (cache && cache->content)
	{
		i = 0;
		while (cache->content[i] && i < cache->length)
		{
			(*line)[ln_size] = cache->content[i];
			ln_size++;
			i++;
		}
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

	/* Get last buffer line (end of line) that has new line */
	size = 0;
	temp = ft_lstlast(*cache);
	if (!temp)
		return ;
	content = temp->content;
	size = temp->length;
	temp->content = NULL; //reference of cache->content is set to NULL
	//temp->length = 0;
	/* Separate temp from list to free without also 
			removing temp content that references the line list */
	ft_lstclear(cache, free);
	i = 0;
	if (content[size] != '\0')
	{
		while (content[size] != '\0')
		{
			content[i] = content[size];
			i++;
			size++;
		}
		content[i] = '\0';
		new_node = ft_lstnew(content);
		ft_lstadd_back(cache, new_node);
	}
	else
		free(content);
} 

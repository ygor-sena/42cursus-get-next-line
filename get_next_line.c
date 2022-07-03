/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:12:21 by yde-goes          #+#    #+#             */
/*   Updated: 2022/07/03 03:31:14 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*search_nl(char *line);

char	*get_next_line(int fd)
{
	static char	*cache = NULL;
	char		*content;
	t_list		*file;
	t_list		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file = NULL;
	// read fd until EOF or error
	if (!cache)
	{
		cache = malloc(sizeof(*cache) * BUFFER_SIZE + 1);
		read(fd, cache, BUFFER_SIZE);
		cache[BUFFER_SIZE] = '\0';
	}	
	content = search_nl(cache);
	//create a node to save read line to a file list
	temp = ft_lstnew(content);
	ft_lstadd_back(&file, temp);
	return (file->content);
}

char	*search_nl(char *line)
{
	size_t	i;
	char	*content;

	content = NULL;
	//TODO: I need a function just to read bytes until \n, like get_nl_size
	i = 0;
	while (line[i] != '\n')
		i++;
	content = malloc((i + 1) * sizeof(*content));
	if (!content)
		return (NULL);
	i = 0;
	//copy line to a temp variable to be added to file list
	while (line[i] != '\n')
	{
		content[i] = line[i];
		i++;
	}
	content[i] = '\0';
	return (content);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 20:41:57 by malu              #+#    #+#             */
/*   Updated: 2019/01/29 20:42:15 by malu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		ft_check_end_line(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

size_t	ft_linesize(const char *str)
{
	size_t size;

	size = 0;
	if (!str)
		return (0);
	while (str[size] && str[size] != '\n')
		size++;
	return (size);
}

char	*ft_strcpy_until(char *dest, const char *src, char c)
{
	int i;

	i = 0;
	while (src[i] || src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcmpcpy(const char *s1, char *s2)
{
	while (s1 && s2)
	{
		if (s1 != s2)
		{
			s1++;
			s2++;
		}
		else
			break ;
	}
	return (s2);
}

int		get_next_line(const int fd, char **line)
{
	static char		*repere = NULL;
	int				ret;
	char			*buff;
	
	ret = 1;
	if (!(buff = ft_memalloc(sizeof(char *) * BUFF_SIZE + 1)))
		return (0);
	if (repere == NULL)
	{
		if (!(repere = ft_memalloc(sizeof(char *) * BUFF_SIZE + 1)))
		return (0);
	}
	else
	{
		if (!(*line = ft_memalloc(sizeof(char *) * BUFF_SIZE + 1)))
			return (0);
		*line = ft_strjoin(*line, repere);
		free(repere);
		if (!(repere = ft_memalloc(sizeof(char *) * BUFF_SIZE + 1)))
		return (0);
	}
	while(ret != 0 && ret != -1)
	{
		ret = read(fd, buff, BUFF_SIZE);
		if (ft_strchr(buff, '\n') != NULL)
				break ;
		else
			repere = ft_strjoin(repere, buff);
	}
	//printf("%s", repere);
	//repere = ft_strjoin(repere, buff);
	free(buff);
	if (*line != NULL)
		free(*line);
	if (*line == NULL)
	{
		if (!(*line = ft_memalloc(sizeof(char *) * BUFF_SIZE + 1)))
			return (0);
	}
	*line = ft_strjoin(*line, repere);
	free(repere);
	//printf("%s", repere);
	//printf("%s", *line);
	ft_putstr(*line);
	//if (line)
	//	ft_putstr(ft_strcpy_until(*line, repere, '\n'));
	if (ret == 1)	
		return (1);
	else if (ret == -1)
		return (-1);
	else
		return (0);
}

int		main(void)
{
	int		fd = open("test.txt", O_RDONLY);
	char	*line = NULL;
	int		ret;
	
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		ft_putchar('\n');
	}
	close(fd);
	return (0);
}

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

char	*ft_strjoinSpecial(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 && s2)
	{
		if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
			return (NULL);
		while (s1[i] != '\0')
		{
			new[i] = s1[i];
			i++;
		}
		while (s2[j] != '\0' && s2[j] != '\n')
		{
			new[i] = s2[j];
			j++;
			i++;
		}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}

char	*ft_strcpyuntilendofline (char *dest, const char *src)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (src[i] != '\0' &&& src[i] != '\n')
		i++;
	j = i;
	while(src[j])
		j++;
	dest = ft_strnew(j);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


int		get_next_line(const int fd, char **line)
{
	static char		*repere = NULL;
	int				ret;
	char			*buff;
	
	ret = 1;
	// init buff
	if (!(buff = ft_memalloc(sizeof(char *) * BUFF_SIZE + 1)))
		return (0);
	// init repere
	if (repere == NULL)
	{
		if (!(repere = ft_memalloc(sizeof(char *) * BUFF_SIZE + 1)))
		return (0);
	}
	else // cp repere in line until /n
	{
		if (!(*line = ft_memalloc(sizeof(char *) * BUFF_SIZE + 1)))
			return (0);
		*line = ft_strjoin(*line, repere);
		free(repere);
		if (!(repere = ft_memalloc(sizeof(char *) * BUFF_SIZE + 1)))
		return (0);
	}
	// read and cp in buff
	while(ret != 0 && ret != -1)
	{
		ret = read(fd, buff, BUFF_SIZE);
		// if \n exist in buff OR EOF cp and break
		if (ft_strchr(buff, '\n') != NULL || ret == 0)
		{
			repere = ft_strjoin(repere, buff);
			break ;
		}
		else // else cp and break only
			repere = ft_strjoin(repere, buff);
	}
	free(buff);
	if (*line == NULL)
	{
		if (!(*line = ft_memalloc(sizeof(char *) * BUFF_SIZE + 1)))
			return (0);
	}
	*line = ft_strjoinSpecial(*line, repere);
	printf("LINE : %s", *line);
	//ft_putstr(*line);
	if (ret > 0)	
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

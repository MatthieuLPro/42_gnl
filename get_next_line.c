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

size_t	ft_strlenline(const char *s1)
{
	size_t i;

	i = 0;
	while(s1[i] != '\n' && s1[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlenlineafter(const char *s1)
{
	size_t i;

	i = 0;
	while(s1[i] != '\n' && s1[i] != '\0')
		i++;
	return (i + 1);
}

char	*ft_strcpyline(char *dest, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strcleanfirstline(char *s1, size_t n)
{
	char	*new;
	size_t	i;
	size_t	temp;

	i = 0;
	temp = ft_strlen(s1);
	if (s1)
	{
		if (!(new = malloc(sizeof(char) * ((ft_strlen(s1) - n) + 1))))
			return (NULL);
		if (s1[i] == '\n')
			n++;
		while(s1[i + n] != '\0')
		{
			new[i] = s1[i + n];
			i++;
		}
		new[i + n] = '\0';
		if (s1[0] == '\n')
			n--;
		if (n != 0)
			return (new);
		else
			free(new);
	}
	return (NULL);
}

char	*ft_strjoinline(char const *s1, char const *s2)
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
		printf("new : %s - s2 : %s\n", new, s2);
		return (new);
	}
	return (NULL);
}

int		get_next_line(const int fd, char **line, size_t buff_size)
{
	static char		*repere = NULL;
	int				ret;
	char			*buff;

	ret = 1;
	// init buff
	if (!(buff = ft_memalloc(sizeof(char *) * buff_size + 1)))
		return (-1);
	// init repere IF NULL
	if (repere == NULL)
	{
		if (!(repere = ft_memalloc(sizeof(char *) * buff_size + 1)))
			return (-1);
	}
	else // IF repere NOT NULL 
	{
		free(*line);
		*line = NULL;
		if (!(*line = ft_memalloc(sizeof(char *) * ft_strlenline(repere) + 1)))
			return (-1);
		*line = ft_strcpyline(*line, repere, ft_strlenline(repere));
		//printf("lineBefore : %s - ", *line);
		if (ft_strcleanfirstline(repere, ft_strlenlineafter(repere)))
			repere = ft_strcleanfirstline(repere, ft_strlenlineafter(repere));
	}
	// read and cp in buff
	while(ret)
	{
		if (!(ret = read(fd, buff, buff_size)))
			break ;
		// if \n exist in buff OR EOF cp and break
		if (ft_strchr(buff, '\n') != NULL || ret == 0)
		{
			repere = ft_strjoin(repere, buff);
			break ;
		}
		repere = ft_strjoin(repere, buff);
	}
	// Free buff if exist
	if (buff)
	{
		free(buff);
		buff = NULL;
	}
	//free(*line);
	//*line = NULL;
	//printf("repere : %s - line repere : %ld\n", repere, ft_strlenline(repere));
	if (*line == NULL)
	{
		// cpy repere into line (until \n) destroy first line of repere
		if (!(*line = ft_memalloc(sizeof(char *) * ft_strlenline(repere) + 1)))
			return (-1);
		*line = ft_strcpyline(*line, repere, ft_strlenline(repere));
		//printf("lineAfter : %s - repere : %s - ", *line, repere);
		if (ft_strcleanfirstline(repere, ft_strlenlineafter(repere)))
			repere = ft_strcleanfirstline(repere, ft_strlenlineafter(repere));
		//printf("repereAFTER : %s - ", repere);
	}
	else
	{
		*line = ft_strjoinline(*line, repere);
		if (ft_strcleanfirstline(repere, ft_strlenlineafter(repere)))
			repere = ft_strcleanfirstline(repere, ft_strlenlineafter(repere));
	}
	//printf("repere : %s - ", repere);
	//*line = ft_strjoinSpecial(*line, repere);
	//printf("LINE : %s", *line);
	//printf("ret : %d\n", ret);
	//printf("line : %s repere : %s - ", *line, repere);
	//ft_putstr(*line);
	//printf("repere: %s - ",repere);
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
	size_t	my_size;

/*	my_size = 1;
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line, my_size);
		printf("\n");
	}
	close(fd);

	my_size = 2;
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line, my_size);
		printf("\n");
	}
	close(fd);

*/	my_size = 10;
	fd = open("test.txt", O_RDONLY);
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line, my_size);
		printf("\n");
	}
	close(fd);

/*	my_size = 100;
	fd = open("test.txt", O_RDONLY);
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line, my_size);
		ft_putchar('\n');
	}
	close(fd);

	my_size = 1000;
	fd = open("test.txt", O_RDONLY);
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line, my_size);
		ft_putchar('\n');
	}
	close(fd);

	my_size = 10000;
	fd = open("test.txt", O_RDONLY);
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line, my_size);
		ft_putchar('\n');
	}
	close(fd); */
	return (0);
}

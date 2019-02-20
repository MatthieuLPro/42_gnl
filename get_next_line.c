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

static char			*ft_strnjoin(char *s1, char *s2, size_t size)
{
	char			*dest;

	dest = NULL;
	if (s1 && s2)
	{
		dest = ft_strnew(ft_strlen(s1) + size);
		if (dest)
		{
			ft_strcpy(dest, s1);
			ft_strncat(dest, s2, size);
		}
	}
	return (dest);
}

static int			ft_words_size(char *str)
{
	size_t			i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		i++;
	}
	return (i);
}

static void			ft_strcpy_safe(char *dest, char *src)
{
	size_t			i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (dest[i])
	{
		dest[i] = 0;
		i++;
	}
}

static int			ft_fill(char *buf, int size)
{
	if (buf == NULL)
		buf[0] = 0;
	else
		ft_strcpy_safe(buf, &(buf[size + 1]));
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static char		buf[4096][BUFF_SIZE + 1];
	char			*tmp;
	int				ret;
	int				words_size;

	ret = 1;
	printf("1 : buf : %s - line : %s\n", buf[fd], *line);
	if (!line || fd < 0)
		return (-1);
	printf("2 : buf : %s - line : %s\n", buf[fd], *line);
	*line = ft_strnew(1);
	printf("3 : buf : %s - line : %s\n", buf[fd], *line);
	while (ret >= 1)
	{
		if (buf[fd][0] == 0)
			ret = read(fd, &buf[fd], BUFF_SIZE);
		printf("4 : buf : %s - line : %s\n", buf[fd], *line);
		if (ret <= -1)
			return (ret);
		printf("5 : buf : %s - line : %s\n", buf[fd], *line);
		words_size = ft_words_size(buf[fd]);
		tmp = *line;
		*line = ft_strnjoin(tmp, buf[fd], words_size);
		printf("6 : buf : %s - line : %s - tmp : %s\n", buf[fd], *line, tmp);
		free(tmp);
		if ((!buf[fd][0] && *line[0]) || (buf[fd][words_size]))
			return (ft_fill(buf[fd], words_size));
		printf("7 : buf : %s - line : %s\n", buf[fd], *line);
		ft_strclr((char *)&buf[fd]);
	}
	return (0);
}

/*
int		main(void)
{
	int		fd = open("test.txt", O_RDONLY);
	char	*line = NULL;
	int		ret;

	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (line)
			ft_putstr(line);
		ft_putchar('\n');
	}
	close(fd);
	return (0);
}
*/

int				main(void)
{
	char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	char		*filename;
	int			errors;

	filename = "gnl_to_free_or_not_to_free.txt";
	fd = open(filename, O_RDONLY);
	if (fd > 2)
	{
		count_lines = 0;
		errors = 0;
		line = NULL;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			printf("%s\n",line);
			if (count_lines == 0 && strcmp(line, "This is the first line") != 0)
				errors++;
			if (count_lines == 1 && strcmp(line, "This is the second one") != 0)
				errors++;
			if (count_lines == 2 && strcmp(line, "This is the third") != 0)
				errors++;
			if (count_lines == 3 && strcmp(line, "This is the last") != 0)
				errors++;
			count_lines++;
			free(line);
			if (count_lines > 50)
				break ;
		}
		close(fd);
		if (count_lines != 4)
			printf("-> must have returned '1' four times instead of %d time(s)\n", count_lines);
		if (errors > 0)
			printf("-> must have read \"This is the first line\", \"This is the second one\", \"This is the third\", \"This is the last\".\n");
		if (count_lines == 4 && errors == 0)
			printf("OK");
	}
	else
		printf("An error occured while opening file %s\n", filename);
	return (0);
}
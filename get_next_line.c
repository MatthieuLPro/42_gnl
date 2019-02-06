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

size_t	ft_strlenline(const char *s1)
{
	size_t i;

	i = 0;
	while (s1[i] != '\n' && s1[i])
		i++;
	return (i);
}

size_t	ft_strlenafterfirstline(const char *s1)
{
	size_t i;

	i = 0;
	if (s1)
	{	
		while (s1[i] != '\n' && s1[i])
			i++;
		i++;
		while (s1[i] != '\0')
			i++;
		return (i);
	}
	return (0);
}

char	*ft_strfirstline(char const *s1)
{
	char	*new;
	size_t	i;

	i = 0;
	if (s1)
	{
		if (!(new = ft_strnew(ft_strlenline(s1))))
			return (NULL);
		while (s1[i] != '\n' && s1[i])
		{
			new[i] = s1[i];
			i++;
		};	
		while (i < ft_strlenline(s1) + 1)
		{
			new[i] = '\0';
			i++;
		}
		if (new[0] == '\0')
			return (NULL);
		return (new);
	}
	return (NULL);
}

char	*ft_strafterfirstline(char *s1)
{
	char	*new;
	int		i;

	i = 0;
	if (s1)
	{
		if (!(new = ft_strnew(ft_strlenafterfirstline(s1))))
			return (NULL);
		while (*s1 != '\n' && *s1 != '\0')
			s1++;
		s1++;
		while (*s1 != '\0')
		{
			new[i] = *s1;
			s1++;
			i++;
		}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}

////////////////////////////////////////////////////////////////

int		get_next_line(const int fd, char **line)
{
	static char		*repere = NULL;
	int				ret;
	char			*buff;

	// init buff
	if (!(buff = ft_memalloc(sizeof(char *) * BUFF_SIZE + 1)))
		return (-1);
	// init repere IF NULL
	if (repere == NULL)
	{
		if (!(repere = ft_memalloc(sizeof(char *) * BUFF_SIZE + 1)))
			return (-1);
	}
	free(*line);
	*line = NULL;
	// read and cp in buff
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		// if \n exist in buff OR EOF cp and break
		if (ret == -1)
			return (-1);
		if (ft_strchr(buff, '\n') != NULL || ret < BUFF_SIZE)
		{
			repere = ft_strjoin(repere, buff);
			break ;
		}
		repere = ft_strjoin(repere, buff);
	}
	// Free buff if exist
	//if (ret < buff_size && ret > 0)
	//	repere = ft_strjoinSpecial(repere, buff);
	if (buff)
	{
		free(buff);
		buff = NULL;
	}
	*line = ft_strfirstline(repere);
	if (ft_strafterfirstline(repere))
		repere = ft_strafterfirstline(repere);
	if (!*line)	
		return (0);
	if (ret > 0 || repere)
		return (1);
	else if (ret == -1)
		return (-1);
	else
		return (0);
}
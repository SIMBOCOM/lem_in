/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:34:12 by rthai             #+#    #+#             */
/*   Updated: 2019/11/19 18:14:26 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int		index_char(const char *str, char c)
{
	int index;

	index = 0;
	while (str[index] != c && str[index])
		index++;
	if (str[index] == c)
		return (index);
	return (-1);
}

int		cheak_read(char **new_str, char **line, int a, char **res)
{
	if (a < 0)
	{
		ft_strdel(new_str);
		return (-1);
	}
	*line = *new_str;
	ft_strdel(res);
	return ((**new_str == 0) ? 0 : 1);
}

int		found_enter(char **res, char **line, char **new_str, int i_enter)
{
	if (new_str == 0)
	{
		if (!(*line = ft_strnew(i_enter)))
			return (-1);
		ft_strncpy(*line, *res, i_enter);
		ft_memmove(*res, *res + i_enter + 1, ft_strlen(*res + i_enter + 1) + 1);
		return (1);
	}
	if (!(*line = ft_strnew(ft_strlen(*new_str) + i_enter)))
		return (-1);
	ft_strcpy(*line, *new_str);
	ft_strncat(*line, *res, i_enter);
	ft_memmove(*res, *res + i_enter + 1, ft_strlen(*res + i_enter + 1) + 1);
	ft_strdel(new_str);
	return (1);
}

int		filling_str(char **line, char **res, int fd, int a)
{
	char	*new_str;
	char	*temp;

	if (!(new_str = ft_strdup(*res)))
		return (-1);
	ft_bzero(*res, BUFF_SIZE);
	while (1)
	{
		if ((a = read(fd, *res, BUFF_SIZE)) <= 0)
			return (cheak_read(&new_str, line, a, res));
		(*res)[a] = '\0';
		if ((a = index_char(*res, '\n')) != -1)
			return (found_enter(res, line, &new_str, a));
		if (!(temp = ft_strjoin(new_str, *res)))
			return (-1);
		ft_strdel(&new_str);
		new_str = temp;
		ft_bzero(*res, BUFF_SIZE);
	}
}

int		get_next_line(const int fd, char **line)
{
	static char	*residue[10240];
	int			index_enter;
	int			ret;

	if (fd < 0)
		return (-1);
	if (residue[fd] == NULL)
	{
		if (!(residue[fd] = ft_strnew(BUFF_SIZE)))
			return (-1);
		if ((ret = read(fd, residue[fd], BUFF_SIZE)) > 0)
			residue[fd][ret] = '\0';
		else
		{
			ft_strdel(&residue[fd]);
			return (ret < 0 ? -1 : 0);
		}
		if ((index_enter = index_char(residue[fd], '\n')) != -1)
			return (found_enter(&residue[fd], line, 0, index_enter));
		return (filling_str(line, &residue[fd], fd, index_enter));
	}
	if ((index_enter = index_char(residue[fd], '\n')) != -1)
		return (found_enter(&residue[fd], line, 0, index_enter));
	return (filling_str(line, &residue[fd], fd, index_enter));
}

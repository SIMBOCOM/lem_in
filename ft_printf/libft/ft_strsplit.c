/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 13:58:03 by flogan            #+#    #+#             */
/*   Updated: 2019/09/10 00:18:47 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	freez(int n, char **ss)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(ss[i]);
		ss[i++] = NULL;
	}
	free(ss);
}

static int		mstlen(const char *s, char c)
{
	int i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s != c && *s)
				s++;
			i++;
		}
		if (!*s)
			return (i);
		s++;
	}
	return (i);
}

static int		lstlen(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char		*mallocer(const char **s, char c, int i, char **ss)
{
	char	*new_word;
	int		j;

	if (!(new_word = (char*)malloc(sizeof(char) * (lstlen(*s, c) + 1))))
	{
		freez(i, ss);
		return (NULL);
	}
	j = 0;
	while (**s && **s != c)
	{
		new_word[j] = **s;
		(*s)++;
		j++;
	}
	new_word[j] = 0;
	return (new_word);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array_str;
	int		i;

	if (!s)
		return (NULL);
	if (!(array_str = (char**)malloc(sizeof(char*) * (mstlen(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!(array_str[i] = mallocer(&s, c, i, array_str)))
				return (NULL);
			i++;
		}
		if (*s == 0)
			break ;
		s++;
	}
	array_str[i] = NULL;
	return (array_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:33:42 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/04 11:28:25 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	strs_count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s++ == c)
		{
			count++;
			while (*s == c)
				s++;
		}
	}
	return (count + 1);
}

static void	free_strs(char **strs, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(strs[j++]);
	free(strs);
}

static char	*ft_split_skip(char *s, char c, char *sep)
{
	s = sep;
	while (s && *s && *s == c)
		s++;
	return (s);
}

static char	**ft_split_helper(char *s, char c, size_t count, char **strs)
{
	size_t	i;
	int		len;
	char	*sep;

	i = 0;
	while (i < count - 1)
	{
		sep = ft_strchr(s, c);
		if (sep)
			len = sep - s + 1;
		else
			len = ft_strlen(s) + 1;
		strs[i] = malloc(sizeof(char) * len);
		if (!strs[i])
		{
			free_strs(strs, i);
			return (NULL);
		}
		ft_strlcpy (strs[i], s, len);
		s = ft_split_skip(s, c, sep);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	count;
	char	*str;
	char	ar[2];

	if (!s)
		return (NULL);
	ar[0] = c;
	ar[1] = '\0';
	str = ft_strtrim(s, ar);
	if (!str)
		return (NULL);
	count = strs_count(str, c) + 1;
	if (ft_strlen(str) == 0)
		count = 1;
	strs = malloc(sizeof(char *) * (count));
	if (!strs)
	{
		free (str);
		return (NULL);
	}
	strs = ft_split_helper(str, c, count, strs);
	free (str);
	return (strs);
}

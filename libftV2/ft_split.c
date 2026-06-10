/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:05:58 by MP9               #+#    #+#             */
/*   Updated: 2025/07/18 15:28:55 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (words);
}

static char	*one_word(const char *s, char c, size_t	*i)
{
	char	*word;
	size_t	start;

	start = 0;
	while (s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] != c && s[*i] != '\0')
		(*i)++;
	word = (char *)malloc(sizeof(char) * (*i - start + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + start, *i - start + 1);
	return (word);
}

static char	**fill_words(char **words, const char *s, char c)
{
	size_t	wordi;
	size_t	i;

	wordi = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			words[wordi] = one_word(s, c, &i);
			if (!words[wordi])
			{
				while (wordi > 0)
					free(words[--wordi]);
				free(words);
				return (NULL);
			}
			wordi++;
		}
		else
			i++;
	}
	words[wordi] = NULL;
	return (words);
}

char	**ft_split(const char *s, char c)
{
	char	**words;

	if (!s)
		return (NULL);
	words = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!words)
		return (NULL);
	return (fill_words(words, s, c));
}

// int	main()
// {
// 	printf("%lu\n", count_words("                  olol", ' '));
// 	return (0);
// }
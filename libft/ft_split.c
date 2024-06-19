/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:29:07 by rhorvath          #+#    #+#             */
/*   Updated: 2023/04/13 13:45:07 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_word_copy(const char *s, char c)
{
	char	*word;
	int		len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	word[len] = '\0';
	while (len--)
		word[len] = s[len];
	return (word);
}

static void	ft_free_words(char **words, int i)
{
	while (i--)
		free(words[i]);
	free(words);
}

static void	ft_process_word(const char **s, char c, char **words, int *i)
{
	words[*i] = ft_word_copy(*s, c);
	if (!words[*i])
	{
		ft_free_words(words, *i);
		*i = -1;
		return ;
	}
	(*i)++;
	while (**s && **s != c)
		(*s)++;
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		i;
	int		num_words;

	if (!s)
		return (NULL);
	num_words = ft_count_words(s, c);
	words = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (*s && i >= 0)
	{
		while (*s == c)
			s++;
		if (*s)
			ft_process_word(&s, c, words, &i);
	}
	if (i == -1)
		return (NULL);
	words[i] = NULL;
	return (words);
}

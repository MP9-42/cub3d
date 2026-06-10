/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:46:45 by MP9               #+#    #+#             */
/*   Updated: 2025/08/10 18:38:26 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*sorc;

	i = 0;
	dest = (char *)dst;
	sorc = (const char *)src;
	if (!src && !dst)
		return (NULL);
	while (i < n)
	{
		dest[i] = sorc[i];
		i++;
	}
	return (dst);
}

static char	*join_line(int fd, char *buf, char *line)
{
	int		n;
	char	*tmp;

	n = 1;
	while (!ft_strchr(buf, '\n') && n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
			return (ft_memcpy(buf, "\0", 1), free(line), NULL);
		buf[n] = '\0';
		tmp = ft_strjoin(line, buf);
		free(line);
		if (!tmp)
			return (NULL);
		line = tmp;
	}
	return (line);
}

static char	*cut_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (ft_substr(str, 0, i + 1));
	else
		return (ft_strdup(str));
}

static void	clean_buf(char *buf)
{
	int		i;
	char	*nl;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
	{
		nl = ft_strchr(buf, '\n');
		if (nl)
			ft_memcpy(buf, nl + 1, ft_strlen(nl));
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_memcpy(buf, "\0", 1), NULL);
	line = ft_strdup(buf);
	if (!line)
		return (NULL);
	line = join_line(fd, buf, line);
	if (!line)
		return (NULL);
	if (!*line)
		return (free(line), NULL);
	result = cut_line(line);
	clean_buf(buf);
	free(line);
	return (result);
}

// int main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
// 	fd = open("text.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	i = 1;
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("line %d: %s", i++, line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
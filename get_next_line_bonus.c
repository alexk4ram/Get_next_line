/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkaram <alkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:20:31 by alkaram           #+#    #+#             */
/*   Updated: 2024/02/24 17:33:09 by alkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	if (!buffer)
		return (ft_strdup(buf));
	temp = ft_strjoin(buffer, buf);
	free(buffer);
	buffer = NULL;
	return (temp);
}

char	*ft_next(char *buffer)
{
	char	*next_line;
	size_t	len;
	char	*new_buffer;

	if (!buffer)
		return (NULL);
	next_line = ft_strchr(buffer, '\n');
	if (next_line)
	{
		next_line++;
		len = ft_strlen(next_line);
		new_buffer = malloc(len + 1);
		if (!new_buffer)
			return (free(buffer), NULL);
		ft_strlcpy(new_buffer, next_line, len + 1);
		free(buffer);
		return (new_buffer);
	}
	else
	{
		free(buffer);
		return (NULL);
	}
}

char	*ft_line(char *buffer)
{
	int		i;
	char	*line;
	int		newline_exist;

	newline_exist = 0;
	if (!buffer || !*buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		newline_exist = 1;
	line = (char *)malloc(i + newline_exist + 1);
	if (!line)
		return (free(buffer), NULL);
	ft_strlcpy(line, buffer, i + newline_exist + 1);
	if (newline_exist)
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*read_file(int fd, char *result)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(result), NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		result = ft_free(result, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
		free(buffer);
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (free(result), NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(result), NULL);
	}
	free(buffer);
	buffer = NULL;
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD || read(fd, 0, 0) < 0
		|| fd == 1 || fd == 2)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	buffer[fd] = ft_next(buffer[fd]);
	return (line);
}

// int	main(void)
// {
// int		fd;
// int		fd2;
// char	*result;
// int		fd3;
// int		fd4;
// int fd5;

// fd = open("test.txt", O_RDONLY);
// if (fd == -1)
// {
// 	perror("open");
// 	return (1);
// }
// while ((result = get_next_line(fd)))
// {
// 	printf("%s", result);
// 	free(result);
// }
// fd2 = open("test1.txt", O_RDONLY);
// if (fd2 == -1)
// {
// 	perror("open");
// 	return (1);
// }
// while ((result = get_next_line(fd2)))
// {
// 	printf("%s", result);
// 	free(result);
// }
// fd3 = open("test2.txt", O_RDONLY);
// if (fd3 == -1)
// {
// 	perror("open");
// 	return (1);
// }
// while ((result = get_next_line(fd3)))
// {
// 	printf("%s", result);
// 	free(result);
// }
// fd4 = open("test3.txt", O_RDONLY);
// if (fd4 == -1)
// {
// 	perror("open");
// 	return (1);
// }
// while ((result = get_next_line(fd4)))
// {
// 	printf("%s", result);
// 	free(result);
// }
// fd5 = open("giant_line_nl.txt", O_RDONLY);
// if (fd5 == -1)
// {
// 	perror("open");
// 	return (1);
// }
// while ((result = get_next_line(fd5)))
// {
// 	printf("%s", result);
// 	free(result);
// }
// close(fd);
// close(fd2);
// close(fd3);
// close(fd4);
// 	close(fd5);
// 	return (0);
// }

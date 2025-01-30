#include "get_next_line.h"

static char	*cleaner(char *static_str)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (static_str[i] != '\n' && static_str[i] != '\0')
		i++;
	if (static_str[i] == '\0')
	{
		free(static_str);
		return (NULL);
	}
	temp = ft_calloc_gnl((ft_strlen_gnl(static_str) + 1 - i), sizeof(char));
	j = 0;
	i++;
	while (static_str[i] != '\0')
		temp[j++] = static_str[i++];
	free(static_str);
	return (temp);
}

static char	*get_good_line(char *static_str)
{
	char	*temp;
	int		i;

	i = 0;
	while (static_str[i] != '\n' && static_str[i] != '\0')
		i++;
	temp = ft_calloc_gnl((i + 1 + ft_strchr_gnl(static_str, '\n')), sizeof(char));
	i = 0;
	while (static_str[i] != '\n' && static_str[i] != '\0')
	{
		temp[i] = static_str[i];
		i++;
	}
	if (ft_strchr_gnl(static_str, '\n'))
		temp[i] = '\n';
	return (temp);
}

static char	*read_all(int fd, char *static_str)
{
	int		reader;
	char	*temp;

	if (!static_str)
		static_str = ft_calloc_gnl(1, sizeof(char)); // <--------
	temp = ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	reader = 1;
	while (reader > 0)
	{
		reader = read(fd, temp, BUFFER_SIZE);
		if (reader < 0)
		{
			free(temp);
			return (NULL);
		}
		temp[reader] = '\0';
		static_str = ft_strjoin_gnl(static_str, temp);
		if (ft_strchr_gnl(temp, '\n'))
			break ;
	}
	free(temp);
	return (static_str);
}

char	*get_next_line(int fd)
{
	static char *static_str;
	char		*good_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_str = read_all(fd, static_str);
	if (static_str == NULL)
		return (free(static_str), static_str = NULL, NULL);
	good_line = get_good_line(static_str);
	if (good_line == NULL)
		return (free(static_str), static_str = NULL, NULL);
	static_str = cleaner(static_str);
	if (static_str == NULL)
		return (free(static_str), static_str = NULL, NULL);
	return (good_line);
}

int main()
{
	int		archive = "archivo.txt";
	char	*line;

	archive = open(archive, O_RDONLY);
	line = get_next_line(archive);
	while (line != NULL)
	{

	}
}

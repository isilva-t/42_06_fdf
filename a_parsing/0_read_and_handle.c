
#include "../fdf.h"

int	have_color(const char *str)
{
	int	i;

	i = 2;
	if (!str)
		return (0);
	if (ft_strlen(str) > 9
		|| (ft_strlen(str) == 9 && str[8] != '\n'))
		return (-1);
	if (!(*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')))
		return (-1);
	while (str[i] && i < 8)
	{
		if (!(ft_isdigit(str[i])
				|| (str[i] >= 'a' && str[i] <= 'f')
				|| (str[i] >= 'A' && str[i] <= 'F')))
			return (-1);
		i++;
	}
	return (1);
}

void	make_big_str(char *av, t_map *map, char *line)
{
	char	*tmp_to_free;

	map->fd1 = open(av, O_RDONLY);
	if (map->fd1 < 0)
		return ;
	map->big_str = (char *)ft_calloc(1, sizeof(char) + 1);
	if (!map->big_str)
		return ;
	while (line)
	{
		line = get_next_line(map->fd1);
		if (!line)
		{
			free (line);
			break ;
		}
		tmp_to_free = map->big_str;
		map->big_str = ft_strjoin(map->big_str, line);
		free (tmp_to_free);
		free (line);
		map->fd_lines += 1;
	}
	close(map->fd1);
	return ;
}

void	print_created_map(t_map *map, int i)
{
	auto int x = 0, y = 0;
	while (y < map->fd_lines && i == 1)
	{
		ft_printf("\n");
		x = 0;
		while (x < map->width[y])
		{
			ft_printf("\033[0m%d\033[0;33m%d\033[0m ", \
			map->pt[y][x].z, map->pt[y][x].color);
			x++;
		}
		y++;
	}
	ft_printf("\033[0;36m\nmap.width[0]: %d\nmap.height: %d\n\033[0m", map->width[0], map->fd_lines);
	return ;
}

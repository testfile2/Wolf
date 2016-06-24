/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 08:55:06 by kcowle            #+#    #+#             */
/*   Updated: 2016/06/17 11:38:40 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"
#include "wolf.h"
#include <fcntl.h>
#define MAPAREA 702

void		get_map_size(t_env *env, char *argv)
{
	char			*line;
	int				fd;
	char			**line2;
	char			*map;
	int				i;

	map = (char *)malloc(sizeof(char *) * MAPAREA);
	fd = open(argv, O_RDONLY);
	while (fd != -1 && get_next_line(fd, &line))
	{
		i = 0;
		if ((line2 = ft_strsplit(line, ',')))
		{
			while (line2[i] != '\0')
			{
				ft_strcat(map, line2[i]);
				i++;
			}
		}
		env->map_y++;
	}
	env->map_x = i - 1;
	*env = insert_map(map, env);
}

t_env		insert_map(char *line, t_env *env)
{
	int		i;
	int		j;
	int		place;

	place = 0;
	i = 0;
	j = 0;
	env->worldmap = (char **)malloc(sizeof(char **) * env->map_y);
	while (j <= env->map_y)
	{
		env->worldmap[j] = (char *)malloc(sizeof(char *) * env->map_x);
		++j;
	}
	j = -1;
	while (j++ <= env->map_y)
	{
		i = 0;
		while (i <= env->map_x && line[place] != '\n' && line[place] != '\0')
		{
			env->worldmap[j][i] = line[place];
			place++;
			i++;
		}
	}
	return (*env);
}

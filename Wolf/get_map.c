/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 07:57:15 by kcowle            #+#    #+#             */
/*   Updated: 2016/06/14 16:16:26 by kcowle           ###   ########.fr       */
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
	char 			*map;
	int				i;

	map = (char *)malloc(sizeof(char *) * MAPAREA);
	fd = open(argv, O_RDONLY);
	if (fd != -1)
	{
		while (get_next_line(fd, &line))
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
		ft_putstr(map);
		env = insert_map(map, env);
	}
	else
		exit(0);
}

t_env	*insert_map(char *line, t_env *env)
{
	t_env *env1;
	int i;
	int j;
	int place;
	
	place = 0;
	i = 0;
	j = 0;
	env1 = env;
	env1->worldmap = (char **)malloc(sizeof(char **) * env->map_y);
	while (j <= env->map_y)
	{
		env1->worldmap[j] = (char *)malloc(sizeof(char *) * env->map_x);
		++j;
	}
	j = 0;
	while (j <= env->map_y)
	{
		i = 0;
		while (i <= env->map_x && line[place] != '\n' && line[place] != '\0')
		{
			ft_putchar(line[place]);
			env1->worldmap[j][i] = line[place];
			++i;
			place++;
		}
		++j;
	}
	*env = *env1;
	return (env1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 09:43:29 by kcowle            #+#    #+#             */
/*   Updated: 2016/06/14 16:17:46 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft/libft.h"
#include <math.h>
#include <stdio.h>
#include "wolf.h"
#include <stdlib.h>
#define MAPWIDTH 26
#define MAPHEIGHT 27

int		get_key_event(int keycode, t_env *env)
{
	double	olddirx;
	double	oldplanex;
	t_env	env1;

	if (keycode == 53)
	{
		free(env->img);
		free(env->data);
		exit(0);
	}
	if (keycode == 126)
	{
		mlx_clear_window(env->mlx, env->win);
		mlx_destroy_image(env->mlx, env->img);
		env->img = mlx_new_image(env->mlx, 800, 800);
		env->data = \
		mlx_get_data_addr(env->img, &env->bpp, &env->sizeline, &env->endian);
		if (env->worldmap[(int)(env->posX + env->dirX * 0.5)][(int)(env->posY)] == '0')
			env->posX += env->dirX * 0.5;
		if (env->worldmap[(int)(env->posX)][(int)(env->posY + env->dirY * 0.5)] == '0')
			env->posY += env->dirY * 0.5;
		env1 = *env;
		*env = env1;
		wolf(&env1);
	}
	if (keycode == 125)
	{
		mlx_clear_window(env->mlx, env->win);
		mlx_destroy_image(env->mlx, env->img);
		env->img = mlx_new_image(env->mlx, 800, 800);
		env->data = \
		mlx_get_data_addr(env->img, &env->bpp, &env->sizeline, &env->endian);
		if (env->worldmap[(int)(env->posX - env->dirX * 0.5)][(int)(env->posY)] == '0')
			env->posX -= env->dirX * 0.5;
		if (env->worldmap[(int)(env->posX)][(int)(env->posY - env->dirY * 0.5)] == '0')
			env->posY -= env->dirY * 0.5;
		env1 = *env;
		*env = env1;
		wolf(&env1);
	}
	if (keycode == 124)
	{
		mlx_clear_window(env->mlx, env->win);
		mlx_destroy_image(env->mlx, env->img);
		env->img = mlx_new_image(env->mlx, 800, 800);
		env->data = \
		mlx_get_data_addr(env->img, &env->bpp, &env->sizeline, &env->endian);
		olddirx = env->dirX;
		env->dirX = env->dirX * cos(-0.3) - env->dirY * sin(-0.3);
		env->dirY = olddirx * sin(-0.3) + env->dirY * cos(-0.3);
		oldplanex = env->planeX;
		env->planeX = env->planeX * cos(-0.3) - env->planeY * sin(-0.3);
		env->planeY = oldplanex * sin(-0.3) + env->planeY * cos(-0.3);
		env1 = *env;
		*env = env1;
		wolf(&env1);
	}
	if (keycode == 123)
	{
		mlx_clear_window(env->mlx, env->win);
		mlx_destroy_image(env->mlx, env->img);
		env->img = mlx_new_image(env->mlx, 800, 800);
		env->data = \
		mlx_get_data_addr(env->img, &env->bpp, &env->sizeline, &env->endian);
		olddirx = env->dirX;
		env->dirX = env->dirX * cos(0.3) - env->dirY * sin(0.3);
		env->dirY = olddirx * sin(0.3) + env->dirY * cos(0.3);
		oldplanex = env->planeX;
		env->planeX = env->planeX * cos(0.3) - env->planeY * sin(0.3);
		env->planeY = oldplanex * sin(0.3) + env->planeY * cos(0.3);
		env1 = *env;
		*env = env1;
		wolf(&env1);
	}
	return (0);
}

void		makeparams(t_env *env)
{
	env->drawEnd = 0;
	env->drawStart = 0;
	env->color = 0;
	env->x = 0;
	env->sizeline = 0;
	env->pixel_nbr = 0;
	env->mlx = mlx_init();
	env->img = mlx_new_image(env->mlx, 800, 800);
	env->win = mlx_new_window(env->mlx, 800, 800, "Wolf");
	env->data = mlx_get_data_addr(env->img, &env->bpp, &env->sizeline, &env->endian);
	env->posX = 22;
	env->posY = 12;
	env->dirX = -1;
	env->dirY = 0;
	env->planeX = 0;
	env->planeY = 0.66;
}

void		redo(t_env *env)
{
	env->cameraX = 2 * env->x / (double)w - 1;
	env->rayPosX = env->posX;
	env->rayPosY = env->posY;
	env->rayDirX = env->dirX + env->planeX * env->cameraX;
	env->rayDirY = env->dirY + env->planeY * env->cameraX;
	env->mapX = (int)env->rayPosX;
	env->mapY = (int)env->rayPosY;
	env->sideDistX = 0;
	env->sideDistY = 0;
	env->deltaDistX = sqrt(1 + (env->rayDirY * env->rayDirY) / \
			(env->rayDirX * env->rayDirX));
	env->deltaDistY = sqrt(1 + (env->rayDirX * env->rayDirX) / \
			(env->rayDirY * env->rayDirY));
	env->perpWallDist = 0;
	env->stepX = 0;
	env->stepY = 0;
	env->hit = 0;
	env->lineHeight = 0;
}

void		wolf(t_env *env)
{
	int start;
	int line;

	start = 0;
	line = 0;
	env->x = 0;
	while (env->x < 800)
	{
		redo(env);
		if (env->rayDirX < 0)
		{
			env->stepX = -1;
			env->sideDistX = (env->rayPosX - env->mapX) * env->deltaDistX;
		}
		else
		{
			env->stepX = 1;
			env->sideDistX = (env->mapX + 1.0 - env->rayPosX) * env->deltaDistX;
		}
		if (env->rayDirY < 0)
		{
			env->stepY = -1;
			env->sideDistY = (env->rayPosY - env->mapY) * env->deltaDistY;
		}
		else
		{
			env->stepY = 1;
			env->sideDistY = (env->mapY + 1.0 - env->rayPosY) * env->deltaDistY;
		}
		while (env->hit == 0)
		{
			if (env->sideDistX < env->sideDistY)
			{
				env->sideDistX += env->deltaDistX;
				env->mapX += env->stepX;
				env->side = 0;
			}
			else
			{
				env->sideDistY += env->deltaDistY;
				env->mapY += env->stepY;
				env->side = 1;
			}
			if (env->worldmap[env->mapX][env->mapY] > '0')
				env->hit = 1;
		}
		if (env->side == 0)
			env->perpWallDist = (env->mapX - env->rayPosX + \
					(1 - env->stepX) / 2) / env->rayDirX;
		else
			env->perpWallDist = (env->mapY - env->rayPosY + \
					(1 - env->stepY) / 2) / env->rayDirY;
		env->lineHeight = (int)(h / env->perpWallDist);
		env->drawStart = -env->lineHeight / 2 + h / 2;
		if (env->drawStart < 0)
			env->drawStart = 0;
		env->drawEnd = env->lineHeight / 2 + h / 2;
		if (env->drawEnd >= h)
			env->drawEnd = h - 1;
		line = env->drawStart;
		if (env->side == 0)
		{
			while (line <= env->drawEnd && env->side == 0)
			{
				env->data[(line * env->sizeline) + \
					(env->x * env->bpp / 8)] = 200;
				env->data[(line * env->sizeline) + \
					(env->x * env->bpp / 8) + 1] = 10;
				env->data[(line * env->sizeline) + \
					(env->x * env->bpp / 8) + 2] = 200;
				line++;
			}
		}
		else
		{
			while (line <= env->drawEnd)
			{
				env->data[(line * env->sizeline) + \
					(env->x * env->bpp / 8)] = 10;
				env->data[(line * env->sizeline) + \
					(env->x * env->bpp / 8) + 1] = 200;
				env->data[(line * env->sizeline) + \
					(env->x * env->bpp / 8) + 2] = 10;
				line++;
			}
		}
		start = 0;
		while (start < env->drawStart)
		{
			env->data[(start * env->sizeline) + \
				(env->x * env->bpp / 8)] = 200;
			env->data[(start * env->sizeline) + \
				(env->x * env->bpp / 8) + 1] = 191;
			env->data[(start * env->sizeline) + \
				(env->x * env->bpp / 8) + 2] = 0;
			start++;
		}
		start = env->drawEnd;
		while (start < 800)
		{
			env->data[(start * env->sizeline) + (env->x * env->bpp / 8)] = 250;
			env->data[(start * env->sizeline) + (env->x * env->bpp / 8) + 1] = 10;
			env->data[(start * env->sizeline) + (env->x * env->bpp / 8) + 2] = 10;
			start++;
		}
		env->x++;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

int			main(void)
{
	t_env	env;

	get_map_size(&env, "map");
	makeparams(&env);
	wolf(&env);
	mlx_hook(env.win, 2, (1L << 0), get_key_event, &env);
	mlx_loop(env.mlx);
	return (0);
}

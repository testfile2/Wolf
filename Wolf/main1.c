#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include "wolf.h"
#include <stdlib.h>
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int get_key_event(int keycode, t_env *env)
{
	printf("keycode = %i\n", keycode);
	if (keycode == 53)
		exit(0);
	if (keycode == 126)
	{
		env->x = 0;

	}
	return 0;
}

void	makeParams(t_env *env)
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
	mlx_key_hook(env->win, get_key_event, &env->x);
	env->data = mlx_get_data_addr(env->img, &env->bpp, &env->sizeline, &env->endian);
	env->posX = 1;
	env->posY = 1;
	env->dirX = 2;
	env->dirY = 1;
	env->planeX = 0;
	env->planeY = 0.66;
}

void reDo(t_env *env)
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
	env->deltaDistX = sqrt(1 + (env->rayDirY * env->rayDirY) / (env->rayDirX * env->rayDirX));
	env->deltaDistY = sqrt(1 + (env->rayDirX * env->rayDirX) / (env->rayDirY * env->rayDirY));
	env->perpWallDist = 0;;
	env->stepX = 0;
	env->stepY = 0;
	env->hit = 0;
	env->lineHeight = 0;
}

void Wolf(t_env *env)
{
	while (env->x < 800)
	{
		reDo(env);
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
			if (worldMap[env->mapX][env->mapY] > 0) env->hit = 1;
		}
		if (env->side == 0) env->perpWallDist = (env->mapX - env->rayPosX + (1 - env->stepX) / 2) / env->rayDirX;
		else           env->perpWallDist = (env->mapY - env->rayPosY + (1 - env->stepY) / 2) / env->rayDirY;
		env->lineHeight = (int)(h / env->perpWallDist);
		env->drawStart = -env->lineHeight / 2 + h / 2;
		if(env->drawStart < 0)env->drawStart = 0;
		env->drawEnd = env->lineHeight / 2 + h / 2;
		if(env->drawEnd >= h)env->drawEnd = h - 1;
		env->data[(env->drawStart * env->sizeline) + (env->x * env->bpp /8) + 0] = 255;
		env->data[(env->drawStart * env->sizeline) + (env->x * env->bpp /8) + 1] = 10;
		env->data[(env->drawStart * env->sizeline) + (env->x * env->bpp /8) + 2] = 10;
		env->data[(env->drawEnd * env->sizeline) + (env->x * env->bpp /8) + 0] = 255;
		env->data[(env->drawEnd * env->sizeline) + (env->x * env->bpp /8) + 1] = 255;
		env->data[(env->drawEnd * env->sizeline) + (env->x * env->bpp /8) + 2] = 10;
		int line = env->drawStart - 1;
		if (env->side == 0)
		{
			while (line <= env->drawEnd && env->side == 0)
			{
				line++;
				env->data[(line * env->sizeline) + (env->x * env->bpp /8) + 0] = 150;
				env->data[(line * env->sizeline) + (env->x * env->bpp /8) + 1] = 10;
				env->data[(line * env->sizeline) + (env->x * env->bpp /8) + 2] = 150;
			}
		}
		else
		{
			while (line <= env->drawEnd)
			{
				line++;
				env->data[(line * env->sizeline) + (env->x * env->bpp /8) + 0] = 10;
				env->data[(line * env->sizeline) + (env->x * env->bpp /8) + 1] = 150;
				env->data[(line * env->sizeline) + (env->x * env->bpp /8) + 2] = 10;
			}
		}
		env->x++;
	}
}

int main()
{
	t_env env;
	makeParams(&env);
	Wolf(&env);
	mlx_key_hook(env.win, get_key_event, &env);
	mlx_put_image_to_window(env.mlx, env.win, env.img, 0, 0);
	mlx_loop(env.mlx);
	return 0;
}

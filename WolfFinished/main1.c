/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 09:43:29 by kcowle            #+#    #+#             */
/*   Updated: 2016/06/24 08:42:58 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft/libft.h"
#include <math.h>
#include "wolf.h"
#include <stdlib.h>
#define MAPWIDTH 26
#define MAPHEIGHT 27

int			get_key_event(int keycode, t_env *env)
{
	t_env	env1;

	if (keycode == 53)
	{
		free(env->img);
		free(env->data);
		exit(0);
	}
	if (keycode == 126)
		env1 = move_forward(env);
	if (keycode == 125)
		env1 = move_backwards(env);
	if (keycode == 124)
		env1 = look_left(env);
	if (keycode == 123)
		env1 = look_right(env);
	if (keycode >= 123 && keycode <= 126)
		wolf(&env1);
	return (0);
}

void		makeparams(t_env *env)
{
	env->drawend = 0;
	env->drawstart = 0;
	env->color = 0;
	env->x = 0;
	env->sizeline = 0;
	env->pixel_nbr = 0;
	env->mlx = mlx_init();
	env->img = mlx_new_image(env->mlx, 800, 800);
	env->win = mlx_new_window(env->mlx, 800, 800, "Wolf");
	env->data = \
	mlx_get_data_addr(env->img, &env->bpp, &env->sizeline, &env->endian);
	env->posx = 2;
	env->posy = 2;
	env->dirx = -1;
	env->diry = 0;
	env->planex = 0;
	env->planey = 0.66;
}

void		redo(t_env *env)
{
	env->camerax = 2 * env->x / (double)W - 1;
	env->rayposx = env->posx;
	env->rayposy = env->posy;
	env->raydirx = env->dirx + env->planex * env->camerax;
	env->raydiry = env->diry + env->planey * env->camerax;
	env->mapx = (int)env->rayposx;
	env->mapy = (int)env->rayposy;
	env->sidedisty = 0;
	env->sidedisty = 0;
	env->deltadistx = sqrt(1 + (env->raydiry * env->raydiry) / \
			(env->raydirx * env->raydirx));
	env->deltadisty = sqrt(1 + (env->raydirx * env->raydirx) / \
			(env->raydiry * env->raydiry));
	env->perpwalldist = 0;
	env->stepx = 0;
	env->stepy = 0;
	env->hit = 0;
	env->lineheight = 0;
}

void		wolf(t_env *env)
{
	env->x = 0;
	while (env->x < 800)
	{
		redo(env);
		*env = dda(env);
		*env = cast_until_hit(env);
		*env = get_distances(env);
		if (env->side == 0)
			*env = ns_wall(env);
		else
			*env = we_wall(env);
		*env = draw_skybox(env);
		*env = draw_floor(env);
		env->x++;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

int			main(void)
{
	t_env	env;

	get_map_size(&env, "maze");
	makeparams(&env);
	wolf(&env);
	mlx_hook(env.win, 2, (1L << 0), get_key_event, &env);
	mlx_hook(env.win, 17, 0L, redx, &env);
	mlx_loop(env.mlx);
	return (0);
}

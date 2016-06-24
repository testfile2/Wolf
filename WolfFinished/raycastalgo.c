/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RaycastAlgo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 08:24:56 by kcowle            #+#    #+#             */
/*   Updated: 2016/06/17 10:00:01 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_env	dda(t_env *env)
{
	if (env->raydirx < 0)
	{
		env->stepx = -1;
		env->sidedistx = (env->rayposx - env->mapx) * env->deltadistx;
	}
	else
	{
		env->stepx = 1;
		env->sidedistx = (env->mapx + 1.0 - env->rayposx) * env->deltadistx;
	}
	if (env->raydiry < 0)
	{
		env->stepy = -1;
		env->sidedisty = (env->rayposy - env->mapy) * env->deltadisty;
	}
	else
	{
		env->stepy = 1;
		env->sidedisty = (env->mapy + 1.0 - env->rayposy) * env->deltadisty;
	}
	return (*env);
}

t_env	cast_until_hit(t_env *env)
{
	while (env->hit == 0)
	{
		if (env->sidedistx < env->sidedisty)
		{
			env->sidedistx += env->deltadistx;
			env->mapx += env->stepx;
			env->side = 0;
		}
		else
		{
			env->sidedisty += env->deltadisty;
			env->mapy += env->stepy;
			env->side = 1;
		}
		if (env->worldmap[env->mapx][env->mapy] > '0')
			env->hit = 1;
	}
	return (*env);
}

t_env	get_distances(t_env *env)
{
	if (env->side == 0)
		env->perpwalldist = (env->mapx - env->rayposx + \
				(1 - env->stepx) / 2) / env->raydirx;
	else
		env->perpwalldist = (env->mapy - env->rayposy + \
				(1 - env->stepy) / 2) / env->raydiry;
	env->lineheight = (int)(H / env->perpwalldist);
	env->drawstart = -env->lineheight / 2 + H / 2;
	if (env->drawstart < 0)
		env->drawstart = 0;
	env->drawend = env->lineheight / 2 + H / 2;
	if (env->drawend >= H)
		env->drawend = H - 1;
	return (*env);
}

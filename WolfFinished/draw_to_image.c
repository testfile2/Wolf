/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_to_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 08:11:22 by kcowle            #+#    #+#             */
/*   Updated: 2016/06/17 09:46:22 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_env	ns_wall(t_env *env)
{
	int line;

	line = env->drawstart;
	while (line <= env->drawend && env->side == 0)
	{
		env->data[(line * env->sizeline) + \
			(env->x * env->bpp / 8)] = 200;
		env->data[(line * env->sizeline) + \
			(env->x * env->bpp / 8) + 1] = 10;
		env->data[(line * env->sizeline) + \
			(env->x * env->bpp / 8) + 2] = 200;
		line++;
	}
	return (*env);
}

t_env	we_wall(t_env *env)
{
	int line;

	line = env->drawstart;
	while (line <= env->drawend)
	{
		env->data[(line * env->sizeline) + \
			(env->x * env->bpp / 8)] = 10;
		env->data[(line * env->sizeline) + \
			(env->x * env->bpp / 8) + 1] = 200;
		env->data[(line * env->sizeline) + \
			(env->x * env->bpp / 8) + 2] = 10;
		line++;
	}
	return (*env);
}

t_env	draw_skybox(t_env *env)
{
	int start;

	start = 0;
	while (start < env->drawstart)
	{
		env->data[(start * env->sizeline) + \
			(env->x * env->bpp / 8)] = 200;
		env->data[(start * env->sizeline) + \
			(env->x * env->bpp / 8) + 1] = 191;
		env->data[(start * env->sizeline) + \
			(env->x * env->bpp / 8) + 2] = 0;
		start++;
	}
	return (*env);
}

t_env	draw_floor(t_env *env)
{
	int start;

	start = env->drawend;
	while (start < 800)
	{
		env->data[(start * env->sizeline) + \
			(env->x * env->bpp / 8)] = 250;
		env->data[(start * env->sizeline) + \
			(env->x * env->bpp / 8) + 1] = 10;
		env->data[(start * env->sizeline) + \
			(env->x * env->bpp / 8) + 2] = 10;
		start++;
	}
	return (*env);
}

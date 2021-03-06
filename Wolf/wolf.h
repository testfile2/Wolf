/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 11:03:04 by kcowle            #+#    #+#             */
/*   Updated: 2016/06/14 16:35:10 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define mapWidth 24
#define mapHeight 24
#define w 800
#define h 800

typedef struct s_env{
	int map_y;
	int map_x;
	char **worldmap;
	int drawEnd;
	int drawStart;
	int color;
	int bpp;
	int x;
	int endian;
	int i;
	int sizeline;
	int pixel_nbr;
	void *mlx;
	void *win;
	int *img;
	char *data;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double cameraX;
	double rayPosX;
	double rayPosY;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
}				t_env;

t_env	*insert_map(char *line, t_env *env);
void	get_map_size(t_env *env, char *argv);
void 	reDo(t_env *env);
int 	get_key_event(int keycode, t_env *env);
void 	wolf(t_env *env);

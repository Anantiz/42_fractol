/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   captain_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:40:05 by aurban            #+#    #+#             */
/*   Updated: 2023/11/21 13:01:05 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void update_iter_count(t_param *p, int direction);

static void cptn_hook_keys2(mlx_key_data_t keydata, t_param *p)
{
	if (keydata.key == MLX_KEY_R)
		shift_color(p, SHIFT_RED, MV_UP, 0);
	else if (keydata.key == MLX_KEY_F)
		shift_color(p, SHIFT_RED, MV_DOWN, 0);
	else if (keydata.key == MLX_KEY_T)
		shift_color(p, SHIFT_GREEN, MV_UP, 0);
	else if (keydata.key == MLX_KEY_G)
		shift_color(p, SHIFT_GREEN, MV_DOWN, 0);
	else if (keydata.key == MLX_KEY_Y)
		shift_color(p, SHIFT_BLUE, MV_UP, 0);
	else if (keydata.key == MLX_KEY_H)
		shift_color(p, SHIFT_BLUE, MV_DOWN, 0);
	else if (keydata.key == MLX_KEY_M)
		shift_color(p, MAGIC_COLOR, MV_UP, 0.5);
	else if (keydata.key == MLX_KEY_N)
		shift_color(p, MAGIC_COLOR, MV_DOWN, 0.5);
	else if (keydata.key == MLX_KEY_L)
		update_iter_count(p, MV_UP);
	else if (keydata.key == MLX_KEY_K)
		update_iter_count(p, MV_DOWN);
	else
		return;
	ft_image_update(p);
}

void cptn_hook_keys(mlx_key_data_t keydata, void *param)
{
	t_param *p;

	p = (t_param *)param;
	if (keydata.action == MLX_RELEASE)
		return;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(p->mlx);
	else if (keydata.key == MLX_KEY_RIGHT)
		move_cam(p, MV_RIGHT, MOVE_AMMOUNT);
	else if (keydata.key == MLX_KEY_LEFT)
		move_cam(p, MV_LEFT, MOVE_AMMOUNT);
	else if (keydata.key == MLX_KEY_UP)
		move_cam(p, MV_UP, MOVE_AMMOUNT);
	else if (keydata.key == MLX_KEY_DOWN)
		move_cam(p, MV_DOWN, MOVE_AMMOUNT);
	else if (keydata.key == MLX_KEY_SPACE)
		inverse_bg_color(p);
	else
	{
		cptn_hook_keys2(keydata, p);
		return;
	}
	ft_image_update(p);
}

static void update_iter_count(t_param *p, int direction)
{
	long double dynamic;

	dynamic = 0.1 * (p->colors.max_iter * 1 / MAX_ITER_ADD);
	if (direction == MV_UP)
	{
		if (p->colors.max_iter + MAX_ITER_ADD < MAX_ITER_ALLOWED + dynamic)
			p->colors.max_iter += MAX_ITER_ADD + dynamic;
	}
	else
	{
		if (p->colors.max_iter > MAX_ITER + MAX_ITER_ADD + dynamic)
			p->colors.max_iter -= MAX_ITER_ADD + dynamic;
		else
			p->colors.max_iter = MAX_ITER;
	}
	if (p->colors.max_iter > MAX_ITER_ALLOWED)
		p->colors.max_iter = MAX_ITER_ALLOWED;
}

void cptn_hook_resize(int width, int height, void *param)
{
	t_param *p;

	p = (t_param *)param;
	p->w = width;
	p->h = height;
	p->win_resolution = (long double)1.0 / (p->h / 2.5);
	ft_printf("Start resizing\t");
	mlx_delete_image(p->mlx, p->img);
	p->img = mlx_new_image(p->mlx, p->w, p->h);
	if (!p->img)
		p->img = NULL;
	if (mlx_image_to_window(p->mlx, p->img, 0, 0) < 0)
		p->img = NULL;
	ft_get_image_origin(&p->img_origin ,p);
	ft_printf("(I'm not dead)\t");
	ft_image_update(p);
	ft_printf("DONE\n");
}

void cptn_hook_scroll(double xdelta, double ydelta, void *param)
{
	t_param *p;
	t_i		win_origin;
	int 	x;
	int 	y;
	t_i		pp;

	p = (t_param *)param;
	mlx_get_mouse_pos(p->mlx, &x, &y);
	if (ydelta > 0)
	{
		p->zoom *= ZOOM_AMMOUNT;
		pp.r = x;
		pp.i = y;
		map_pixel_to_point(&pp, p);
		ft_get_image_origin(&win_origin, p);
		//printf("Math: calc=%LF  img_or=%LF\tshit=%LF\n", (x * p->zoom), p->img_origin.r,(p->zoom * p->win_resolution));
		p->img_origin.r += (p->zoom * p->win_resolution);// + (p->img_origin.r - (x * p->zoom));
		p->img_origin.i += (p->zoom * p->win_resolution);// + (p->img_origin.i - (y * p->zoom));
		printf("2Math:calc=%LF  ppr=%LF img_or=%LF\t\n",((pp.r) / (p->win_resolution))/p->zoom,pp.r ,p->img_origin.r);
		p->img_origin.r -=  (pp.r) / (p->zoom * p->win_resolution);
		p->img_origin.i -=  (pp.i) / (p->zoom * p->win_resolution);
		shift_color(p, MAGIC_COLOR, MV_UP, 0.5);
		update_iter_count(p, MV_UP);
		ft_image_update(p);
	}
	else if (ydelta < 0)
	{
		if (p->zoom < 1.0)
		{
			ft_get_image_origin(&win_origin, p);
			p->img_origin.r -= (p->zoom * p->win_resolution) + (win_origin.r - (x * p->zoom));
			p->img_origin.i -= (p->zoom * p->win_resolution) + (win_origin.r - (x * p->zoom));
		}
		p->zoom /= ZOOM_AMMOUNT;
		if (p->zoom > 1.0)
			p->zoom = 1.0;
		shift_color(p, MAGIC_COLOR, MV_DOWN, 0.5);
		update_iter_count(p, MV_DOWN);
		ft_image_update(p);
	}
	xdelta++;
	// printf("o.r=%LF  o.r=%LF\n", p->img_origin.r, p->img_origin.i);
}

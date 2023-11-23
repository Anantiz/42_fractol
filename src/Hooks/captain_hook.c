/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   captain_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:40:05 by aurban            #+#    #+#             */
/*   Updated: 2023/11/22 01:01:31 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	cptn_hook_keys2(mlx_key_data_t keydata, t_param *p)
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
		shift_color(p, MAGIC_COLOR, MV_UP, 5.0);
	else if (keydata.key == MLX_KEY_N)
		shift_color(p, MAGIC_COLOR, MV_DOWN, 5.0);
	else if (keydata.key == MLX_KEY_L)
		update_iter_count(p, MV_UP, (p->colors.max_iter / 4) + MAX_ITER_ADD);
	else if (keydata.key == MLX_KEY_K)
		update_iter_count(p, MV_DOWN, (p->colors.max_iter / 4) + MAX_ITER_ADD);
	else
		return ;
	ft_image_update(p);
}

void	cptn_hook_keys(mlx_key_data_t keydata, void *param)
{
	t_param	*p;

	p = (t_param *)param;
	if (keydata.action == MLX_RELEASE)
		return ;
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
		return ;
	}
	ft_image_update(p);
}

static void	cptn_hook_scroll_add(t_i *xy, t_param *p, int x, int y)
{
	map_pixel_to_point(xy, p);
	p->zoom_count++;
	map_point_to_pixel(xy, p);
	xy->r = x - xy->r;
	xy->i = y - xy->i;
	p->oo_coordinate.r += xy->r;
	p->oo_coordinate.i += xy->i;
	update_iter_count(p, MV_UP, MAX_ITER_ADD);
	ft_image_update(p);
}

static void	cptn_hook_scroll_sub(t_i *xy, t_param *p, int x, int y)
{
	map_pixel_to_point(xy, p);
	p->zoom_count--;
	if (p->zoom_count < 0.0)
		p->zoom_count = 0.0;
	else
	{
		map_point_to_pixel(xy, p);
		xy->r = xy->r - x;
		xy->i = xy->i - y;
		p->oo_coordinate.r -= xy->r;
		p->oo_coordinate.i -= xy->i;
		update_iter_count(p, MV_DOWN, MAX_ITER_ADD);
		ft_image_update(p);
	}
}

void	cptn_hook_scroll(double xdelta, double ydelta, void *param)
{
	t_param	*p;
	int		x;
	int		y;
	t_i		xy;

	p = (t_param *)param;
	mlx_get_mouse_pos(p->mlx, &x, &y);
	xy.r = x;
	xy.i = y;
	if (ydelta > 0)
		cptn_hook_scroll_add(&xy, p, x, y);
	else if (ydelta < 0)
		cptn_hook_scroll_sub(&xy, p, x, y);
	if (xdelta)
		ft_printf("");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   captain_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:40:05 by aurban            #+#    #+#             */
/*   Updated: 2023/11/20 12:42:47 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define MV_RIGHT 2
#define MV_LEFT -2
#define MV_UP 1
#define MV_DOWN -1
#define MAGIC_COLOR 420

#define MOVE_AMMOUNT 0.015
#define	SHIFT_AMMOUNT 15
#define ZOOM_AMMOUNT 0.75

static void	move_cam(t_param *p, int direction, long double move_amount)
{
	if (direction == MV_UP)
		p->img_origin.i += (long double)p->h * move_amount * (p->zoom / p->zoom * 4);
	else if (direction == MV_DOWN)
		p->img_origin.i -= (long double)p->h * move_amount * (p->zoom / p->zoom * 4);
	else if (direction == MV_RIGHT)
		p->img_origin.r -= (long double)p->w * move_amount * (p->zoom / p->zoom * 4);
	else if (direction == MV_LEFT)
		p->img_origin.r += (long double)p->w * move_amount * (p->zoom / p->zoom * 4);
	if (p->img_origin.r > p->w)
		p->img_origin.r = p->w;
	else if (p->img_origin.r < 0.0)
		p->img_origin.r = 0.0;
	if (p->img_origin.i > p->h)
		p->img_origin.i = p->h;
	else if (p->img_origin.i < 0.0)
		p->img_origin.i = 0.0;
	printf("o.r=%LF  o.r=%LF\n",p->img_origin.r, p->img_origin.i);
}

static uint8_t	shift_color_change(uint8_t *channel, int direction)
{
	int	change;

	change = direction * SHIFT_AMMOUNT;
	if (change + *channel > 255)
		change = 255 - *channel;
	else if (change + *channel < 0)
		change = (int)(*channel) * -1;
	*channel += change;
	return (change);
}

static void	shift_color(t_param *p, int color, int direction)
{
	int	change;

	change = 0;
	if (color == MAGIC_COLOR)
	{
		if (direction == MV_UP)
			p->colors.magic += 5.0;
		else
			if (p->colors.magic - 5.0 > 0)
				p->colors.magic -= 5.0;
		change = 1;
	}
	else
	{
		if (color == SHIFT_RED)
			change = shift_color_change(&p->colors.red, direction);
		else if (color == SHIFT_GREEN)
			change = shift_color_change(&p->colors.green, direction);
		else if (color == SHIFT_BLUE)
			change = shift_color_change(&p->colors.blue, direction);
		ft_printf("NEW COLORS= r=%u  g=%u  b=%u\n", p->colors.red \
		,p->colors.green, p->colors.blue);
	}
	if (change)
		ft_image_update(p);
}

static void	cptn_hook_keys2(mlx_key_data_t keydata, t_param *p)
{
	if (keydata.key == MLX_KEY_R)
		shift_color(p, SHIFT_RED, MV_UP);
	else if (keydata.key == MLX_KEY_F)
		shift_color(p, SHIFT_RED, MV_DOWN);
	else if (keydata.key == MLX_KEY_T)
		shift_color(p, SHIFT_GREEN, MV_UP);
	else if (keydata.key == MLX_KEY_G)
		shift_color(p, SHIFT_GREEN, MV_DOWN);
	else if (keydata.key == MLX_KEY_Y)
		shift_color(p, SHIFT_BLUE, MV_UP);
	else if (keydata.key == MLX_KEY_H)
		shift_color(p, SHIFT_BLUE, MV_DOWN);
	else if (keydata.key == MLX_KEY_M)
		shift_color(p, MAGIC_COLOR, MV_UP);
	else if (keydata.key == MLX_KEY_N)
		shift_color(p, MAGIC_COLOR, MV_DOWN);
	else
		return ;
	ft_image_update(p);
}

void	cptn_hook_keys(mlx_key_data_t keydata, void *param)
{
	t_param	*p;
	
	p = (t_param *) param;
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
	else
	{
		cptn_hook_keys2(keydata, p);
		return ;
	}
	ft_image_update(p);
}

void	cptn_hook_resize(int width, int height, void *param)
{
	t_param	*p;

	p = (t_param *)param;
	p->w = width;
	p->h = height;
	p->win_resolution = (long double)1.0 / (p->h / 2.5);
	mlx_delete_image(p->mlx, p->img);
	p->img = mlx_new_image(p->mlx, p->w, p->h);
	if (!p->img)
		p->img = NULL;
	if (mlx_image_to_window(p->mlx, p->img, 0, 0) < 0)
		p->img = NULL;
	ft_get_image_origin(p);
	ft_image_update(p);
}

void	cptn_hook_scroll(double xdelta, double ydelta, void* param)
{
	t_param	*p;
	int		x;
	int		y;

	p = (t_param *)param;
	if (ydelta > 0)
	{
		mlx_get_mouse_pos(p->mlx, &x, &y);
		p->img_origin.r += x * p->zoom * p->win_resolution;
		p->img_origin.i += y * p->zoom * p->win_resolution;
		p->zoom *= ZOOM_AMMOUNT;
	}
	else if (ydelta < 0)
		p->zoom /= ZOOM_AMMOUNT;
	if (p->zoom > 1.0 || p->zoom <= 0.0)
			p->zoom = 1.0;
	xdelta ++;
	ft_image_update(p);
	printf("ZOOM=%LF\t",p->zoom);
	printf("o.r=%LF  o.r=%LF\n",p->img_origin.r, p->img_origin.i);
}

/**
 * Returns the current, relative, mouse cursor position on the window, starting
 * from the top left corner.
 * 
 * Negative values or values greater than window width or height 
 * indicate that it is outside the window.
 * 
 * @param[in] mlx The MLX instance handle. 
 * @param[out] x The position.
 * @param[out] y The position.
 */
void mlx_get_mouse_pos(mlx_t* mlx, int32_t* x, int32_t* y);

/*


*/
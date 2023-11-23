/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:59:52 by aurban            #+#    #+#             */
/*   Updated: 2023/11/23 16:03:01 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "libft.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"

# define MAX_ITER 128
# define MAX_ITER_ADD 8
# define MAX_CONVERGE 2
# define SHIFT_RED 0
# define SHIFT_GREEN 1
# define SHIFT_BLUE 2
# define DEFAULT_MAGIC 5.0

# define MAX_ITER_ALLOWED 8388608

# define MV_RIGHT 2
# define MV_LEFT -2
# define MV_UP 1
# define MV_DOWN -1
# define MAGIC_COLOR 420

# define MOVE_AMMOUNT 0.1
# define SHIFT_AMMOUNT 15
# define ZOOM_AMMOUNT 0.75

typedef struct s_idouble
{
	long double	i;
	long double	r;
}t_i;

typedef struct s_colors
{
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
	unsigned int	void_color;
	unsigned int	max_iter;
	float			magic;
	int				bg_color;
}t_colors;

/*
oo_coordinates is the pixel coordinate of the origin
*/
typedef struct s_param
{
	unsigned int	w;
	unsigned int	h;
	long double		zoom_count;
	long double		win_resolution;
	t_i				oo_coordinate;
	t_i				c;
	t_colors		colors;
	char			set;
	mlx_t			*mlx;
	mlx_image_t		*img;
}t_param;

/*
CORE
*/

int				generate_fractal(t_param *p);
int				ft_image_update(t_param *p);
void			ft_get_image_origin(t_i *point, t_param *p);

/*
MATH
*/

int				ft_atoz(t_i *z, char *str);
long double		ft_abs(long double n);
void			map_pixel_to_point(t_i *pixel_pos, t_param *p);
void			map_point_to_pixel(t_i *point, t_param *p);

/*
SETS
*/

unsigned int	julia_set(t_colors *colors, t_i *z, t_i *c);
unsigned int	celtic_set(t_colors *colors, t_i *c);
unsigned int	mandlebrot_set(t_colors *colors, t_i *c);

/*
COLOR & CAM
*/

unsigned int	get_color(unsigned int n, t_colors *colors);
void			inverse_bg_color(t_param *p);
void			shift_color(t_param *p, int color, int dir, float ammount);
void			update_iter_count(t_param *p, int direction, float ammount);
void			move_cam(t_param *p, int direction, long double move_amount);

/*
HOOKS
*/
void			cptn_hook_keys(mlx_key_data_t keydata, void *param);
void			cptn_hook_resize(int width, int height, void *param);
void			cptn_hook_scroll(double xdelta, double ydelta, void *param);
void			cptn_hook_zoom(void *param);

/*
HELPERS
*/

int				init_param(char **argv, int argc, t_param *p);
int				init_const(char *str, t_param *p);
int				init_set(char *str, t_param *p);
int				init_size(char *str, t_param *p);

/*
ERROR AND DISPLAY
*/

int				args_help(void);
int				checkif_error(int error, t_param *p);
int				error_invalid_set(char set);
int				error_invalid_constant(int error);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:59:52 by aurban            #+#    #+#             */
/*   Updated: 2023/11/18 18:00:50 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "libft.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"

#include <stdio.h>
#include <fcntl.h>

# ifndef MAX_ITER
#  define MAX_ITER 64
# endif
# if (MAX_ITER > 512 || MAX_ITER <= 0)
#  define MAX_ITER 64
# endif
# define MAX_CONVERGE 6

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
}t_colors;

typedef struct s_param
{
	unsigned int	w;
	unsigned int	h;
	long double		zoom;
	long double		screen_resolution;
	t_i				img_origin;
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

/*
SETS
*/

unsigned int	julia_set(t_colors *colors, t_i *z, t_i *c);
unsigned int	mandlebrot_set(t_colors *colors, t_i *c);

/*
HOOKS
*/
void			cptn_hook_escape(void *param);
void			cptn_hook_zoom(void *param);
void			cptn_hook_move_cam(void *param);
void			cptn_hook_shift_color(void *param);

/*
HELPERS
*/

int				ft_atoz(t_i *z, char *str);
int				init_param(char **argv, int argc, t_param *p);
int				args_help(void);
int				error_invalid_set(char set);
int				error_invalid_constant(int error);

#endif
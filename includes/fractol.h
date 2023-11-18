/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:59:52 by aurban            #+#    #+#             */
/*   Updated: 2023/11/18 12:38:38 by aurban           ###   ########.fr       */
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
	# define MAX_ITER 16
# endif
# if (MAX_ITER > 512 || MAX_ITER <= 0)
	# define MAX_ITER 32
# endif
# define MAX_CONVERGE 2

typedef struct s_idouble
{
	long double	i;
	long double	r;
}t_i;

typedef struct s_param
{
	unsigned int	w;
	unsigned int	h;
	long double		zoom;
	long double		screen_resolution;
	t_i		 		img_origin;
	t_i				c;
	char			set;
	mlx_t			*mlx;
	mlx_image_t		*img;
}t_param;


int	generate_fractal(t_param *p);
int	ft_init_image(t_param *p);

unsigned int	julia_set(t_i *z,t_i *c);
unsigned int	mandlebrot_set(t_i *c);

int	init_param(char **argv, int argc, t_param *p);
int	args_help();
int	error_invalid_set(char set);
int	error_invalid_constant(int error);

int	ft_atoz(t_i *z, char *str);

#endif
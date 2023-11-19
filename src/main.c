/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:57:51 by aurban            #+#    #+#             */
/*   Updated: 2023/11/19 13:00:50 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_param	param;
	int		error;

	if (argc == 1)
		return (args_help());
	if (init_param(argv, argc, &param) != 0)
		return (args_help());
	error = generate_fractal(&param);
	if (error)
		ft_printf("ERROR, could not open window error:%d\n", error);
	//free_params(&param); Will be developped later
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:57:51 by aurban            #+#    #+#             */
/*   Updated: 2023/11/21 21:49:49 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	show_controls(void);

int	main(int argc, char **argv)
{
	t_param	param;
	int		error;

	if (argc == 1)
		return (args_help());
	if (init_param(argv, argc, &param) != 0)
		return (args_help());
	show_controls();
	error = generate_fractal(&param);
	if (error)
		ft_printf("ERROR, could not open window error:%d\n", error);
	return (0);
}

static void	show_controls(void)
{
	ft_printf("\n\nControls:\n"
		"\tUpdate RGB channel\n"
		"\t\tRed:   'R_KEY' to increase 'F_KEY' to decrease\n"
		"\t\tGreen: 'T_KEY' to increase 'G_KEY' to decrease\n"
		"\t\tBlue:  'Y_KEY' to increase 'H_KEY' to decrease\n"
		"\tUpdate Background\n"
		"\t\tSwitch color: 'SPACE_BAR'\n"
		"\tUpdate Precision\n"
		"\t\tRendering: 'L_KEY' to increase 'K_KEY' to decrease\n"
		"\t\tColors:    'M_KEY' to increase 'N_KEY' to decrease\n"
		"\tArrow keys to move the camera\n"
		"");
}

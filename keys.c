/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:01:16 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/21 16:42:57 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	keyrelease(int keycode, t_data *game)
{
	if (keycode == 13)
		game->inputs.w_pressed = false;
	if (keycode == 0)
		game->inputs.a_pressed = false;
	if (keycode == 1)
		game->inputs.s_pressed = false;
	if (keycode == 2)
		game->inputs.d_pressed = false;
	return (1);
}

int	keypress(int keycode, t_data *game)
{
	if (keycode == 53)
		end_game(game);
	if (keycode == 13)
		game->inputs.w_pressed = true;
	if (keycode == 0)
		game->inputs.a_pressed = true;
	if (keycode == 1)
		game->inputs.s_pressed = true;
	if (keycode == 2)
		game->inputs.d_pressed = true;
	return (0);
}

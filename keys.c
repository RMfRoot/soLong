/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:01:16 by egeorgel          #+#    #+#             */
/*   Updated: 2024/02/26 21:42:16 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	keyrelease(int keycode, t_data *game)
{
	if (keycode == 0x0057 || keycode == 0x0077)
		game->inputs.w_pressed = false;
	if (keycode == 0x0041 || keycode == 0x0061)
		game->inputs.a_pressed = false;
	if (keycode == 0x0053 || keycode == 0x0073)
		game->inputs.s_pressed = false;
	if (keycode == 0x0044 || keycode == 0x0064)
		game->inputs.d_pressed = false;
	return (1);
}

int	keypress(int keycode, t_data *game)
{
	if (keycode == 65307)
		end_game(game);
	if (keycode == 0x0057 || keycode == 0x0077)
		game->inputs.w_pressed = true;
	if (keycode == 0x0041 || keycode == 0x0061)
		game->inputs.a_pressed = true;
	if (keycode == 0x0053 || keycode == 0x0073)
		game->inputs.s_pressed = true;
	if (keycode == 0x0044 || keycode == 0x0064)
		game->inputs.d_pressed = true;
	return (0);
}

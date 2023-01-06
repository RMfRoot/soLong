/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:43:06 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/02 14:43:10 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "solong.h"

void free_img(t_frames *frames)
{
	free(frames->addr);
	free(frames->bits_per_pixel);
	free(frames->endian);
	free(frames->height);
	free(frames->images);
	free(frames->line_size);
}
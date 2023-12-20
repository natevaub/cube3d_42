/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 07:17:15 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/20 12:18:43 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	play_sound(char *path)
{
	pid_t pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		execve("/usr/bin/afplay", (char *[]){"/usr/bin/afplay", path, NULL}, NULL);
		exit(EXIT_FAILURE);
	}
}

void	sound_play(t_sound_type type)
{
	if (type == SOUND_PUNCH)
		play_sound("sounds/punch/punch01.mp3");
	else if (type == SOUND_FART)
		play_sound("sounds/farts/fart01.mp3");
}
// {
// 	pid_t pid = fork();
// 	if (pid < 0)
// 		return ;
// 	if (pid == 0)
// 	{
// 		execve("/usr/bin/afplay", (char *[]){"/usr/bin/afplay", path, NULL}, NULL);
// 		exit(EXIT_FAILURE);
// 	}
// }

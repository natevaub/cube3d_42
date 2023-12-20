/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 07:17:15 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/20 15:25:03 by rrouille         ###   ########.fr       */
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
	else if (type == SOUND_VOICE)
	{
		int i;
		
		i = rand() % 3;
		if (i == 0)
			play_sound("sounds/voices/oh-boy.flac");
		else if (i == 1)
			play_sound("sounds/voices/oh-my-god01.mp3");
		else if (i == 2)
			play_sound("sounds/voices/oh-my-god02.mp3");
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 07:17:15 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 19:05:44 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	sound_play(char *path)
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

void	plays_sounds(int punch_sound)
{
	if (punch_sound)
		sound_play("sounds/punch.mp3");
}

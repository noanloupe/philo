/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:30:32 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/29 23:34:34 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	my_usleep(int time_to_sleep)
{
	struct timeval	curr_time;
	int				start_time;
	int				checker;

	gettimeofday(&curr_time, NULL);
	start_time = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	while (1)
	{
		gettimeofday(&curr_time, NULL);
		checker = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
		if (checker < start_time + time_to_sleep)
			usleep(100);
		else
			break ;
	}
}

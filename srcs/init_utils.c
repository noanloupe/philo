/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:45:28 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/29 21:34:00 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	get_number(char	*str, int *error)
{
	int	n;
	int	prev;
	int	i;
	
	n = 0;
	i = 0;
	while (str[i])
	{
		prev = n;
		n = n * 10 + (int)str[i] - '0';
		if (prev > n)
			*error = 1;
		i++;
	}
	return (n);
}

void	error_free_mutex(int mode, t_mutex *mutex)
{
	if (mode == DEATH)
	{
		pthread_mutex_destroy(&mutex->print);
		printf("Death mutex failed\n");
	}
	else if (mode == DEAD_M)
	{
		pthread_mutex_destroy(&mutex->print);
		pthread_mutex_destroy(&mutex->death);
		printf("Dead malloc failed\n");
	}
	free(mutex);
}

int	init_data_error(int mode, t_data *data, t_mutex *mutex)
{
	if (mode == STRUCT)
		printf("Data malloc failed\n");
	else 
	{
		if (mode == OVER)
			printf("Argument is too big\n");
		else if (mode == MUTEX)
			printf("Mutex malloc failed\n");
		else
			error_free_mutex(mode, mutex);
		free(data);
	}
	return (1);
}

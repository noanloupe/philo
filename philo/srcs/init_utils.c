/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:45:28 by noloupe           #+#    #+#             */
/*   Updated: 2023/07/10 13:01:36 by noloupe          ###   ########.fr       */
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
	if (n == 0)
		*error = 1;
	return (n);
}

void	error_free_mutex(int mode, t_mutex *mutex)
{
	if (mode == death)
	{
		pthread_mutex_destroy(&mutex->print);
		printf("Death mutex failed\n");
	}
	else if (mode == e_dead)
	{
		pthread_mutex_destroy(&mutex->print);
		pthread_mutex_destroy(&mutex->death);
		printf("Dead malloc failed\n");
	}
	free(mutex);
}

int	init_data_error(int mode, t_data *data, t_mutex *mutex)
{
	if (mode == e_struct)
		printf("Data malloc failed\n");
	else
	{
		if (mode == over)
			printf("Argument is zero or too big\n");
		else if (mode == e_mutex)
			printf("Mutex malloc failed\n");
		else
			error_free_mutex(mode, mutex);
		free(data);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:44:45 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/29 23:33:23 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_mutex(t_mutex **mutex, t_data *data)
{
	*mutex = malloc(sizeof(t_mutex));
	if (!*mutex)
		return (init_data_error(e_mutex, data, *mutex));
	if (pthread_mutex_init(&(*mutex)->print, NULL))
		return (init_data_error(print, data, *mutex));
	if (pthread_mutex_init(&(*mutex)->death, NULL))
		return (init_data_error(e_dead, data, *mutex));
	return (0);
}

int	init_data(int ac, char **av, t_data	**data)
{
	int	error;

	error = 0;
	*data = malloc(sizeof(t_data));
	if (!data)
		return (init_data_error(e_struct, *data, NULL));
	(*data)->n_philo = get_number(av[1], &error);
	(*data)->time_to_die = get_number(av[2], &error);
	(*data)->time_to_eat = get_number(av[3], &error);
	(*data)->time_to_sleep = get_number(av[4], &error);
	(*data)->n_meals = -1;
	if (ac == 6)
		(*data)->n_meals = get_number(av[5], &error);
	if (error == 1)
		return (init_data_error(over, *data, NULL));
	return (0);
}

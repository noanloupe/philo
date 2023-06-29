/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:44:45 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/29 18:49:36 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	init_data_error(int mode, t_data *data)
{
	if (mode == STRUCT)
		printf("Data malloc failed\n");
	else 
	{
		if (mode == OVER)
			printf("Argument is too big\n");
		else if (mode == PRINT)
			printf("Print mutex failed\n");
		else if (mode == DEATH)
		{
			pthread_mutex_destroy(&data->print);
			printf("Death mutex failed\n");
		}
		free(data);
	}
	return (1);
}

static int	get_number(char	*str, int *error)
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

static int	set_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL))
		return (init_data_error(PRINT, data));
	if (pthread_mutex_init(&data->death, NULL))
		return (init_data_error(DEATH, data));
	return (0);
}

int	init_data(int ac, char **av, t_data	**data)
{
	int	error;

	error = 0;
	*data = malloc(sizeof(t_data));
	if (!data)
		return (init_data_error(STRUCT, *data));
	(*data)->n_philo = get_number(av[1], &error);
	(*data)->time_to_die = get_number(av[2], &error);
	(*data)->time_to_eat = get_number(av[3], &error);
	(*data)->time_to_sleep = get_number(av[4], &error);
	(*data)->n_meals = -1;
	if (ac == 6)
		(*data)->n_meals = get_number(av[5], &error);
	if (error == 1)
		return (init_data_error(OVER, *data));
	return (set_data_mutex(*data));
}

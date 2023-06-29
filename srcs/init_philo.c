/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:55:06 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/29 22:10:16 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	lst_add_back(t_philo **philo, t_philo *new)
{
	t_philo	*tmp;

	if (!new)
		return;
	if (!*philo)
	{
		*philo = new;
		return;
	}
	tmp = *philo;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_philo	*create_philo(int i, t_data *data, t_mutex *mutex, int *dead)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->philo_id = i;
	new->meals = 0;
	new->last_meal = 0;
	new->dead = dead;
	if (pthread_mutex_init(&new->fork, NULL))
		return (NULL);
	new->data = data;
	new->mutex = mutex;
	new->next = NULL;
	return (new);
}

int	set_dead(int **dead)
{
	*dead = malloc(sizeof(int));
	if (!*dead)
		return (1);
	**dead = 0;
	return (0);
}

int	init_philo(t_philo **philo, t_data *data, t_mutex *mutex)
{
	t_philo			*new;
	struct timeval	start;
	int				*dead;
	int				i;

	gettimeofday(&start, NULL);
	if (set_dead(&dead))
		return (init_data_error(DEAD_M, data, mutex));
	i = -1;
	while (++i < data->n_philo)
	{
		new = create_philo(i, data, mutex, dead);
		if (!new)
		{
			data->n_philo = i - 1;
			free_philo(philo, data, mutex);
			return (1);
		}
		new->start.tv_sec = start.tv_sec;		
		new->start.tv_usec = start.tv_usec;
		lst_add_back(philo, new);
	}
	if (data->n_philo > 1)
		new->next = *philo;
	return (0);
}

int init_structs(int ac, char **av, t_philo **philo)
{
	t_data	*data;
	t_mutex	*mutex;

	data = NULL;
	mutex = NULL;
	if (init_data(ac, av, &data))
		return (1);
	if (init_mutex(&mutex, data))
		return (1);
	if (init_philo(philo, data, mutex))
		return (1);
	return (0);
}
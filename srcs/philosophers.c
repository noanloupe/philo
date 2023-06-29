/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:56:10 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/29 18:22:15 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	end_all(t_philo *philo, pthread_t *brain)
{
	t_philo	*tmp;
	int		n_philo;
	int		i;

	pthread_mutex_lock(&philo->data->death);
	*philo->dead = YES;
	pthread_mutex_unlock(&philo->data->death);
	tmp = philo;
	n_philo = tmp->data->n_philo;
	i = 0;
	while (i < n_philo && tmp->next)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		i++;
	}
	pthread_join(*brain, NULL);
	pthread_mutex_lock(&philo->data->print);
	free_philo(&philo, philo->data);
	return (1);
}

int	end_sim(pthread_t *brain, t_philo *philo)
{
	int	n_philo;
	int	i;

	n_philo = philo->data->n_philo;
	i = 0;
	while (i < n_philo)
	{
		if (pthread_join(philo->thread, NULL))
			return (end_all(philo, brain));
		philo = philo->next;
		i++;
	}
	if (pthread_join(*brain, NULL))
		return (end_all(philo, brain));
	return (0);
}

int	launch_sim(t_philo *philo)
{
	pthread_t	brain;
	t_philo		*tmp;
	int			i;
	int			n_philo;

	if (pthread_create(&brain, NULL, &supervising, philo))
		return (end_all(philo, &brain));
	tmp = philo;
	i = 0;
	n_philo = tmp->data->n_philo;
	while (i < n_philo)
	{
		if (pthread_create(&tmp->thread, NULL, &routine, tmp))
			return (end_all(philo, &brain));
		tmp = tmp->next;
		i++;
	}
	return (end_sim(&brain, philo));
}

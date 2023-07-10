/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:14:33 by noloupe           #+#    #+#             */
/*   Updated: 2023/07/10 15:42:17 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->death);
	if (*philo->dead)
	{
		pthread_mutex_unlock(&philo->mutex->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex->death);
	return (0);
}

int	death_check(t_philo *philo, int base_time)
{
	struct timeval	time;
	int				checker;

	gettimeofday(&time, NULL);
	checker = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (philo->last_meal == 0)
		philo->last_meal = base_time;
	if (checker - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->mutex->death);
		*philo->dead = 1;
		pthread_mutex_unlock(&philo->mutex->death);
		return (1);
	}
	return (0);
}

int	meals_check(t_philo *philo)
{
	t_philo	*tmp;
	int		valid;
	int		n_philo;
	int		i;

	if (philo->data->n_meals == -1)
		return (0);
	tmp = philo;
	valid = 0;
	n_philo = tmp->data->n_philo;
	i = 0;
	while (i < n_philo)
	{
		if (tmp->meals < tmp->data->n_meals)
			valid = 1;
		tmp = tmp->next;
		i++;
	}
	if (valid == 1)
		return (0);
	pthread_mutex_lock(&philo->mutex->death);
	*philo->dead = 1;
	pthread_mutex_unlock(&philo->mutex->death);
	return (1);
}

void	*supervising(void *philo)
{
	t_philo		*tmp;
	int			base_time;

	tmp = (t_philo *)philo;
	base_time = tmp->start.tv_sec * 1000 + tmp->start.tv_usec / 1000;
	while (1)
	{
		if (is_dead(tmp))
			return (NULL);
		if (death_check(tmp, base_time))
			break ;
		if (meals_check(tmp))
			return (NULL);
		if (tmp->next)
			tmp = tmp->next;
	}
	pthread_mutex_lock(&tmp->mutex->death);
	if (*tmp->dead != 0)
	{
		pthread_mutex_unlock(&tmp->mutex->death);
		print_action(tmp, DEAD);
	}
	pthread_mutex_unlock(&tmp->mutex->death);
	return (NULL);
}

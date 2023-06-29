/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:45:11 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/29 18:39:10 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_philos(t_philo **philo)
{
	t_philo	*tmp;
	int		i = 0;

	tmp = *philo;
	while (i < tmp->data->n_philo)
	{
		printf("--- PHILO %d ---\n\n", i);
		printf("philo id	~> %d\n", tmp->philo_id);
		printf("meals eaten	~> %d\n", tmp->meals);
		printf("last meal	~> %d\n", tmp->last_meal);
		printf("timer sec	~> %ld\n", tmp->start.tv_sec);
		printf("timer usec	~> %d\n", tmp->start.tv_usec);
		printf("\n------------\n\n");
		i++;
		if (tmp->next)
			tmp = tmp->next;
	}
}

void	print_data(t_data *data)
{
	printf("--- DATA ---\n\n");
	printf("n_philo		~> %d\n", data->n_philo);
	printf("time_to_die	~> %d\n", data->time_to_die);
	printf("time_to_eat	~> %d\n", data->time_to_eat);
	printf("time_to_sleep	~> %d\n", data->time_to_sleep);
	printf("n_meals		~> %d\n", data->n_meals);
	printf("\n------------\n\n");
	pthread_mutex_lock(&data->print);
	printf("print locked\n");
	pthread_mutex_unlock(&data->print);
	printf("print unlocked\n");
	pthread_mutex_lock(&data->death);
	printf("death locked\n");
	pthread_mutex_unlock(&data->death);
	printf("death unlocked\n");
	printf("\n------------\n\n");
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	
	philo = NULL;
	if (parse_arguments(ac, av))
		return (1);
	if (init_structs(ac, av, &philo))
		return (1);
	if (launch_sim(philo))
		return (1);
	free_philo(&philo, philo->data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:32:17 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/29 19:09:41 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_philo(t_philo **philo, t_data *data)
{
	t_philo	*tmp;
	int		i;
	
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
	free((*philo)->dead);
	i = 0;
	while (i < data->n_philo)
	{
		tmp = *philo;
		if ((*philo)->next)
			*philo = (*philo)->next;
		pthread_mutex_destroy(&(*philo)->fork);
		free(tmp);
		i++;
	}
	free(data);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:45:11 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/29 21:45:21 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
	free_philo(&philo, philo->data, philo->mutex);
	return (0);
}

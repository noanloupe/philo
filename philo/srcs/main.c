/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:45:11 by noloupe           #+#    #+#             */
/*   Updated: 2023/07/17 12:56:19 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;

	philo = NULL;
	if (parse_arguments(argc, argv))
		return (1);
	if (init_structs(argc, argv, &philo))
		return (1);
	if (launch_sim(philo))
		return (1);
	free_philo(&philo, philo->data, philo->mutex, e_else);
	return (0);
}

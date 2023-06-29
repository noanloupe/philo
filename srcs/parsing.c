/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:14:21 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/27 17:51:05 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	arguments_parsing_error(int mode)
{
	if (mode == AC)
		printf("Wrong number of arguments\n");
	else if (mode == NUMBER)
		printf("Arguments must be numbers only\n");
	return (1);
}

static int	check_numbers(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (arguments_parsing_error(NUMBER));
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_arguments(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (arguments_parsing_error(AC));
	return (check_numbers(av));
}
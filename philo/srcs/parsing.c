/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:14:21 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/29 23:34:47 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	arguments_parsing_error(int mode)
{
	if (mode == ac)
		printf("Wrong number of arguments\n");
	else if (mode == number)
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
				return (arguments_parsing_error(number));
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_arguments(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (arguments_parsing_error(ac));
	return (check_numbers(argv));
}

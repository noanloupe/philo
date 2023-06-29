/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:47:22 by noloupe           #+#    #+#             */
/*   Updated: 2023/06/29 23:31:53 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

/*** STRUCT ***/

typedef struct s_philo
{
	int				philo_id;
	_Atomic int		meals;
	_Atomic int		last_meal;
	int				*dead;
	pthread_t		thread;
	pthread_mutex_t	fork;
	struct timeval	start;
	struct s_data	*data;
	struct s_mutex	*mutex;
	struct s_philo	*next;
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
}	t_data;

typedef struct s_mutex
{
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}	t_mutex;

/*** ENUMS ***/

enum	e_arguments_parsing_errors	{ac, number};
enum	e_init_errors	{e_struct, over, print, death, data, e_mutex, e_dead};

/*** DEFINES ***/

# define FORK	"has taken a fork"
# define EAT	"is eating"
# define DEAD	"died"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"

/*** FUNCTIONS ***/

/* ~PARSING~ */

int		parse_arguments(int ac, char **av);

/* ~STRUCT INIT~ */

int		get_number(char	*str, int *error);
int		init_data(int ac, char **av, t_data	**data);
int		init_data_error(int mode, t_data *data, t_mutex *mutex);
int		init_mutex(t_mutex **mutex, t_data *data);
int		init_structs(int ac, char **av, t_philo **philo);

/* ~PROGRAM~ */

int		launch_sim(t_philo *philo);
void	my_usleep(int time_to_sleep);
void	print_action(t_philo *philo, char *str);
void	*routine(void *philo);
void	*supervising(void *philo);

/* ~FREE~ */

void	free_philo(t_philo **philo, t_data *data, t_mutex *mutex);

#endif
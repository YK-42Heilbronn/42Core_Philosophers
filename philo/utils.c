/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 15:08:00 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/01 16:17:21 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void initialize_the_philosopher(t_philosopher *philo)
// {
// 	philo->nr = 1;
// 	philo->time_to_die = 10;
// 	philo->starvation = 20;
// 	philo->current_state = 1;
// 	philo->fork = 1;
// 	philo->states = 2;
// 	philo->s_duration.thinking = 10;
// 	philo->s_duration.eating = 20;
// 	philo->s_duration.sleeping = 30;
// }

// void set_philo_states_duration();

// suseconds_t current_time(void)
// {
// 	struct timeval	tv;

// 	// struct timezone tz;
// 	// tz.tz_dsttime = DST_WET;
// 	// tz.tz_minuteswest = -60;  // UTC+1
//  	gettimeofday(&tv, NULL);
// 	// printf("%ld", tv.tv_usec);
// 	// return (0);
// 	return (tv.tv_usec);
// }

suseconds_t current_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((suseconds_t)tv.tv_sec * 1000000 + tv.tv_usec);
}
void now()
{
	time_t now = time(NULL);          // get current time in seconds since epoch
    char *time_str = ctime(&now);     // convert to local time string

    printf("Current time: %s", time_str);  // ctime() includes a trailing '\n'
}

void	print_philo_list(t_simulation *sim_data)
{
	t_lst	*philos;
	int		nr_philos;

	philos = sim_data->philosophers;
	nr_philos = 0;
	// print sim data
	now();
	printf("============ Sim data ============\nnr_of_philos:: %d\nminimum_meals:: %d\n"
	"all_eaten_min_meals:: %d\nsim_stopped:: %d\n", sim_data->nr_of_philos, sim_data->minimum_meals,
	sim_data->all_eaten_min_meals, sim_data->sim_stopped);
	// print each philo data
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		// printf("philos: %p\n", philos);
		printf("=========== philo_nr:: %d===========\nphilo_fork:: %d\nphilo_meals_count:: %d\n"
			"philo_time_to_die:: %d\nphilo_time_to_eat:: %d\nphilo_time_to_sleep:: %d\n",
			philos->philo->nr, philos->philo->fork,
			philos->philo->meals_count, philos->philo->time_to_die,
			philos->philo->time_to_eat, philos->philo->time_to_sleep);
		// printf("philos-next: %p\n", philos->next_philo);
		philos = philos->next_philo;
		// printf("%p - %d\n", philos->philo, philos->philo->nr);
	}
}
void	destroy_philo_mutexes(t_simulation *sim_data)
{
	t_lst	*philo_node;
	int		nr_philos;

	philo_node = sim_data->philosophers;
	nr_philos = 0;
	// sim mutexes
	pthread_mutex_destroy(&(sim_data->print_mutex));
	pthread_mutex_destroy(&(sim_data->sim_stop_mutex));
	// each philo mutexes
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		pthread_mutex_destroy(&(philo_node->philo->reserve_resource));
		pthread_mutex_destroy(&(philo_node->philo->meal_mutex));
		pthread_mutex_destroy(&(philo_node->philo->last_meal_mutex));
		philo_node = philo_node->next_philo;
	}
}

void	initialize_philo_mutexes(t_simulation *sim_data)
{
	t_lst	*philo_node;
	int		nr_philos;

	philo_node = sim_data->philosophers;
	nr_philos = 0;
	// sim mutexes
	pthread_mutex_init(&(sim_data->print_mutex), NULL);
	pthread_mutex_init(&(sim_data->sim_stop_mutex), NULL);
	// each philo mutexes
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		// printf("mutex_init\n");
		pthread_mutex_init(&(philo_node->philo->reserve_resource), NULL);
		pthread_mutex_init(&(philo_node->philo->meal_mutex), NULL);
		pthread_mutex_init(&(philo_node->philo->last_meal_mutex), NULL);
		// printf("%p\n", philo_node->philo);
		philo_node = philo_node->next_philo;
	}
	// printf("in initialize:after while loop\n");
}

// void	set_philo_state_values(t_simulation *sim_data, int time_to_die, int eat_duration, int sleep_duration)
// {
// 	t_lst	*philo_node;
// 	int		nr_philos;

// 	philo_node = sim_data->philosophers;
// 	nr_philos = 0;
// 	// while (philo_node)
// 	while (nr_philos++ < sim_data->nr_of_philos)
// 	{
// 		philo_node->philo->time_to_eat = eat_duration;
// 		philo_node->philo->time_to_die = time_to_die;
// 		philo_node->philo->time_to_sleep = sleep_duration;
// 		philo_node = philo_node->next_philo;
// 	}
// }

void	initialize_philo_list(t_simulation *sim_data, int time_to_die, int eat_duration, int sleep_duration)
{
	t_philosopher	*philo;
	t_lst *philo_node;
	int				ind;

	ind = 1;
	// create philo linkedlist
	while (ind <= sim_data->nr_of_philos)
	{
		// printf("ind: %d\n", ind);
		philo = (t_philosopher *)malloc(sizeof(t_philosopher));
		philo->nr = ind++;
		philo->fork = 0;
    	philo->meals_count = 0;
		philo->time_to_eat = eat_duration;
		philo->time_to_die = time_to_die;
		philo->time_to_sleep = sleep_duration;
		// printf("philo: %p - %d\n", philo, philo->nr);
		ft_lstadd_back(&(sim_data->philosophers), new_lst(philo));
		// printf("philo: %p - %d\n", philo, philo->nr);
	}
	// make linked list cyclic so that last_node next_node is set to first_node
	philo_node = sim_data->philosophers;
	while (philo_node->next_philo)
	{
		// assign the sim_data pointer to each philosopher
		philo_node->philo->sim_data = sim_data;
		philo_node = philo_node->next_philo;
	}
	philo_node->next_philo = sim_data->philosophers;
}

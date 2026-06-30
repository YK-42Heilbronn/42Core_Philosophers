/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 15:08:00 by ykonka            #+#    #+#             */
/*   Updated: 2026/06/30 15:45:11 by ykonka           ###   ########.fr       */
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

void	print_philo_list(t_simulation *sim_data)
{
	t_lst	*philos;
	int		nr_philos;

	philos = sim_data->philosophers;
	nr_philos = 0;
	// while (philos)
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		// printf("philos: %p\n", philos);
		printf("%p - %d\n", philos->philo, philos->philo->nr);
		// printf("philos-next: %p\n", philos->next_philo);
		philos = philos->next_philo;
		// printf("%p - %d\n", philos->philo, philos->philo->nr);
	}
}

void	initialize_philo_mutexes(t_simulation *sim_data)
{
	t_lst	*philo_node;
	int		nr_philos;

	philo_node = sim_data->philosophers;
	nr_philos = 0;
	// printf("in initialize %p\n", philo_node);
	// while (philo_node)
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		// printf("mutex_init\n");
		pthread_mutex_init(&(philo_node->philo->reserve_resource), NULL);
		pthread_mutex_init(&(philo_node->philo->print_mutex), NULL);
		pthread_mutex_init(&(philo_node->philo->meal_mutex), NULL);
		pthread_mutex_init(&(philo_node->philo->sim_stop_mutex), NULL);
		pthread_mutex_init(&(philo_node->philo->last_meal_taken_mutex), NULL);
		// printf("%p\n", philo_node->philo);
		philo_node = philo_node->next_philo;
	}
	// printf("in initialize:after while loop\n");
}

void	destroy_philo_mutexes(t_simulation *sim_data)
{
	t_lst	*philo_node;
	int		nr_philos;

	philo_node = sim_data->philosophers;
	nr_philos = 0;
	// while (philo_node)
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		pthread_mutex_destroy(&(philo_node->philo->reserve_resource));
		pthread_mutex_destroy(&(philo_node->philo->print_mutex));
		pthread_mutex_destroy(&(philo_node->philo->meal_mutex));
		pthread_mutex_destroy(&(philo_node->philo->sim_stop_mutex));
		pthread_mutex_destroy(&(philo_node->philo->last_meal_taken_mutex));
		philo_node = philo_node->next_philo;
	}
}

void	set_philo_state_values(t_simulation *sim_data)
{
	t_lst	*philo_node;
	int		nr_philos;

	philo_node = sim_data->philosophers;
	nr_philos = 0;
	// while (philo_node)
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		philo_node->philo->time_to_eat = sim_data->eat_duration;
		philo_node->philo->time_to_die = sim_data->time_to_die;
		philo_node->philo->time_to_sleep = sim_data->sleep_duration;
		philo_node->philo->minimum_meals = sim_data->minimum_meals;
		philo_node = philo_node->next_philo;
	}
}

void	initialize_philo_list(t_lst **philo_head, int philo_nr)
{
	t_philosopher	*philo;
	t_lst *philo_node;
	int				ind;

	ind = 1;
	while (ind <= philo_nr)
	{
		// printf("ind: %d\n", ind);
		philo = (t_philosopher *)malloc(sizeof(t_philosopher));
		philo->nr = ind++;
		// printf("philo: %p - %d\n", philo, philo->nr);
		ft_lstadd_back(philo_head, new_lst(philo));
		// printf("philo: %p - %d\n", philo, philo->nr);
	}
	// make linked list cyclic so that last_node next_node is set to first_node
	philo_node = *philo_head;
	while (philo_node->next_philo)
	{
		philo_node = philo_node->next_philo;
	}
	philo_node->next_philo = *philo_head;
}


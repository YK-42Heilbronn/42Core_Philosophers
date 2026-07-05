/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 12:21:33 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/05 14:38:14 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philo_mutexes(t_simulation *sim_data)
{
	t_lst	*philo_node;
	int		nr_philos;

	philo_node = sim_data->philosophers;
	nr_philos = 0;
	pthread_mutex_destroy(&(sim_data->print_mutex));
	pthread_mutex_destroy(&(sim_data->state_mutex));
	pthread_mutex_destroy(&(sim_data->stop_mutex));
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		pthread_mutex_destroy(&(philo_node->philo->fork_mutex));
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
	pthread_mutex_init(&(sim_data->print_mutex), NULL);
	pthread_mutex_init(&(sim_data->state_mutex), NULL);
	pthread_mutex_init(&(sim_data->stop_mutex), NULL);
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		pthread_mutex_init(&(philo_node->philo->fork_mutex), NULL);
		pthread_mutex_init(&(philo_node->philo->meal_mutex), NULL);
		pthread_mutex_init(&(philo_node->philo->last_meal_mutex), NULL);
		philo_node = philo_node->next_philo;
	}
}

// make linked list cyclic so that last_node next_node is set to first_node
static void	build_cyclic_philo_list(t_simulation *sim_data)
{
	t_lst	*philo_node;

	if (sim_data->nr_of_philos > 1)
	{
		philo_node = sim_data->philosophers;
		while (philo_node->next_philo)
			philo_node = philo_node->next_philo;
		philo_node->next_philo = sim_data->philosophers;
	}
}

static void	set_philo_values(t_philosopher *philo, int time_to_die,
		int eat_duration, int sleep_duration)
{
	philo->fork = 0;
	philo->meals_count = 0;
	philo->time_to_eat = eat_duration;
	philo->time_to_die = time_to_die;
	philo->time_to_sleep = sleep_duration;
}

// create philo linkedlist
int	initialize_philo_list(t_simulation *sim_data, int time_to_die,
		int eat_duration, int sleep_duration)
{
	t_philosopher	*philo;
	t_lst			*new_node;
	int				ind;

	ind = 1;
	while (ind <= sim_data->nr_of_philos)
	{
		philo = (t_philosopher *)malloc(sizeof(t_philosopher));
		if (philo == NULL)
			return (free_philo_lst(sim_data, ind), 0);
		set_philo_values(philo, time_to_die, eat_duration, sleep_duration);
		philo->sim_data = sim_data;
		new_node = new_lst(philo);
		if (new_node == NULL)
		{
			free_philo_lst(sim_data, ind);
			free(philo);
			return (0);
		}
		philo->nr = ind++;
		ft_lstadd_back(&(sim_data->philosophers), new_node);
	}
	build_cyclic_philo_list(sim_data);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 11:33:59 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/05 15:02:27 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	died(t_lst *philo_node)
{
	suseconds_t	print_time;

	print_time = current_time() - philo_node->philo->sim_data->start_time;
	pthread_mutex_lock(&(philo_node->philo->sim_data->print_mutex));
	printf("%ld %d died\n", print_time / 1000, philo_node->philo->nr);
	pthread_mutex_unlock(&(philo_node->philo->sim_data->print_mutex));
}

int	simulation_stops(t_lst *philo_node)
{
	t_philosopher	*philo;

	philo = philo_node->philo;
	pthread_mutex_lock(&(philo->sim_data->stop_mutex));
	if (get_sim_stopped(philo->sim_data))
	{
		pthread_mutex_unlock(&(philo->sim_data->stop_mutex));
		return (get_sim_stopped(philo->sim_data));
	}
	if (is_philo_dead(philo_node))
	{
		philo->sim_data->sim_stopped = 1;
		died(philo_node);
		pthread_mutex_unlock(&(philo->sim_data->stop_mutex));
		return (get_sim_stopped(philo->sim_data));
	}
	if (are_philos_minimum_meals_done(philo_node))
	{
		philo->sim_data->sim_stopped = 1;
		pthread_mutex_unlock(&(philo->sim_data->stop_mutex));
		return (get_sim_stopped(philo->sim_data));
	}
	pthread_mutex_unlock(&(philo->sim_data->stop_mutex));
	return (get_sim_stopped(philo->sim_data));
}

void	start_threads(t_simulation *sim_data)
{
	t_lst	*next;
	int		nr_philos;

	next = sim_data->philosophers;
	nr_philos = 0;
	sim_data->start_time = current_time();
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		next->philo->last_meal_taken = sim_data->start_time;
		pthread_create(&(next->philo->routine), NULL, &philo_routine, next);
		next = next->next_philo;
	}
}

void	end_threads(t_simulation *sim_data)
{
	t_lst	*next;
	int		nr_philos;

	next = sim_data->philosophers;
	nr_philos = 0;
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		pthread_join(next->philo->routine, NULL);
		next = next->next_philo;
	}
}

void	simulation(t_simulation *sim_data)
{
	initialize_philo_mutexes(sim_data);
	start_threads(sim_data);
	end_threads(sim_data);
	destroy_philo_mutexes(sim_data);
	free_philo_lst(sim_data, sim_data->nr_of_philos);
}

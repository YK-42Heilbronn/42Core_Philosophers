/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 16:19:38 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/03 16:43:51 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// }
void	fork_taken(t_lst *philo_node)
{
	suseconds_t	print_time;

	print_time = current_time() - philo_node->philo->sim_data->start_time;
	pthread_mutex_lock(&(philo_node->philo->sim_data->print_mutex));
	printf("%ld %d has taken a fork\n", print_time / 1000,
		philo_node->philo->nr);
	pthread_mutex_unlock(&(philo_node->philo->sim_data->print_mutex));
}

void single_philo_eating(t_lst *philo_node)
{
	pthread_mutex_lock(&(philo_node->philo->reserve_resource));
	if (!simulation_stops(philo_node)) 			// Action: Take forks
	{
		update_forks_state(philo_node, 1, -1); 	// left fork taken
	}
	update_forks_state(philo_node, 0, -1); 		// left fork returned
	pthread_mutex_unlock(&(philo_node->philo->reserve_resource));
	usleep(philo_node->philo->time_to_die * 1000);
	if (is_philo_dead(philo_node))
		died(philo_node);
	set_sim_stopped(philo_node->philo->sim_data, 1);
}

void	eating(t_lst *philo_node)
{
	suseconds_t	print_time;

	pthread_mutex_lock(&(philo_node->philo->reserve_resource));
	pthread_mutex_lock(&(philo_node->next_philo->philo->reserve_resource));
	if (!simulation_stops(philo_node)) 			// Action: Take forks
	{
		update_forks_state(philo_node, 1, -1); 	// left fork taken
		update_forks_state(philo_node, 1, 1); 	// right fork taken
	}
	if (!simulation_stops(philo_node)) 			// Action: Print Eating
	{
		update_philo_last_meal_taken(philo_node); // update last meal taken time
		print_time = current_time() - philo_node->philo->sim_data->start_time;
		pthread_mutex_lock(&(philo_node->philo->sim_data->print_mutex));
		printf("%ld %d is eating\n", print_time / 1000, philo_node->philo->nr);
		pthread_mutex_unlock(&(philo_node->philo->sim_data->print_mutex));
	}
	if (!simulation_stops(philo_node)) 			// Action: Sleep Simulation Eating
		usleep(philo_node->philo->time_to_eat * 1000);
	update_forks_state(philo_node, 0, -1); 		// left fork returned
	update_forks_state(philo_node, 0, 1); 		// right fork returned
	pthread_mutex_unlock(&(philo_node->philo->reserve_resource));
	pthread_mutex_unlock(&(philo_node->next_philo->philo->reserve_resource));
	update_philo_meals_count(philo_node);     	// increment meals count
}

void	sleeping(t_lst *philo_node)
{
	t_philosopher	*philo;
	suseconds_t	print_time;

	philo = philo_node->philo;
	// if (!simulation_stops(philo_node))
	// {
	if (!simulation_stops(philo_node))
	{
		print_time = current_time() - philo->sim_data->start_time;
		pthread_mutex_lock(&(philo->sim_data->print_mutex));
		printf("%ld %d is sleeping\n", print_time / 1000, philo->nr);
		pthread_mutex_unlock(&(philo->sim_data->print_mutex));
	}
	if (!simulation_stops(philo_node))
		usleep(philo_node->philo->time_to_sleep * 1000);
}

void	thinking(t_lst *philo_node)
{
	suseconds_t	print_time;

	if (!simulation_stops(philo_node))
	{
		print_time = current_time() - philo_node->philo->sim_data->start_time;
		pthread_mutex_lock(&(philo_node->philo->sim_data->print_mutex));
		printf("%ld %d is thinking\n", print_time / 1000,
			philo_node->philo->nr);
		pthread_mutex_unlock(&(philo_node->philo->sim_data->print_mutex));
	}

	if (!simulation_stops(philo_node))
		usleep(10 * 1000);  // 10 milliseconds
}

void	died(t_lst *philo_node)
{
	suseconds_t	print_time;

	print_time = current_time() - philo_node->philo->sim_data->start_time;
	pthread_mutex_lock(&(philo_node->philo->sim_data->print_mutex));
	printf("%ld %d died\n", print_time / 1000, philo_node->philo->nr);
	pthread_mutex_unlock(&(philo_node->philo->sim_data->print_mutex));
}

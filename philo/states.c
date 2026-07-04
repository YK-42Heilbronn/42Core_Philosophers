/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 16:19:38 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/04 15:45:33 by ykonka           ###   ########.fr       */
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

/*
L36: Action: Take forks
L38: left fork taken
L40: left fork returned
L45: sim flag updated
*/
void	single_philo_eating(t_lst *philo_node)
{
	pthread_mutex_lock(&(philo_node->philo->reserve_resource));
	if (!simulation_stops(philo_node))
	{
		update_forks_state(philo_node, 1, -1);
	}
	update_forks_state(philo_node, 0, -1);
	pthread_mutex_unlock(&(philo_node->philo->reserve_resource));
	usleep(philo_node->philo->time_to_die * 1000);
	if (is_philo_dead(philo_node))
		died(philo_node);
	set_sim_stopped(philo_node->philo->sim_data, 1);
}

/*
L56: Action: Take forks
L58: left fork taken
L59: right fork taken
L61: Action: Print Eating
L63: update last meal taken time
L69: Action: Sleep Simulation Eating
L71: left fork returned
L72: right fork returned
L75: increment meals count
*/
void	eating(t_lst *philo_node)
{
	suseconds_t	print_time;

	pthread_mutex_lock(&(philo_node->philo->reserve_resource));
	pthread_mutex_lock(&(philo_node->next_philo->philo->reserve_resource));
	if (!simulation_stops(philo_node))
	{
		update_forks_state(philo_node, 1, -1);
		update_forks_state(philo_node, 1, 1);
	}
	if (!simulation_stops(philo_node))
	{
		update_philo_last_meal_taken(philo_node);
		print_time = current_time() - philo_node->philo->sim_data->start_time;
		pthread_mutex_lock(&(philo_node->philo->sim_data->print_mutex));
		printf("%ld %d is eating\n", print_time / 1000, philo_node->philo->nr);
		pthread_mutex_unlock(&(philo_node->philo->sim_data->print_mutex));
	}
	if (!simulation_stops(philo_node))
		usleep(philo_node->philo->time_to_eat * 1000);
	update_forks_state(philo_node, 0, -1);
	update_forks_state(philo_node, 0, 1);
	pthread_mutex_unlock(&(philo_node->philo->reserve_resource));
	pthread_mutex_unlock(&(philo_node->next_philo->philo->reserve_resource));
	update_philo_meals_count(philo_node);
}

void	sleeping(t_lst *philo_node)
{
	t_philosopher	*philo;
	suseconds_t		print_time;

	philo = philo_node->philo;
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
		usleep(10 * 1000);
}

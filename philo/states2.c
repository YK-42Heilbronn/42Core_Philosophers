/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 17:18:56 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/04 17:48:28 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	lock_forks(t_lst *philo_node, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	*first = &(philo_node->philo->reserve_resource);
	*second = &(philo_node->next_philo->philo->reserve_resource);
	if (*first > *second)
	{
		*first = &(philo_node->next_philo->philo->reserve_resource);
		*second = &(philo_node->philo->reserve_resource);
	}
	pthread_mutex_lock(*first);
	pthread_mutex_lock(*second);
}

void	eating(t_lst *philo_node)
{
	suseconds_t		print_time;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	lock_forks(philo_node, &first, &second);
	if (!simulation_stops(philo_node))
	{
		update_forks_state(philo_node, 1, -1);
		update_forks_state(philo_node, 1, 1);
		update_philo_last_meal_taken(philo_node);
		print_time = current_time() - philo_node->philo->sim_data->start_time;
		pthread_mutex_lock(&(philo_node->philo->sim_data->print_mutex));
		printf("%ld %d is eating\n", print_time / 1000, philo_node->philo->nr);
		pthread_mutex_unlock(&(philo_node->philo->sim_data->print_mutex));
		usleep(philo_node->philo->time_to_eat * 1000);
		update_forks_state(philo_node, 0, -1);
		update_forks_state(philo_node, 0, 1);
		update_philo_meals_count(philo_node);
	}
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

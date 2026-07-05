/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 16:19:38 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/05 13:51:13 by ykonka           ###   ########.fr       */
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
		usleep(1 * 1000);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 11:46:02 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/03 13:36:44 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void update_all_eaten_min_meals(t_simulation *sim_data, int value)
{
	pthread_mutex_lock(&(sim_data->state_mutex));
	sim_data->all_eaten_min_meals = value;
	pthread_mutex_unlock(&(sim_data->state_mutex));
}

void	update_forks_state(t_lst *philo_node, int state, int left_or_right)
{
	if (left_or_right == -1)
	{
		philo_node->philo->fork = state;  // left fork state
	}
	else if (left_or_right == 1)
	{
		philo_node->next_philo->philo->fork = state;  // right fork state
	}
	if (state == 1)
	{
		fork_taken(philo_node);
	}
}

void	update_philo_meals_count(t_lst *philo_node)
{
	pthread_mutex_lock(&(philo_node->philo->meal_mutex));
	philo_node->philo->meals_count++;
	pthread_mutex_unlock(&(philo_node->philo->meal_mutex));
}

void	update_philo_last_meal_taken(t_lst *philo_node)
{
	pthread_mutex_lock(&(philo_node->philo->last_meal_mutex));
	philo_node->philo->last_meal_taken = current_time();
	pthread_mutex_unlock(&(philo_node->philo->last_meal_mutex));
}

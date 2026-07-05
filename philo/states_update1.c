/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_update1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 11:46:02 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/05 09:27:03 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_forks_state(t_lst *philo_node, int state, int left_or_right)
{
	if (left_or_right == -1)
	{
		philo_node->philo->fork = state;
	}
	else if (left_or_right == 1)
	{
		philo_node->next_philo->philo->fork = state;
	}
	if (state == 1)
	{
		fork_taken(philo_node);
	}
}

int	get_philo_meals_count(t_lst *philo_node)
{
	int	meals_count;

	pthread_mutex_lock(&(philo_node->philo->meal_mutex));
	meals_count = philo_node->philo->meals_count;
	pthread_mutex_unlock(&(philo_node->philo->meal_mutex));
	return (meals_count);
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

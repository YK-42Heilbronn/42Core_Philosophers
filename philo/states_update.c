/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 11:46:02 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/01 16:53:07 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_forks_state(t_lst *philo, int state)
{
	philo->fork = state;
	next_philo->philo->fork = state;
	if (state == 1)
		fork_taken(philo_node->philo, current_time()-philo_node->philo->sim_start_time);
}

void	update_philo_meals_count(t_lst *philo)
{
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->meals_count++;
	pthread_mutex_lock(&(philo->meal_mutex));
}

void	update_philo_last_meal_taken(t_lst *philo)
{
	pthread_mutex_lock(&(philo->last_meal_mutex));
	philo->last_meal_taken = current_time();
	pthread_mutex_unlock(&(philo->last_meal_mutex));
}

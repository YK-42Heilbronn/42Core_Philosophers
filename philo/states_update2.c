/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_update2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 11:39:46 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/04 12:24:22 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_sim_stopped(t_simulation *sim_data)
{
	int	stopped;

	pthread_mutex_lock(&(sim_data->state_mutex));
	stopped = sim_data->sim_stopped;
	pthread_mutex_unlock(&(sim_data->state_mutex));
	return (stopped);
}

void	set_sim_stopped(t_simulation *sim_data, int value)
{
	pthread_mutex_lock(&(sim_data->state_mutex));
	sim_data->sim_stopped = value;
	pthread_mutex_unlock(&(sim_data->state_mutex));
}

int	get_all_eaten_min_meals(t_simulation *sim_data)
{
	int	all_eaten;

	pthread_mutex_lock(&(sim_data->state_mutex));
	all_eaten = sim_data->all_eaten_min_meals;
	pthread_mutex_unlock(&(sim_data->state_mutex));
	return (all_eaten);
}

void	update_all_eaten_min_meals(t_simulation *sim_data, int value)
{
	pthread_mutex_lock(&(sim_data->state_mutex));
	sim_data->all_eaten_min_meals = value;
	pthread_mutex_unlock(&(sim_data->state_mutex));
}

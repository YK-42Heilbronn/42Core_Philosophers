/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 16:19:38 by ykonka            #+#    #+#             */
/*   Updated: 2026/06/30 11:28:10 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// }
void	fork_taken(t_philosopher *philo, suseconds_t time_us)
{
	printf("%ld %d has taken a fork\n", time_us / 1000, philo->nr);
}

void	eating(t_thread_context *t_context, suseconds_t time_us)
{
	t_philosopher *philo;
	t_lst *philo_node;

	philo_node = t_context->philo;
	philo = t_context->philo->philo;
	if (!simulation_stops(t_context))
	{
		pthread_mutex_lock(&(philo->reserve_resource));
		update_forks_state(philo_node, 1); // taken
		usleep(philo->time_to_eat * 1000);
		printf("%ld %d is eating\n", time_us / 1000, philo->nr);
		update_forks_state(philo_node, 0); // returned
		update_philo_meals_count(philo_node);  // increment meals count
		update_philo_last_meal_taken(philo_node); // update last meal taken time
		pthread_mutex_unlock(&(philo->reserve_resource));
	}
	end_threads(t_context->sim_data);
}

void	sleeping(t_thread_context *t_context, suseconds_t time_us)
{
	t_philosopher *philo;

	philo = t_context->philo->philo;
	if (!simulation_stops(t_context))
	{
		usleep(philo->time_to_sleep * 1000);
		printf("%ld %d is sleeping\n", time_us / 1000, philo->nr);
	}
	end_threads(t_context->sim_data);
}

void	thinking(t_thread_context *t_context, suseconds_t time_us)
{
	t_philosopher *philo;

	philo = t_context->philo->philo;
	if (!simulation_stops(t_context))
	{
		printf("%ld %d is thinking\n", time_us / 1000, philo->nr);
	}
	end_threads(t_context->sim_data);
}

void	died(t_philosopher *philo, suseconds_t time_us)
{
	printf("%ld %d died\n", time_us / 1000, philo->nr);
	// exit(0);
}

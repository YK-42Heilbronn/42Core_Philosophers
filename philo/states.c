/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 16:19:38 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/01 16:49:12 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// }
void	fork_taken(t_philosopher *philo, suseconds_t time_us)
{
	pthread_mutex_lock(&(philo->sim_data->print_mutex));
	printf("%ld %d has taken a fork\n", time_us / 1000, philo->nr);
	pthread_mutex_unlock(&(philo->sim_data->print_mutex));
}

void	eating(t_philosopher *philo, suseconds_t time_us)
{
	// t_philosopher *philo;
	// t_lst *philo_node;

	// philo_node = philo;
	// philo = t_context->philo->philo;
	if (!simulation_stops(philo))
	{
		pthread_mutex_lock(&(philo->reserve_resource));
		update_forks_state(philo, 1); // taken
		usleep(philo->time_to_eat * 1000);
		printf("%ld %d is eating\n", time_us / 1000, philo->nr);
		update_forks_state(philo, 0); // returned
		pthread_mutex_unlock(&(philo->reserve_resource));
		update_philo_meals_count(philo);  // increment meals count
		update_philo_last_meal_taken(philo); // update last meal taken time
	}
	end_threads(philo);
}

void	sleeping(t_philosopher *philo, suseconds_t time_us)
{
	t_philosopher *philo;

	philo = t_context->philo->philo;
	if (!simulation_stops(t_context))
	{
		usleep(philo->time_to_sleep * 1000);
		pthread_mutex_lock(&(philo->print_mutex));
		printf("%ld %d is sleeping\n", time_us / 1000, philo->nr);
		pthread_mutex_unlock(&(philo->print_mutex));
	}
	end_threads(t_context->sim_data);
}

void	thinking(t_philosopher *philo, suseconds_t time_us)
{
	t_philosopher *philo;

	philo = t_context->philo->philo;
	if (!simulation_stops(t_context))
	{
		pthread_mutex_lock(&(philo->print_mutex));
		printf("%ld %d is thinking\n", time_us / 1000, philo->nr);
		pthread_mutex_unlock(&(philo->print_mutex));
	}
	end_threads(t_context->sim_data);
}

void	died(t_philosopher *philo, suseconds_t time_us)
{
	pthread_mutex_lock(&(philo->print_mutex));
	printf("%ld %d died\n", time_us / 1000, philo->nr);
	pthread_mutex_unlock(&(philo->print_mutex));
	// exit(0);
}

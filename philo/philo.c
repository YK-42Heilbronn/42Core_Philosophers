/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 13:05:35 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/04 14:32:21 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philos_minimum_meals_done(t_lst *philo_node)
{
	t_simulation	*sim_data;
	t_lst			*nxt_philo;
	int				nr_philos;

	sim_data = philo_node->philo->sim_data;
	nxt_philo = sim_data->philosophers;
	nr_philos = 0;
	if (sim_data->minimum_meals <= 0)
		return (0);
	update_all_eaten_min_meals(sim_data, 1);
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		if (nxt_philo->philo->meals_count < sim_data->minimum_meals)
		{
			update_all_eaten_min_meals(sim_data, 0);
			break ;
		}
		nxt_philo = nxt_philo->next_philo;
	}
	return (get_all_eaten_min_meals(sim_data));
}

int	is_philo_dead(t_lst *philo_node)
{
	t_philosopher	*philo;
	suseconds_t		time_since_last_meal;

	philo = philo_node->philo;
	time_since_last_meal = time_elapsed_in_sim(philo->last_meal_taken,
			current_time());
	if (time_since_last_meal >= philo->time_to_die * 1000)
	{
		return (1);
	}
	return (0);
}

static int	run_even_cycle(t_lst *philo_node)
{
	eating(philo_node);
	if (get_sim_stopped(philo_node->philo->sim_data))
		return (1);
	sleeping(philo_node);
	if (get_sim_stopped(philo_node->philo->sim_data))
		return (1);
	thinking(philo_node);
	return (0);
}

static int	run_odd_cycle(t_lst *philo_node)
{
	sleeping(philo_node);
	if (get_sim_stopped(philo_node->philo->sim_data))
		return (1);
	thinking(philo_node);
	if (get_sim_stopped(philo_node->philo->sim_data))
		return (1);
	if (philo_node->philo->sim_data->nr_of_philos == 1)
		return (single_philo_eating(philo_node), 1);
	eating(philo_node);
	return (0);
}

void	*philo_routine(void *p_node)
{
	t_lst	*philo_node;

	philo_node = (t_lst *)p_node;
	while (!get_sim_stopped(philo_node->philo->sim_data))
	{
		if (philo_node->philo->nr % 2 == 0)
		{
			if (run_even_cycle(philo_node))
				break ;
		}
		else if (run_odd_cycle(philo_node))
			break ;
	}
	return (NULL);
}

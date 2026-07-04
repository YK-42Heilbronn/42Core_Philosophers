/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 15:08:00 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/04 12:31:44 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	time_elapsed_in_sim(suseconds_t start_time,
		suseconds_t current_time)
{
	return (current_time - start_time);
}

// L27: in microseconds
suseconds_t	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((suseconds_t)tv.tv_sec * 1000000 + tv.tv_usec);
}

static void	del_philo(void *philo)
{
	free((t_philosopher *)philo);
}

void	free_philo_lst(t_simulation *sim_data, int nr_philos)
{
	t_lst	*next;
	t_lst	*node;
	int		philos;

	node = sim_data->philosophers;
	philos = 0;
	while (philos++ < nr_philos)
	{
		next = node->next_philo;
		del_philo(node->philo);
		node->philo = NULL;
		free(node);
		node = next;
	}
	free(sim_data);
	sim_data = NULL;
}

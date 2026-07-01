/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 13:05:35 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/01 12:12:52 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	time_elapsed_in_sim(suseconds_t start_time,
		suseconds_t current_time)
{
	return (current_time - start_time);
}

int	simulation_stops(t_thread_context *t_context)
{
	t_philosopher	*philo;

	philo = t_context->philo->philo;
	// printf("in simulation stops\n");
	if (is_all_philos_reached_minimum_meals(t_context->sim_data) || is_philo_dead(philo))
	{
		// died(philo, current_time()-philo->sim_start_time);
		pthread_mutex_lock(&(philo->sim_stop_mutex));
		philo->sim_stopped = 1;
		pthread_mutex_unlock(&(philo->sim_stop_mutex));
	}
	// else if ()
	// {
	// 	died(philo, current_time());
	// 	t_context->sim_stopped = 1;
	// }
	else
	{
		pthread_mutex_lock(&(philo->sim_stop_mutex));
		philo->sim_stopped = 0;
		pthread_mutex_unlock(&(philo->sim_stop_mutex));
	}
	return (philo->sim_stopped);
}

int	is_all_philos_reached_minimum_meals(t_simulation *sim_data)
{
	t_lst	*nxt_philo;
	int		nr_philos;
	// int		all_reached_minimum_meals;
	suseconds_t sim_start_time;

	nxt_philo = sim_data->philosophers;
	nr_philos = 0;
	sim_data->all_eaten_min_meals = 1;
	sim_start_time = nxt_philo->philo->sim_start_time;
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		if (nxt_philo->philo->minimum_meals > 0
			&& nxt_philo->philo->meals_count < nxt_philo->philo->minimum_meals)
		{
			sim_data->all_eaten_min_meals = 0;
			break ;
		}
		nxt_philo = nxt_philo->next_philo;
	}
	if (sim_data->all_eaten_min_meals)
	{
		died(nxt_philo->philo, current_time() - sim_start_time);
	}
	return (sim_data->all_eaten_min_meals);
}

int	is_philo_dead(t_philosopher *philo)
{
	suseconds_t	time_since_last_meal;

	time_since_last_meal = time_elapsed_in_sim(philo->last_meal_taken,
			current_time());
	if (time_since_last_meal >= philo->time_to_die * 1000)
	{
		died(philo, current_time() - philo->sim_start_time);
		return (1);
	}
	return (0);
}

// create ds - existence
// thread func
// it is an routine of an single philosopher
void	*philo_routine(void *t_context)
{
	t_lst				*philo_node;
	t_thread_context	*context;

	context = (t_thread_context *)t_context;
	philo_node = context->philo;
	while (1)
	{
		if (philo_node->philo->nr % 2 == 0)
		{
			eating(t_context, current_time()
				- philo_node->philo->sim_start_time);
			sleeping(t_context, current_time()
				- philo_node->philo->sim_start_time);
			thinking(t_context, current_time()
				- philo_node->philo->sim_start_time);
		}
		else
		{
			sleeping(t_context, current_time()
				- philo_node->philo->sim_start_time);
			thinking(t_context, current_time()
				- philo_node->philo->sim_start_time);
			eating(t_context, current_time()
				- philo_node->philo->sim_start_time);
		}
	}
	return (NULL);
}

void	start_threads(t_simulation *sim_data)
{
	t_lst				*next;
	t_thread_context	*context;
	int					nr_philos;

	next = sim_data->philosophers;
	nr_philos = 0;
	sim_data->start_time = current_time();
	context = (t_thread_context *)malloc(sizeof(t_thread_context));
	context->sim_data = sim_data;
	// while (next)
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		next->philo->sim_start_time = sim_data->start_time;
		next->philo->last_meal_taken = sim_data->start_time;
		next->philo->sim_stopped = 0;
		context->philo = next;
		pthread_create(&(next->philo->routine), NULL, &philo_routine, context);
		next = next->next_philo;
	}
}

void	end_threads(t_simulation *sim_data)
{
	t_lst	*next;
	int		nr_philos;

	next = sim_data->philosophers;
	nr_philos = 0;
	// while (next)
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		pthread_join(next->philo->routine, NULL);
		next = next->next_philo;
	}
}

void	simulation(t_simulation *sim_data)
{
	// printf("sim:set:before\n");
	set_philo_state_values(sim_data);
	// printf("sim:set:after\n");
	initialize_philo_mutexes(sim_data);
	// printf("bug in initialize mutex\n");
	// printf("sim:while:before\n");
	start_threads(sim_data);
	end_threads(sim_data);
	// printf("sim:while:after\n");
	destroy_philo_mutexes(sim_data);
}

int	main(int argc, char *argv[])
{
	t_simulation	*sim_data;

	// t_philosopher *philo_head;
	(void)argc;
	sim_data = (t_simulation *)malloc(sizeof(t_simulation));
	sim_data->nr_of_philos = ft_atoi(argv[1]);
	sim_data->time_to_die = ft_atoi(argv[2]);
	sim_data->eat_duration = ft_atoi(argv[3]);
	sim_data->sleep_duration = ft_atoi(argv[4]);
	if (argc == 6)
		sim_data->minimum_meals = ft_atoi(argv[5]);
	else
		sim_data->minimum_meals = -1;
	sim_data->philosophers = NULL;
	// printf("%d %d %d %d\n", philo_nr, eat_duration, think_duration,
	// sleep_duration);
	// philo_head = (t_philosopher*)malloc(sizeof(t_philosopher)*philo_nr);
	initialize_philo_list(&sim_data->philosophers, sim_data->nr_of_philos);
	// printf("before\n");
	simulation(sim_data);
	// printf("after\n");
	// print_philo_list(&sim_data->philosophers);
}

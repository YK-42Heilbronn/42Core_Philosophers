/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 13:05:35 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/03 16:42:47 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	time_elapsed_in_sim(suseconds_t start_time,
		suseconds_t current_time)
{
	return (current_time - start_time);
}

int get_sim_stopped(t_simulation *sim_data)
{
	int stopped;

	pthread_mutex_lock(&(sim_data->state_mutex));
	stopped = sim_data->sim_stopped;
	pthread_mutex_unlock(&(sim_data->state_mutex));
	return (stopped);
}

void set_sim_stopped(t_simulation *sim_data, int value)
{
	pthread_mutex_lock(&(sim_data->state_mutex));
	sim_data->sim_stopped = value;
	pthread_mutex_unlock(&(sim_data->state_mutex));
}

int get_all_eaten_min_meals(t_simulation *sim_data)
{
	int all_eaten;

	pthread_mutex_lock(&(sim_data->state_mutex));
	all_eaten = sim_data->all_eaten_min_meals;
	pthread_mutex_unlock(&(sim_data->state_mutex));
	return (all_eaten);
}

int	simulation_stops(t_lst *philo_node)
{
	t_philosopher	*philo;

	philo = philo_node->philo;
	// printf("in simulation stops\n");
	// set_sim_stopped(philo->sim_data, 0);
	if (get_sim_stopped(philo->sim_data))
	{
		return (get_sim_stopped(philo->sim_data));
	}
	// // printf("in simulation stops: sim_stopped:: before%d\n", philo->sim_data->sim_stopped);
	// stop = is_all_philos_reached_minimum_meals(philo_node)
	// 	|| is_philo_dead(philo_node);
	// // printf("in simulation stops: sim_stopped:: after%d\n", philo->sim_data->sim_stopped);
	// set_sim_stopped(philo->sim_data, stop);
	// if (get_sim_stopped(philo->sim_data))
	// {
	// 	died(philo_node);
	// }
	if (is_philo_dead(philo_node))
	{
		set_sim_stopped(philo->sim_data, 1);
		died(philo_node);
		return (get_sim_stopped(philo->sim_data));
	}
	if (is_all_philos_reached_minimum_meals(philo_node))
	{
		set_sim_stopped(philo->sim_data, 1);
		return (get_sim_stopped(philo->sim_data));
	}
	// if (is_all_philos_reached_minimum_meals(philo_node) || is_philo_dead(philo_node))
	// {
	// 	// died(philo, current_time()-philo->sim_start_time);
	// 	pthread_mutex_lock(&(philo->sim_data->state_mutex));
	// 	philo->sim_data->sim_stopped = 1;
	// 	died(philo_node);
	// 	pthread_mutex_unlock(&(philo->sim_data->state_mutex));
	// }
	// // else if ()
	// // {
	// // 	died(philo, current_time());
	// // 	t_context->sim_stopped = 1;
	// // }
	// else
	// {
	// 	pthread_mutex_lock(&(philo->sim_data->state_mutex));
	// 	philo->sim_data->sim_stopped = 0;
	// 	pthread_mutex_unlock(&(philo->sim_data->state_mutex));
	// }
	// printf("in simulation stops: sim_stopped:: end%d\n", philo->sim_data->sim_stopped);
	return (get_sim_stopped(philo->sim_data));
}

int	is_all_philos_reached_minimum_meals(t_lst *philo_node)
{
	t_simulation *sim_data;
	t_lst	*nxt_philo;
	int		nr_philos;

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
			break;
		}
		nxt_philo = nxt_philo->next_philo;
	}
	// printf("philo_all_eaten:: %d\n", sim_data->all_eaten_min_meals);
	return (get_all_eaten_min_meals(sim_data));
}

int	is_philo_dead(t_lst *philo_node)
{
	t_philosopher *philo;
	suseconds_t	time_since_last_meal;
	philo = philo_node->philo;

	time_since_last_meal = time_elapsed_in_sim(philo->last_meal_taken,
			current_time());
	// printf("in is_philo_dead\n");
	// printf("last meal:: %ld %d\n", time_since_last_meal, philo->time_to_die * 1000);
	if (time_since_last_meal >= philo->time_to_die * 1000)
	{
		return (1);
	}
	return (0);
}

// create ds - existence
// thread func
// it is an routine of an single philosopher
void	*philo_routine(void *p_node)
{
	t_lst				*philo_node;
	// t_thread_context	*context;

	// context = (t_thread_context *)t_context;
	philo_node = (t_lst*)p_node;
	while (1)
	{
		// printf("philo_routine: philo_nr:: %d\n", philo_node->philo->nr);
		if (philo_node->philo->nr % 2 == 0)
		{
			if (get_sim_stopped(philo_node->philo->sim_data))
				break;
			eating(philo_node);
			if (get_sim_stopped(philo_node->philo->sim_data))
				break;
			sleeping(philo_node);
			if (get_sim_stopped(philo_node->philo->sim_data))
				break;
			thinking(philo_node);
		}
		else
		{
			if (get_sim_stopped(philo_node->philo->sim_data))
				break;
			sleeping(philo_node);
			if (get_sim_stopped(philo_node->philo->sim_data))
				break;
			thinking(philo_node);
			if (get_sim_stopped(philo_node->philo->sim_data))
				break;
			if (philo_node->philo->sim_data->philosophers->next_philo == NULL)
			{
				single_philo_eating(philo_node);
				break;
			}
			else
				eating(philo_node);
		}
	}
	return (NULL);
}
// void clean_threads(t_simulation sim_data)
// {

// }
void	start_threads(t_simulation *sim_data)
{
	t_lst				*next;
	int					nr_philos;

	next = sim_data->philosophers;
	nr_philos = 0;
	sim_data->start_time = current_time();
	// context = (t_thread_context *)malloc(sizeof(t_thread_context));
	// context->sim_data = sim_data;
	// while (next)
	while (nr_philos++ < sim_data->nr_of_philos)
	{
		// next->philo->sim_start_time = sim_data->start_time;
		next->philo->last_meal_taken = sim_data->start_time;
		// next->philo->sim_stopped = 0;
		// context->philo = next;
		// status = pthread_create(&(next->philo->routine), NULL, &philo_routine, next);
		pthread_create(&(next->philo->routine), NULL, &philo_routine, next);
		// if (status != 0)
		// {

		// }
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
	// set_philo_state_values(sim_data, die_time, eat_time, sleep_time);
	// printf("sim:initialize:before\n");
	initialize_philo_mutexes(sim_data);
	// printf("bug in initialize mutex\n");
	// printf("sim:start:before\n");
	start_threads(sim_data);
	// printf("sim:start:after\n");
	end_threads(sim_data);
	// printf("sim:end:after\n");
	destroy_philo_mutexes(sim_data);
	free_philo_lst(sim_data, sim_data->nr_of_philos);
	// printf("sim:destroy:after\n");
}

int	main(int argc, char *argv[])
{
	t_simulation	*sim_data;
	int philos;
	int die_t;
	int eat_t;
	int sleep_t;
	int min_meals;

	// t_philosopher *philo_head;
	if (argc == 5 || argc == 6)
	{
		if (parse_argv(argv, &philos, &die_t, &eat_t, &sleep_t) == 1)
		{
			printf("Error: invalid argument\n");
			return (1);
		}
		sim_data = (t_simulation *)malloc(sizeof(t_simulation));
		if (sim_data == NULL)
			return (1);
		sim_data->nr_of_philos = philos;
		sim_data->all_eaten_min_meals = 0;
		sim_data->sim_stopped = 0;
		if (argc == 6)
		{
			min_meals = ft_satoi(argv[5]);
			if (min_meals <= 0)
			{
				printf("Error: invalid argument\n");
				return (1);
			}
			sim_data->minimum_meals = min_meals;
		}
		else
			sim_data->minimum_meals = 0;
		sim_data->philosophers = NULL;
		if (!initialize_philo_list(sim_data, die_t, eat_t, sleep_t))
			return(1);
		simulation(sim_data);
		return (0);
	}
	else
	{
		printf("Error: invalid number of arguments\n");
		return (1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:18:35 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/05 14:36:56 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_simulation	t_simulation;

typedef struct s_philosopher
{
	int						nr;
	int						fork;
	int						meals_count;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	suseconds_t				last_meal_taken;

	pthread_mutex_t			fork_mutex;
	pthread_mutex_t			meal_mutex;
	pthread_mutex_t			last_meal_mutex;

	pthread_t				routine;
	t_simulation			*sim_data;
}							t_philosopher;

typedef struct s_lst
{
	t_philosopher			*philo;
	struct s_lst			*next_philo;
}							t_lst;

typedef struct s_simulation
{
	int						nr_of_philos;
	int						minimum_meals;
	int						all_eaten_min_meals;
	int						sim_stopped;

	suseconds_t				start_time;

	pthread_mutex_t			state_mutex;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			stop_mutex;

	t_lst					*philosophers;
}							t_simulation;

// lnk_list.c
t_lst						*new_lst(t_philosopher *philo);
void						ft_lstadd_front(t_lst **lst, t_lst *new);
void						ft_lstadd_back(t_lst **lst, t_lst *new);
void						ft_lstclear(t_lst **lst, void (*del)(void *));

// states.c
void						fork_taken(t_lst *philo_node);
void						eating(t_lst *philo_node);
void						single_philo_eating(t_lst *philo_node);
void						sleeping(t_lst *philo_node);
void						thinking(t_lst *philo_node);
void						died(t_lst *philo_node);

// parsing.c
int							parse_argv(char *argv[], int ind, int *ptr);

// philo.c
void						*philo_routine(void *p_node);
int							are_philos_minimum_meals_done(t_lst *philo_node);
int							is_philo_dead(t_lst *philo_node);

// states_update1.c
void						update_forks_state(t_lst *philo_node, int state,
								int left_or_right);
int							get_philo_meals_count(t_lst *philo_node);
void						update_philo_meals_count(t_lst *philo_node);
void						update_philo_last_meal_taken(t_lst *philo_node);
void						update_all_eaten_min_meals(t_simulation *sim_data,
								int value);

// states_update2.c
int							get_sim_stopped(t_simulation *sim_data);
void						set_sim_stopped(t_simulation *sim_data, int value);
int							get_all_eaten_min_meals(t_simulation *sim_data);
void						update_all_eaten_min_meals(t_simulation *sim_data,
								int value);

// simulation.c
suseconds_t					time_elapsed_in_sim(suseconds_t start_time,
								suseconds_t current_time);
int							simulation_stops(t_lst *philo_node);
void						start_threads(t_simulation *sim_data);
void						end_threads(t_simulation *sim_data);
void						simulation(t_simulation *sim_data);

// utils.c
suseconds_t					current_time(void);
void						destroy_philo_mutexes(t_simulation *sim_data);
void						initialize_philo_mutexes(t_simulation *sim_data);
int							initialize_philo_list(t_simulation *sim_data,
								int time_to_die, int eat_duration,
								int sleep_duration);
void						free_philo_lst(t_simulation *sim_data,
								int nr_philos);

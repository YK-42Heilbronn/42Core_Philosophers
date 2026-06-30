/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:18:35 by ykonka            #+#    #+#             */
/*   Updated: 2026/06/30 15:40:26 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// typedef struct s_states_duration
// {
// 	int	thinking;
// 	int	eating;
// 	int	sleeping;
// }		t_states_duration;

typedef enum e_states
{
	THINKING = 1,
	EATING = 2,
	SLEEPING = 3
}					t_states;

typedef struct s_philosopher
{
	int				nr;
	int fork; // state: [taken(1) or returned(0)]
	int				meals_count;
	int minimum_meals;           // if minimum meals done, stop simulatiion
	suseconds_t last_meal_taken; // if current_time - last_meal_taken >= time_to_die, stop simulation
	int time_to_die;             // milliseconds
	int time_to_eat;             // milliseconds
	int time_to_sleep;           // milliseconds
	int all_eaten_min_meals;
	int				sim_stopped;
	suseconds_t sim_start_time;  // if current_time - sim_start_time >= time_to_die, stop simulation
	pthread_mutex_t	reserve_resource;
	pthread_mutex_t print_mutex;
	pthread_mutex_t meal_mutex;
	pthread_mutex_t sim_stop_mutex;
	pthread_mutex_t last_meal_taken_mutex;
	pthread_t routine; // thread handles both start - end mechanisms
}					t_philosopher;

typedef struct s_lst
{
	t_philosopher	*philo;
	struct s_lst	*next_philo;
}					t_lst;

typedef struct s_simulation
{
	int				nr_of_philos;
	int				eat_duration;
	int				sleep_duration;
	int				time_to_die;
	int				minimum_meals;
	suseconds_t		start_time;
	t_lst			*philosophers;
}					t_simulation;

typedef struct s_thread_context
{
	t_lst			*philo;
	t_simulation	*sim_data;
}					t_thread_context;

// utils.c
void				initialize_philo_mutexes(t_simulation *sim_data);
void				destroy_philo_mutexes(t_simulation *sim_data);
void				set_philo_state_values(t_simulation *sim_data);
void				print_philo_list(t_simulation *sim_data);
suseconds_t			current_time(void);
void				initialize_philo_list(t_lst **philo_head, int philo_nr);

// states.c
void				fork_taken(t_philosopher *philo, suseconds_t time_ms);
void				eating(t_thread_context *t_context, suseconds_t time_us);
void				sleeping(t_thread_context *t_context, suseconds_t time_us);
void				thinking(t_thread_context *t_context, suseconds_t time_us);
void				died(t_philosopher *philo, suseconds_t time_ms);

// parsing.c
int					ft_atoi(const char *str);

// philo.c
void				initialize_philo_list(t_lst **philo_head, int philo_nr);

// lnk_list.c
t_lst				*new_lst(t_philosopher *philo);
void				ft_lstadd_front(t_lst **lst, t_lst *new);
void				ft_lstadd_back(t_lst **lst, t_lst *new);
void				ft_lstclear(t_lst **lst, void (*del)(void *));

// main.c
int					simulation_stops(t_thread_context *t_context);
void				update_forks_state(t_lst *philo_node, int state);
void				update_philo_meals_count(t_lst *philo_node);
void				update_philo_last_meal_taken(t_lst *philo_node);
void end_threads(t_simulation *sim_data);
int	is_all_philos_reached_minimum_meals(t_simulation *sim_data);
int	is_philo_dead(t_philosopher *philo);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:18:35 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/01 16:46:58 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_simulation t_simulation;

typedef struct s_philosopher
{
    int             nr;
    int             fork;
    int             meals_count;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
	suseconds_t     last_meal_taken;

    pthread_mutex_t reserve_resource;
    pthread_mutex_t meal_mutex;
    pthread_mutex_t last_meal_mutex;

    pthread_t       routine;
    t_simulation    *sim_data;   // NEW: back-pointer to global simulation
}   t_philosopher;

typedef struct s_lst
{
    t_philosopher   *philo;
    struct s_lst    *next_philo;
}   t_lst;

typedef struct s_simulation
{  // global
    int             nr_of_philos;    // read-only after init
    int             minimum_meals;   // read-only after init
    int             all_eaten_min_meals;    // read-write after init
    int             sim_stopped;    		// read-write after init

	suseconds_t     start_time;     // read-only after init

    pthread_mutex_t sim_stop_mutex;
    pthread_mutex_t print_mutex;

    t_lst           *philosophers;  // head of linked list
}   t_simulation;

// utils.c
suseconds_t			current_time(void);
void				print_philo_list(t_simulation *sim_data);
void				destroy_philo_mutexes(t_simulation *sim_data);
void				initialize_philo_mutexes(t_simulation *sim_data);
void				initialize_philo_list(t_simulation *sim_data, int time_to_die, int eat_duration, int sleep_duration);

// states.c
void				fork_taken(t_philosopher *philo, suseconds_t time_ms);
void				eating(t_philosopher *philo, suseconds_t time_us);
void				sleeping(t_philosopher *philo, suseconds_t time_us);
void				thinking(t_philosopher *philo, suseconds_t time_us);
void				died(t_philosopher *philo, suseconds_t time_ms);

// parsing.c
int					ft_atoi(const char *str);

// philo.c

// lnk_list.c
t_lst				*new_lst(t_philosopher *philo);
void				ft_lstadd_front(t_lst **lst, t_lst *new);
void				ft_lstadd_back(t_lst **lst, t_lst *new);
void				ft_lstclear(t_lst **lst, void (*del)(void *));

// main.c
// int					simulation_stops(t_thread_context *t_context);
void end_threads(t_simulation *sim_data);
int	is_all_philos_reached_minimum_meals(t_philosopher *philo);
int	is_philo_dead(t_philosopher *philo);

// states_update.c
void				update_forks_state(t_lst *philo_node, int state);
void				update_philo_meals_count(t_lst *philo_node);
void				update_philo_last_meal_taken(t_lst *philo_node);


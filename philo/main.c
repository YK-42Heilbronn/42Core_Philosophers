/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 11:42:49 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/04 14:30:10 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_sim_data_values(t_simulation **sim_info)
{
	t_simulation	*sim_data;

	sim_data = *sim_info;
	sim_data->all_eaten_min_meals = 0;
	sim_data->sim_stopped = 0;
	sim_data->minimum_meals = 0;
	sim_data->philosophers = NULL;
}

int	main(int argc, char *argv[])
{
	t_simulation	*sim_data;
	int				die_t;
	int				eat_t;
	int				sleep_t;

	if (argc == 5 || argc == 6)
	{
		sim_data = (t_simulation *)malloc(sizeof(t_simulation));
		if (sim_data == NULL)
			return (1);
		if (parse_argv(argv, 1, &(sim_data->nr_of_philos)) == 1
			|| parse_argv(argv, 2, &die_t) == 1 || parse_argv(argv, 3,
				&eat_t) == 1 || parse_argv(argv, 4, &sleep_t) == 1)
			return (printf("Error: invalid argument\n"), free(sim_data), 1);
		set_sim_data_values(&sim_data);
		if (argc == 6 && parse_argv(argv, 5, &(sim_data->minimum_meals)) == 1)
			return (printf("Error: invalid argument\n"), free(sim_data), 1);
		if (!initialize_philo_list(sim_data, die_t, eat_t, sleep_t))
			return (free(sim_data), 1);
		simulation(sim_data);
		return (0);
	}
	else
		return (printf("Error: invalid number of arguments\n"), 1);
}

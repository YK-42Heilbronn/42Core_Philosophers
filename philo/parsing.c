/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 13:14:49 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/04 15:44:55 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str, long *val)
{
	long	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - 48);
	if (*str == '\0')
	{
		*val = result;
		return (1);
	}
	return (0);
}

static int	ft_satoi(const char *str)
{
	int		minus;
	long	result;

	minus = 1;
	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == 45 || *str == 43)
	{
		minus = 44 - *str;
		str++;
	}
	if (ft_atoi(str, &result) == 1 && minus == 1)
		return (result * minus);
	else
		return (-1);
}

// *die_t = ft_satoi(argv[2]);
// *eat_t = ft_satoi(argv[3]);
// *sleep_t = ft_satoi(argv[4]);
int	parse_argv(char *argv[], int ind, int *ptr)
{
	*ptr = ft_satoi(argv[ind]);
	if (*ptr <= 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lnk_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykonka <ykonka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:02:24 by ykonka            #+#    #+#             */
/*   Updated: 2026/07/04 12:24:31 by ykonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_lst	*new_lst(t_philosopher *philo)
{
	t_lst	*new_lst;

	new_lst = (t_lst *)malloc(sizeof(t_lst));
	if (new_lst == NULL)
		return (NULL);
	new_lst->philo = philo;
	new_lst->next_philo = NULL;
	return (new_lst);
}

void	ft_lstadd_front(t_lst **lst, t_lst *new)
{
	if (*lst == NULL)
		*lst = new;
	new->next_philo = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*list;

	list = *lst;
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (list->next_philo)
	{
		list = list->next_philo;
	}
	list->next_philo = new;
}

void	ft_lstclear(t_lst **lst, void (*del)(void *))
{
	t_lst	*list;

	list = *lst;
	while (list)
	{
		del(list->philo);
		free(list);
		list = list->next_philo;
	}
}

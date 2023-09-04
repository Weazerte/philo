/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:08:00 by eaubry            #+#    #+#             */
/*   Updated: 2023/08/30 13:49:21 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_end_sim(t_philo *philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo->data->end_mutex); 
	if (philo->data->end_sim == 1)
		res = 1;
	pthread_mutex_unlock(&philo->data->end_mutex);
	return (res);
}
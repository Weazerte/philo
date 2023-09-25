/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:08:00 by eaubry            #+#    #+#             */
/*   Updated: 2023/09/25 18:06:35 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_end_sim_moni(t_moni *monitoring)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&monitoring->data->end_mutex);
	if (monitoring->data->end_sim == 1)
		res = 1;
	pthread_mutex_unlock(&monitoring->data->end_mutex);
	return (res);
}

int	simu_delay(long int start_time)
{
	while (time_now() < start_time)
		continue ;
	return (0);
}

int	check_max_iter(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->iter_mutex);
		if (data->philo[i].iteration < data->max_iter)
		{
			pthread_mutex_unlock(&data->iter_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->iter_mutex);
		i++;
	}
	return (0);
}

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

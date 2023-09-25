/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weaz <weaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:42:22 by weaz              #+#    #+#             */
/*   Updated: 2023/09/24 05:45:38 by weaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitoring_routine(void *data_ptr)
{
	int	i;
	long int	now;
	
	t_data *data = (t_data *)data_ptr;
	simu_delay(data->start_time);
	while (ft_end_sim_moni(data->monitoring) == 0)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->m_lst_meal);
			now = time_now() - data->philo[i].lst_meal;
			if (now >= data->ttd)
			{
				pthread_mutex_lock(&data->end_mutex);
				data->end_sim = 1;
				pthread_mutex_unlock(&data->end_mutex);
			}
			pthread_mutex_unlock(&data->m_lst_meal);
			i++;
		}
	}
	return (NULL);
}

void	*monitoring_routine_max_iter(void *data_ptr)
{
	int	i;
	long int	now;
	
	t_data *data = (t_data *)data_ptr;
	simu_delay(data->start_time);
	while (ft_end_sim_moni(data->monitoring) == 0)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->m_lst_meal);
			now = time_now() - data->philo[i].lst_meal;
			if (now >= data->ttd || check_max_iter(data) == 0)
			{
				pthread_mutex_lock(&data->end_mutex);
				data->end_sim = 1;
				pthread_mutex_unlock(&data->end_mutex);
			}
			pthread_mutex_unlock(&data->m_lst_meal);
			i++;
		}
	}
	return (NULL);
}

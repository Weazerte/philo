/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:08:00 by eaubry            #+#    #+#             */
/*   Updated: 2023/09/07 14:03:31 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_end_sim_moni(t_moni *monitoring)
{
	int	res;

	res = 0;
	
	printf("%p", monitoring->data);
	pthread_mutex_lock(&monitoring->data->end_mutex);
	printf("qfq\n");
	if (monitoring->data->end_sim == 1)
		res = 1;
	pthread_mutex_unlock(&monitoring->data->end_mutex);
	return (res);
}

void	*monitoring_routine(void *data_ptr)
{
	int	i;
	
	t_moni *monitoring = (t_moni *)data_ptr;
	printf("jsuis la \n");
	while (ft_end_sim_moni(monitoring) == 0)
	{
		i = 0;
		printf("jsuis ici \n");
		while (i < monitoring->data->number_of_philosophers)
		{
			if (monitoring->data->philo[i].lst_meal + monitoring->data->ttd > time_now())
				{
					pthread_mutex_lock(&monitoring->data->end_mutex);
					monitoring->data->end_sim = 1;
					pthread_mutex_unlock(&monitoring->data->end_mutex);
					break;
				}
			i++;
		}
	}
	return (NULL);
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
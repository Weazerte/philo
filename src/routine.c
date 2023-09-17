/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:40:16 by eaubry            #+#    #+#             */
/*   Updated: 2023/09/05 15:05:33 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void to_do(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_mutex[philo->left_fork]);
	print_philo(0, philo);
	pthread_mutex_lock(&philo->data->fork_mutex[philo->right_fork]);
	print_philo(0, philo);
	philo_is_eating(philo);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->left_fork]);	
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->right_fork]);
	philo_is_sleeping(philo);
}

void	*thread_routine(void *data_ptr)
{
	t_philo *philo = (t_philo *)data_ptr;
	while(time_now() < philo->data->start_time)
		continue;
	if (philo->id % 2 == 1)
				ft_usleep(philo->data->tte);
	while (ft_end_sim(philo) == 0)
		to_do(philo);
	return (NULL);
}

void	ft_routine(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = time_now() + (data->number_of_philosophers * 20);
	pthread_create(&data->monitoring->tid, NULL, &monitoring_routine, &data->monitoring);
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philo[i].tid, NULL, &thread_routine, &data->philo[i]);
		i++;
	}
}
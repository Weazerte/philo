/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weaz <weaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:08:00 by eaubry            #+#    #+#             */
/*   Updated: 2023/09/26 23:10:08 by weaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_end_philo(t_philo *philo, int who)
{
	if (check_max_iter(philo->data) == 0 || ft_end_sim(philo->data) == 1)
	{
		if (who == 1)
			pthread_mutex_unlock(&philo->data->fork_mutex[philo->left_fork]);
		if (who == 2)
		{
			pthread_mutex_unlock(&philo->data->fork_mutex[philo->left_fork]);
			pthread_mutex_unlock(&philo->data->fork_mutex[philo->right_fork]);
		}
		return (1);
	}
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

int	ft_end_sim(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->end_mutex);
	if (data->end_sim == 1)
		res = 1;
	pthread_mutex_unlock(&data->end_mutex);
	return (res);
}

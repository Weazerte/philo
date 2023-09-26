/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:08:00 by eaubry            #+#    #+#             */
/*   Updated: 2023/09/26 16:43:53 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// void	start_fcked_routine(t_data *data)
// {
// 		int	i;

// 	i = -1;
// 	while (++i < data->number_of_philosophers)
// 		pthread_create(&data->philo[i].tid, NULL,
// 			&fcked_routine, &data->philo[i]);
// 	if (data->max_iter == -1)
// 		pthread_create(&data->monitoring->tid, NULL,
// 			&monitoring_routine, data);
// 	else
// 		pthread_create(&data->monitoring->tid, NULL,
// 			&monitoring_routine_max_iter, data);
// 	i = -1;
// 	while (++i < data->number_of_philosophers)
// 	{
// 		pthread_mutex_lock(&data->m_lst_meal[data->philo[i].id]);
// 		data->philo[i].lst_meal = data->start_time;
// 		pthread_mutex_unlock(&data->m_lst_meal[data->philo[i].id]);
// 	}
// }

// void	fcked_routine(void *data_ptr)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)data_ptr;
// 	simu_delay(philo->data->start_time);
// 	if (philo->data->number_of_philosophers == 1)
// 	{
// 		print_philo(0, philo);
// 		return (NULL);
// 	}
// 	if (philo->id % 2 == 0)
// 		ft_usleep(philo->data->tte * 0.9 + 1);
// 	if ((philo->data->number_of_philosophers % 2 == 1)
// 		&& (philo->id == (philo->data->number_of_philosophers - 1)))
// 		ft_usleep(philo->data->tte);
	
// }

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

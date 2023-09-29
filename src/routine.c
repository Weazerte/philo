/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:40:16 by eaubry            #+#    #+#             */
/*   Updated: 2023/09/29 13:38:13 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_philo(int who, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->can_i == 0)
	{
		if (who == 0)
			printf("%ld %d has taken a fork\n",
				(time_now() - philo->data->start_time), philo->id + 1);
		else if (who == 1)
			printf("%ld %d is eating\n",
				(time_now() - philo->data->start_time), philo->id + 1);
		else if (who == 2)
			printf("%ld %d is sleeping\n",
				(time_now() - philo->data->start_time), philo->id + 1);
		else if (who == 3)
			printf("%ld %d is thinking\n",
				(time_now() - philo->data->start_time), philo->id + 1);
		else if (who == 4)
			printf("%ld %d died\n",
				(time_now() - philo->data->start_time), philo->id + 1);
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	philo_is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_mutex[philo->left_fork]);
	print_philo(0, philo);
	pthread_mutex_lock(&philo->data->fork_mutex[philo->right_fork]);
	print_philo(0, philo);
	pthread_mutex_lock(&philo->data->m_lst_meal[philo->id]);
	philo->lst_meal = time_now();
	pthread_mutex_unlock(&philo->data->m_lst_meal[philo->id]);
	print_philo(1, philo);
	ft_usleep(philo->data->tte);
	pthread_mutex_lock(&philo->data->iter_mutex);
	++philo->iteration;
	pthread_mutex_unlock(&philo->data->iter_mutex);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->right_fork]);
}

void	philo_is_sleeping(t_philo *philo)
{
	print_philo(2, philo);
	ft_usleep(philo->data->tts);
	if (ft_end_sim(philo->data) == 0)
		return ;
	print_philo(3, philo);
}

void	*thread_routine(void *data_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)data_ptr;
	simu_delay(philo->data->start_time);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->tte * 0.9 + 1);
	if ((philo->data->number_of_philosophers % 2 == 1)
		&& (philo->id == (philo->data->number_of_philosophers - 1)))
		ft_usleep(philo->data->tte);
	if (philo->data->number_of_philosophers == 1)
	{
		print_philo(0, philo);
		return (NULL);
	}
	while (ft_end_sim(philo->data) == 0)
	{
		philo_is_eating(philo);
		philo_is_sleeping(philo);
	}
	return (NULL);
}

void	ft_routine(t_data *data)
{
	int	i;

	i = -1;
	if (data->ttd <= (data->tte + data->tts))
		start_fcked_routine(data);
	else
	{
		data->start_time = time_now() + (data->number_of_philosophers * 20);
		while (++i < data->number_of_philosophers)
			pthread_create(&data->philo[i].tid, NULL,
				&thread_routine, &data->philo[i]);
		if (data->max_iter == -1)
			pthread_create(&data->monitoring->tid, NULL,
				&monitoring_routine, data);
		else
			pthread_create(&data->monitoring->tid, NULL,
				&monitoring_routine_max_iter, data);
		i = -1;
		while (++i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->m_lst_meal[data->philo[i].id]);
			data->philo[i].lst_meal = data->start_time;
			pthread_mutex_unlock(&data->m_lst_meal[data->philo[i].id]);
		}
	}
}

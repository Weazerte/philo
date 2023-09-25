/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weaz <weaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:45:01 by weaz              #+#    #+#             */
/*   Updated: 2023/09/24 06:00:09 by weaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_philo(int	who, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (who == 0)
		printf("%ld %d as taken a fork\n", time_now(), philo->id + 1);
	else if (who == 1)
		printf("%ld %d is eating\n", time_now(), philo->id + 1);
	else if (who == 2)
		printf("%ld %d is sleeping\n", time_now(), philo->id + 1);
	else if (who == 3)
		printf("%ld %d is thinking\n", time_now(), philo->id + 1);
	else if (who == 4)
		printf("%ld %d died\n", time_now(), philo->id + 1);
	pthread_mutex_unlock(&philo->data->print);
}

void	philo_is_eating(t_philo *philo)
{
	print_philo(1, philo);
	pthread_mutex_lock(&philo->data->m_lst_meal);
	philo->lst_meal = time_now();
	pthread_mutex_unlock(&philo->data->m_lst_meal);
	ft_usleep(philo->data->tte);
}

void	philo_is_sleeping(t_philo *philo)
{
	print_philo(2, philo);
	ft_usleep(philo->data->tts);
	print_philo(3, philo);
}

int	ft_destroy_mutex(t_data *data)
{
	int	i;
	
	pthread_mutex_destroy(&data->end_mutex);
	pthread_mutex_destroy(&data->iter_mutex);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->m_lst_meal);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->fork_mutex[i]);
	free(data->fork_mutex);
	return (0);
}

void	ft_free_init(t_data *data, char *s)
{
	free(data->philo);
	if (s[6] == 'm')
		free(data->fork_mutex);
	else if (s[6] == 'd' || s[6] == 'p')
		{
			free(data->fork_mutex);
			free(data->monitoring);
		}
	printf("%s\n", s);
}

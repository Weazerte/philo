/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:54:43 by eaubry            #+#    #+#             */
/*   Updated: 2023/09/15 12:59:57 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->fork_mutex[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print_philo, NULL))
		return (1);
	if (pthread_mutex_init(&data->last_meal_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->start_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (1);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].id = i;
		data->philo[i].iteration = 0;
		data->philo[i].data = data;
		data->philo[i].left_chopstick = i;
		data->philo[i].right_chopstick = (i + 1) % data->nb_philo;
		data->philo[i].last_meal = 0;
		i++;
	}
	if (i != data->nb_philo)
		return (1);
	return (0);
}

int	init_data_bis(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (ft_error("Error: malloc philos"));
	data->chopsticks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->chopsticks)
		return (ft_error("Error: malloc forks\n"));
	if (init_mutex(data))
	{
		free(data->philo);
		free(data->chopsticks);
		return (1);
	}
	if (init_philo(data))
	{
		free(data->philo);
		ft_destroy_mutex(data);
		return (1);
	}
	return (0);
}

int	init_data(int ac, char **av, t_data *data)
{
	if (ac >= 5)
	{
		data->nb_philo = ft_atolui(av[1]);
		data->ttd = ft_atolui(av[2]);
		data->tte = ft_atolui(av[3]);
		data->tts = ft_atolui(av[4]);
		data->start_time = get_time();
		data->max_iter = -1;
		data->end_sim = FALSE;
	}
	if (ac == 6)
		data->max_iter = ft_atolui(av[5]);
	if (data->nb_philo < 1 || data->max_iter == 0)
		return (ft_error("Error: invalid argument\n"));
	if (init_data_bis(data))
		return (1);
	return (0);
}
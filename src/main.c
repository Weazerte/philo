/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:36:24 by eaubry            #+#    #+#             */
/*   Updated: 2023/09/04 16:32:11 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_pars(t_data *data, char **av, int *ac)
{
	int	i;
	(void)*ac;
	(void)**av;
	// size_t	j;

	i = 0; 
	// while(*ac++)
	// {
	// 	j = 0;
	// 	while (j < ft_strlen(av[*ac]))
	// 	{
	// 		i += ft_isdigit(av[*ac][j]);
	// 		j++;
	// 	}
	// }
	// if (i != 0)
	// 	return (i);
	data->number_of_philosophers = ft_atoi(av[1]);
	// data->tte = ft_atoi(av[2]);
	// data->tts = ft_atoi(av[3]);
	// data->ttd = ft_atoi(av[2]);
	return (i);
}

long int	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int	ft_usleep(long int time)
{
	long int	n_time;

	n_time = time_now() + time;
	while (time_now() < n_time)
		usleep(100);
	return (1);
}

int	ft_init(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philo)
		return (-1);
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->fork_mutex)
	{
		free(data->philo);
		return (-1);
	}
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if(pthread_mutex_init(&data->fork_mutex[i], NULL) == -1)
		{
			free(data->philo);
			free(data->fork_mutex);
			return (1);
		}
	}
	if (pthread_mutex_init(&data->end_mutex, NULL) == -1)
	{
		free(data->philo);
		free(data->fork_mutex);
		return (1);
	}
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		data->philo[i].id = i;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->number_of_philosophers;
		data->philo[i].data = data;
	}
	return (0);
}


void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&data->end_mutex);
}

int	main(int ac, char **av)
{
	int	i;
	// if (ac != 5 && ac != 6)
	// {
		t_data data;
		data.end_sim = 0;
		
		if (ft_pars(&data, av, &ac) != 0)
			return (0);
		ft_init(&data);
		ft_routine(&data);
		i = 0;
		while (i < data.number_of_philosophers)
		{
			pthread_join(data.philo[i].tid, NULL);
			i++;
		}
		i = 0;
		ft_free(&data);
	// }
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:36:24 by eaubry            #+#    #+#             */
/*   Updated: 2023/08/28 17:19:54 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_pars(t_data *data, char **av, int *ac)
{
	int	i;
	(void)*ac;
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
	data->arg.number_of_philosophers = ft_atoi(av[1]);
	data->arg.time_to_die = ft_atoi(av[2]);
	data->arg.time_to_eat = ft_atoi(av[3]);
	data->arg.time_to_sleep = ft_atoi(av[4]);
	return (i);
}

void	*thread_routin(void *data)
{
	t_philo *philo = (t_philo *)data;
	printf("Im %ld\n", philo->tid);
	return (NULL);
}

int	main(int ac, char **av)
{
	int	i;
	// if (ac != 5 && ac != 6)
	// {
		t_data data;
		if (ft_pars(&data, av, &ac) != 0)
			return (0);
		i = 0;
		data.philo = malloc(sizeof(data.philo) * data.arg.number_of_philosophers + 1);
		while (i < data.arg.number_of_philosophers)
		{
			pthread_create(&data.philo[i].tid, NULL, &thread_routin, &data.philo[i]);
			i++;
		}
		i = 0;
		while (i < data.arg.number_of_philosophers)
		{
			pthread_join(data.philo[i].tid, NULL);
			i++;
		}
		free()
	// }

	
	return (0);
}
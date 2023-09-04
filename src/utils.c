/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:39:15 by eaubry            #+#    #+#             */
/*   Updated: 2023/09/04 16:39:34 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_philo(int	who, t_philo *philo)
{
	if (who == 0)
		printf("%d as taken a fork\n", philo->id + 1);
	else if (who == 1)
		printf("%d is eating\n", philo->id + 1);
	else if (who == 2)
		printf("%d is sleeping\n", philo->id + 1);
	else if (who == 3)
		printf("%d is thinking\n", philo->id + 1);
	else if (who == 4)
		printf("%d is died\n", philo->id + 1);
}

void	philo_is_eating(t_philo *philo)
{
	print_philo(1, philo);
	ft_usleep(200);
}

void	philo_is_sleeping(t_philo *philo)
{
	print_philo(2, philo);
	ft_usleep(200);
}
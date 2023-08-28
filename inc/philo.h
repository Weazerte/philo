/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:27:21 by eaubry            #+#    #+#             */
/*   Updated: 2023/08/28 16:56:12 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

typedef struct s_arg
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	
} t_arg ;

typedef struct s_philo
{
	int	id;
	pthread_t tid;
	int	data;
	
} t_philo;


typedef struct s_data
{
	unsigned int	*fork;
	pthread_mutex_t	*fork_mutex;
	t_philo *philo;
	t_arg arg;
	
} t_data ;

#endif
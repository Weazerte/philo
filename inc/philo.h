/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:27:21 by eaubry            #+#    #+#             */
/*   Updated: 2023/09/04 16:40:03 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <time.h>
#include <sys/time.h>

typedef struct s_data
{
	long int start_time;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t end_mutex;
	int	end_sim;
	int hm_eaten;
	struct s_philo *philo;
	struct s_moni *monitoring;
	int	number_of_philosophers;
	int	ttd;
	int	tte;
	int	tts;
	
} t_data ;

typedef struct s_moni
{
	pthread_t tid;
	
} t_moni;

typedef struct s_philo
{
	int	id;
	pthread_t tid;
	t_data	*data;
	int	left_fork;
	int	right_fork;
	
} t_philo;

void	ft_routine(t_data *data);

int	ft_end_sim(t_philo *philo);

long int	time_now(void);

int	ft_usleep(long int time);

int	ft_atoi(const char *nptr);

void	print_philo(int	who, t_philo *philo);

void	philo_is_eating(t_philo *philo);

void	philo_is_sleeping(t_philo *philo);

#endif
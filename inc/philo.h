/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weaz <weaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:27:21 by eaubry            #+#    #+#             */
/*   Updated: 2023/09/24 05:41:11 by weaz             ###   ########.fr       */
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
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t end_mutex;
	pthread_mutex_t m_lst_meal;
	pthread_mutex_t iter_mutex;
	pthread_mutex_t print;
	long int start_time;
	struct s_philo *philo;
	struct s_moni *monitoring;
	int	end_sim;
	int	number_of_philosophers;
	int	ttd;
	int	tte;
	int	tts;
	int max_iter;
	
} t_data ;

typedef struct s_moni
{
	pthread_t tid;
	t_data *data;
} t_moni;

typedef struct s_philo
{
	int	id;
	pthread_t tid;
	long int lst_meal;
	t_data	*data;
	int	left_fork;
	int	right_fork;
	int iteration;
	
} t_philo;

void	ft_routine(t_data *data);

int	ft_end_sim(t_philo *philo);

long int	time_now(void);

int	ft_usleep(long int time);

int	ft_atoi(const char *nptr);

void	print_philo(int	who, t_philo *philo);

void	philo_is_eating(t_philo *philo);

void	philo_is_sleeping(t_philo *philo);

void	*monitoring_routine(void *data_ptr);

void	*monitoring_routine_max_iter(void *data_ptr);

int	init_data(int ac, char **av, t_data *data);

int	simu_delay(long int start_time);

void	ft_free_init(t_data *data, char *s);

int	ft_destroy_mutex(t_data *data);

int	ft_isdigit(char c);

int	ft_end_sim_moni(t_moni *monitoring);

int	check_max_iter(t_data *data);

#endif
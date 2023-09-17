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
	
} t_philo;

#endif

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] && ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32)))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

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
	philo->lst_meal = time_now();
	ft_usleep(philo->data->tte);
}

void	philo_is_sleeping(t_philo *philo)
{
	print_philo(2, philo);
	ft_usleep(philo->data->tts);
}

int	ft_end_sim_moni(t_moni *monitoring)
{
	int	res;

	res = 0;
	
	pthread_mutex_lock(&monitoring->data->end_mutex); 
	printf("qfq\n");
	if (monitoring->data->end_sim == 1)
		res = 1;
	pthread_mutex_unlock(&monitoring->data->end_mutex);
	return (res);
}

void	*monitoring_routine(void *data_ptr)
{
	int	i;
	
	t_moni *monitoring = (t_moni *)data_ptr;
	printf("jsuis la \n");
	while (ft_end_sim_moni(monitoring) == 0)
	{
		i = 0;
		printf("jsuis ici \n");
		while (i < monitoring->data->number_of_philosophers)
		{
			if (monitoring->data->philo[i].lst_meal + monitoring->data->ttd > time_now())
				{
					pthread_mutex_lock(&monitoring->data->end_mutex);
					monitoring->data->end_sim = 1;
					pthread_mutex_unlock(&monitoring->data->end_mutex);
					break;
				}
			i++;
		}
	}
	return (NULL);
}

int	ft_end_sim(t_philo *philo)
{
	int	res;

	res = 0;
	
	pthread_mutex_lock(&philo->data->end_mutex); 
	if (philo->data->end_sim == 1)
		res = 1;
	pthread_mutex_unlock(&philo->data->end_mutex);
	return (res);
}

void to_do(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_mutex[philo->left_fork]);
			print_philo(0, philo);
			pthread_mutex_lock(&philo->data->fork_mutex[philo->right_fork]);
			print_philo(0, philo);
			philo_is_eating(philo);
			pthread_mutex_unlock(&philo->data->fork_mutex[philo->left_fork]);
			pthread_mutex_unlock(&philo->data->fork_mutex[philo->right_fork]);
			philo_is_sleeping(philo);
}

void	*thread_routine(void *data_ptr)
{
	t_philo *philo = (t_philo *)data_ptr;
	while(time_now() < philo->data->start_time)
		continue;
	if (philo->id % 2 == 1)
				ft_usleep(philo->data->tte);
	while (ft_end_sim(philo) == 0)
		to_do(philo);
	return (NULL);
}

void	ft_routine(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = time_now() + (data->number_of_philosophers * 20);
	pthread_create(&data->monitoring->tid, NULL, &monitoring_routine, &data->monitoring);
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philo[i].tid, NULL, &thread_routine, &data->philo[i]);
		i++;
	}
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
	data->monitoring = malloc(sizeof(t_moni));
	if (!data->monitoring)
	{
		free(data->philo);
		return (-1);
	}
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->fork_mutex)
	{
		free(data->philo);
		free(data->monitoring);
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
    data->number_of_philosophers = 4;
	data->tte = 410;
	data->tts = 200;
	data->ttd = 200;
	data->monitoring->data = data;
    data.end_sim = 0;
	return (0);
}


void	ft_free(t_data *data)
{
	int	i;

	free(data->philo);
	free(data->fork_mutex);
	free(data->monitoring);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&data->end_mutex);
}

int	main()
{
	int	i;
		t_data data;
		ft_init(&data);
		ft_routine(&data);
		i = 0;
		while (i < data.number_of_philosophers)
		{
			if (pthread_join(data.philo[i].tid, NULL) == -1)
                {
                    ft_free(&data);
                    return (0);
                }
			i++;
		}
		if (pthread_join(data.monitoring->tid, NULL) == -1)
            
		i = 0;
		ft_free(&data);
	return (0);
}

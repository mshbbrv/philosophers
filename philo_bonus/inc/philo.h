/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 23:16:53 by thjonell          #+#    #+#             */
/*   Updated: 2021/07/27 23:16:54 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>
# define EAT "is eating"
# define FORK "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"
# define RUN 1
# define STOP 0
# define FULL 2
# define LIGHT "\e[90m"
# define BOLD "\e[1m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define MAGENTA "\e[35m"
# define CYAN "\e[36m"
# define RED "\e[31m"
# define DEF "\e[0m"

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct s_data
{
	long			philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meals;
	int				full_count;
	int				status;
	struct timeval	all_started;
	sem_t			*forks;
	sem_t			*life_monitor;
	sem_t			*print_status;
	pthread_t		philos_th;
	pthread_t		life_monitor_th;
	t_philo			*philo_head;
};

struct s_philo
{
	int				id;
	int				status;
	struct timeval	last_meal_time;
	int				meals_count;
	pid_t			pid;
	pthread_t		pthread;
	t_data			*data;
	t_philo			*next;
};

int					ft_isdigit(int c);
long				ft_atoi(const char *str);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					error_handler(char *str, t_data *data);
int					check_options(int argc, char *argv[], t_data *data);
int					init_options(t_data *data, int argc, char *argv[]);
void				print_status(t_philo *philo, char *str);
struct timeval		timestamp(struct timeval start);
int					close_sem(t_data *data);
int					init_sem(t_data *data);
int					init_philo(t_data *data);
void				simulation(t_philo *philo);
int					start_simulation(t_data *data);
void				wait_child(t_philo *philo);
void				mysleep(long time);
void				kill_philos(t_philo *philo);
long				lifetime(t_philo *philo);
int					meals_monitor(t_data *data);
void				*life_monitor_thread(void *arg);
void				free_data(t_data *data);
#endif

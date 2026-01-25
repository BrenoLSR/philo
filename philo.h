/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:33:16 by brendos-          #+#    #+#             */
/*   Updated: 2026/01/25 11:33:21 by brendos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define _DEFAULT_SOURCE

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int					philos_nbr;
	long				start_time;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	int					limit_meals;
	int					stop_simulation;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock_mtx;
}						t_table;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long				meals_count;
	long				last_meal;
	t_table				*table;
}						t_philo;

void					clean_table(t_table *table);

long					ft_atol(const char *str);

void					*monitor_routine(void *arg);

int						parse_args(int argc, char **argv, t_table *table);

int						init_philos(t_table *table);

void					*philo_routine(void *arg);

int						sim_start(t_table *data);

int						init_table(t_table *table);

long					get_time_ms(void);
void					smart_sleep(t_table *table, long wakeup);

int						is_digit(char c);
int						is_space(char c);
void					safe_print(t_table *table, int id, const char *msg);
int						error(const char *msg);

#endif

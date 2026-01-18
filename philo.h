#ifndef PHILO_H
# define PHILO_H

# define _DEFAULT_SOURCE

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define THINK_TIME_MAX 600
# define CUT_THINK_TIME 200
# define SILENCE_THINK_MIN 1

typedef pthread_mutex_t	t_mutex;
typedef struct s_philo	t_philo;

typedef struct s_table
{
	pthread_t			monitor;
	int					philo_nbr;
	long long			start_time;
	long long			time_die;
	long long			time_eat;
	long long			time_sleep;
	int					limit_meals;
	bool				simulation_finish;
	t_mutex				sim_lock;
	struct s_philo		*philos;
	t_mutex				*forks;
	t_mutex				write_lock;
}						t_table;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	t_mutex				*left_fork;
	t_mutex				*right_fork;
	long				meals_count;
	t_mutex				eat_lock;
	long long			last_meal;
	t_table				*table;
}						t_philo;

// init_parsing.c
bool					parse_and_init(t_table *table, int ac, char **av,
							int i);
bool					init_create_philo(t_table *table);
bool					init_forks_mutex(t_table *table);

void					*philo_routine(void *data);
void					*monitor_routine(void *data);

// utils.c
long					get_time_ms(void);
void					*ft_calloc(size_t nmemb, size_t size);
long					ft_atol(char *str);

// clean
void					clean_philos(t_philo *philos, int i);
void					clean_forks(t_mutex *forks, int i);
void					clean_table(t_table *table);

bool					is_sim_end(t_table *table);
void					sync_start(time_t start);
void					msg_status(t_philo *philo, const char *msg,
							bool is_monitor);

#endif
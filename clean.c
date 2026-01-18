#include "philo.h"

void	clean_philos(t_philo *philos, int i)
{
	while (i--)
		pthread_mutex_destroy(&philos[i].eat_lock);
	free(philos);
}

void	clean_forks(t_mutex *forks, int i)
{
	while (i--)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
}

void	clean_table(t_table *table)
{
	if (!table)
		return ;
	if (table->philos)
		clean_philos(table->philos, table->philo_nbr);
	if (table->forks)
		clean_forks(table->forks, table->philo_nbr);
	pthread_mutex_destroy(&table->sim_lock);
	pthread_mutex_destroy(&table->write_lock);
	free(table);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:20:51 by brendos-          #+#    #+#             */
/*   Updated: 2026/01/18 16:20:55 by brendos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_positive_int_str(const char *str)
{
	size_t	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	if (!is_digit(str[i]))
		return (0);
	while (is_digit(str[i]))
		i++;
	while (is_space(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

static long	parse_positive_long(const char *str, const char *arg_name)
{
	long	value;

	if (!is_valid_positive_int_str(str))
	{
		printf("Error: invalid format for %s\n", arg_name);
		return (-1);
	}
	value = ft_atol(str);
	if (value < 0)
	{
		printf("Error: %s is invalid or too large\n", arg_name);
		return (-1);
	}
	if (value == 0)
	{
		printf("Error: %s must be greater than 0\n", arg_name);
		return (-1);
	}
	return (value);
}

int	parse_args(int argc, char **argv, t_table *table)
{
	table->philos_nbr = parse_positive_long(argv[1], "number_of_philosophers");
	table->time_die = parse_positive_long(argv[2], "time_to_die");
	table->time_eat = parse_positive_long(argv[3], "time_to_eat");
	table->time_sleep = parse_positive_long(argv[4], "time_to_sleep");
	if (table->philos_nbr <= 0 || table->time_die <= 0
		|| table->time_eat <= 0 || table->time_sleep <= 0)
		return (0);
	table->limit_meals = -1;
	if (argc == 6)
	{
		table->limit_meals = parse_positive_long(argv[5], "limit_meals");
		if (table->limit_meals <= 0)
			return (0);
	}
	return (1);
}

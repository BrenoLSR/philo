#include "philo.h"

long	ft_atol(char *str)
{
	long	result;

	result = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (0);
	if (*str < '0' || *str > '9')
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
			return (0);
		str++;
	}
	if (*str != '\0')
		return (0);
	return (result);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*i;

	i = (unsigned char *)s;
	while (n--)
	{
		*i = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*aloc;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (nmemb > ((size_t)-1) / size)
		return (NULL);
	total = nmemb * size;
	aloc = malloc(total);
	if (aloc == NULL)
		return (NULL);
	ft_bzero(aloc, total);
	return (aloc);
}

long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000
		+ (long long)time.tv_usec / 1000);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:24:56 by davli             #+#    #+#             */
/*   Updated: 2024/07/30 15:29:20 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_data(t_data **data, int argc, char **argv);
static int	ft_init_mutexes(t_data **data);
static int	ft_init_philos(t_philo **philo, t_data *data);

long	ft_atol(char *str)
{
	long	num;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (0);
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i++] - '0');
		if (num > INT_MAX)
			return (0);
	}
	return (num * sign);
}

int	init(t_philo **philo, t_data **data, int argc, char **argv)
{
	(*data) = malloc(sizeof(t_data));
	if (*data == NULL)
		return (0);
	(*data)->mutex = NULL;
	(*data)->th = NULL;
	if (ft_init_data(data, argc, argv) != 1)
		return (0);
	(*philo) = malloc(sizeof(t_philo) * (*data)->n_philos);
	if (*philo == NULL)
		return (0);
	(*philo)->fork = NULL;
	if (ft_init_philos(philo, *data) != 1)
		return (0);
	return (1);
}

static int	ft_init_data(t_data **d, int argc, char **argv)
{
	(*d)->t_start = ft_gettime();
	(*d)->n_philos = ft_atol(argv[1]);
	(*d)->t_death = ft_atol(argv[2]);
	(*d)->t_meal = ft_atol(argv[3]);
	(*d)->t_sleep = ft_atol(argv[4]);
	(*d)->t_think = 0;
	if (((*d)->n_philos % 2) \
		&& (((*d)->t_death - (*d)->t_meal - (*d)->t_sleep) / 2 > 0))
		(*d)->t_think = (((*d)->t_death - (*d)->t_meal - (*d)->t_sleep) / 2);
	(*d)->n_meals = -1;
	if (argc == 6)
	{
		(*d)->n_meals = ft_atol(argv[5]);
		if ((*d)->n_meals == -1)
			return (0);
	}
	(*d)->done = 0;
	(*d)->died = 0;
	if (!ft_init_mutexes(d))
		return (0);
	return (1);
}

static int	ft_init_mutexes(t_data **data)
{
	t_mutex	*mutex;
	int		i;

	mutex = malloc(sizeof(t_mutex) * MTX_NUM);
	if (mutex == NULL)
		return (0);
	i = 0;
	while (i < MTX_NUM)
		pthread_mutex_init(&mutex[i++], NULL);
	(*data)->mutex = mutex;
	return (1);
}

static int	ft_init_philos(t_philo **philo, t_data *data)
{
	t_mutex	*fork;
	int		i;

	fork = malloc(sizeof(t_mutex) * data->n_philos);
	if (!fork)
		return (0);
	i = 0;
	while (i < data->n_philos)
		pthread_mutex_init(&fork[i++], NULL);
	i = 0;
	while (i < data->n_philos)
	{
		(*philo)[i].id = (i + 1);
		(*philo)[i].last_meal = data->t_start;
		(*philo)[i].meal_count = 0;
		(*philo)[i].l_fork = i;
		if ((i - 1) < 0)
			(*philo)[i].r_fork = (data->n_philos - 1);
		else
			(*philo)[i].r_fork = (i - 1);
		(*philo)[i].fork = fork;
		(*philo)[i].data = data;
		++i;
	}
	return (1);
}

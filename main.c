/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:45:07 by davli             #+#    #+#             */
/*   Updated: 2024/07/30 15:21:39 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_kill_mtx(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philos)
		pthread_mutex_destroy(&philo->fork[i++]);
	i = 0;
	while (i < MTX_NUM)
		pthread_mutex_destroy(&philo->data->mutex[i++]);
}

int	ft_monitor(t_philo *philo, t_data *data, int i)
{
	t_msec			l_meal;

	while (1)
	{
		pthread_mutex_lock(&data->mutex[MTX_MEALS]);
		l_meal = philo[i].last_meal;
		pthread_mutex_unlock(&data->mutex[MTX_MEALS]);
		if (l_meal && ft_are_done(philo, data))
		{
			pthread_mutex_lock(&data->mutex[MTX_DONE]);
			data->done = 1;
			pthread_mutex_unlock(&data->mutex[MTX_DONE]);
			break ;
		}
		if (l_meal && ((ft_gettime() - l_meal) > data->t_death))
		{
			ft_died(data);
			ft_log(&philo[i], DIED);
			break ;
		}
		i = ((i + 1) % data->n_philos);
		usleep(200);
	}
	return (1);
}

int	ft_philosophize(t_philo *philo)
{
	int			i;

	philo->data->th = malloc(sizeof(pthread_t) * philo->data->n_philos);
	if (philo->data->th == NULL)
		return (0);
	i = -1;
	while (++i < philo->data->n_philos)
	{
		if (pthread_create(&philo->data->th[i], 0, ft_start_philo, &philo[i]))
		{
			while (i--)
				pthread_join(philo->data->th[i], NULL);
			return (free(philo->data->th), 0);
		}
	}
	if (ft_monitor(philo, philo->data, 0) != 1)
		return (ft_kill_mtx(philo), free(philo->data->th), 0);
	i = -1;
	while (++i < philo->data->n_philos)
		if (pthread_join(philo->data->th[i], NULL))
			return (0);
	return (ft_kill_mtx(philo), free(philo->data->th), 1);
}

void	*ft_start_philo(void *ref)
{
	t_philo	*philo;

	philo = (t_philo *)ref;
	if (philo->id % 2 == 0)
	{
		ft_log(philo, THINK);
		usleep(philo->data->t_meal * 1000);
	}
	while (1)
	{
		if (ft_isdead(philo))
			break ;
		if (ft_eating(philo) != 1)
			break ;
		ft_log(philo, THINK);
		usleep(philo->data->t_think * 1000);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_data	*data;

	data = NULL;
	philos = NULL;
	if (argc != 5 && argc != 6)
		return (printf("Error : Incorrect arguments"));
	if (init(&philos, &data, argc, argv) != 1)
		return (ft_free(philos, data, 0));
	if (ft_philosophize(philos) != 1)
		return (ft_free(philos, data, 0));
	return (ft_free(philos, data, 1));
}
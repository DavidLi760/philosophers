/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:24:45 by davli             #+#    #+#             */
/*   Updated: 2024/07/30 15:29:13 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[MTX_DIED]);
	if (philo->data->died)
	{
		pthread_mutex_unlock(&philo->data->mutex[MTX_DIED]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex[MTX_DIED]);
	return (0);
}

int	ft_isdone(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[MTX_DONE]);
	if (philo->data->done)
	{
		pthread_mutex_unlock(&philo->data->mutex[MTX_DONE]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex[MTX_DONE]);
	return (0);
}

int	ft_are_done(t_philo *philo, t_data *data)
{
	int	i;
	int	done;
	int	meals_count;

	if (data->n_meals == -1)
		return (0);
	i = -1;
	done = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_lock(&philo->data->mutex[MTX_MEALS]);
		meals_count = philo[i].meal_count;
		pthread_mutex_unlock(&philo->data->mutex[MTX_MEALS]);
		if (meals_count >= data->n_meals)
			if (++done == (data->n_philos - 1))
				return (1);
		usleep(50);
	}
	return (0);
}

int	ft_getforks(t_philo *p)
{
	if (p->r_fork > p->l_fork)
		p->max = p->r_fork;
	else
		p->max = p->l_fork;
	if (p->r_fork < p->l_fork)
		p->min = p->r_fork;
	else
		p->min = p->l_fork;
	pthread_mutex_lock(&p->fork[p->min]);
	ft_log(p, FORK);
	if (p->l_fork == p->r_fork)
	{
		pthread_mutex_unlock(&p->fork[p->min]);
		return (0);
	}
	pthread_mutex_lock(&p->fork[p->max]);
	ft_log(p, FORK);
	ft_log(p, EAT);
	return (1);
}

int	ft_dropforks(t_philo *p)
{
	if (p->r_fork > p->l_fork)
		p->max = p->r_fork;
	else
		p->max = p->l_fork;
	if (p->r_fork < p->l_fork)
		p->min = p->r_fork;
	else
		p->min = p->l_fork;
	ft_log(p, SLEEP);
	pthread_mutex_unlock(&p->fork[p->max]);
	pthread_mutex_unlock(&p->fork[p->min]);
	usleep(p->data->t_sleep * 1000);
	return (1);
}
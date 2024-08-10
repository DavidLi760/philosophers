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

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->mutex[MTX_DIED]);
	if (philo->var->died)
	{
		pthread_mutex_unlock(&philo->var->mutex[MTX_DIED]);
		return (1);
	}
	pthread_mutex_unlock(&philo->var->mutex[MTX_DIED]);
	return (0);
}

int	ending(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->mutex[MTX_DONE]);
	if (philo->var->done)
	{
		pthread_mutex_unlock(&philo->var->mutex[MTX_DONE]);
		return (1);
	}
	pthread_mutex_unlock(&philo->var->mutex[MTX_DONE]);
	return (0);
}

int	ft_eat(t_philo *p)
{
	if (take_fork(p) != 1)
		return (0);
	pthread_mutex_lock(&p->var->mutex[MTX_MEALS]);
	p->last_meal = get_time();
	p->meal_count++;
	pthread_mutex_unlock(&p->var->mutex[MTX_MEALS]);
	if (ending(p))
		return (ft_sleep(p), 0);
	usleep(p->var->t2e * 1000);
	ft_sleep(p);
	return (1);
}

int	take_fork(t_philo *p)
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
	print_status(p, FORK);
	if (p->l_fork == p->r_fork)
	{
		pthread_mutex_unlock(&p->fork[p->min]);
		return (0);
	}
	pthread_mutex_lock(&p->fork[p->max]);
	print_status(p, FORK);
	print_status(p, EAT);
	return (1);
}

int	ft_sleep(t_philo *p)
{
	if (p->r_fork > p->l_fork)
		p->max = p->r_fork;
	else
		p->max = p->l_fork;
	if (p->r_fork < p->l_fork)
		p->min = p->r_fork;
	else
		p->min = p->l_fork;
	print_status(p, SLEEP);
	pthread_mutex_unlock(&p->fork[p->max]);
	pthread_mutex_unlock(&p->fork[p->min]);
	usleep(p->var->t2s * 1000);
	return (1);
}

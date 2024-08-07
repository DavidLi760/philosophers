/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:24:56 by davli             #+#    #+#             */
/*   Updated: 2024/07/30 15:29:20 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *p)
{
	long int	time;

	pthread_mutex_lock(p->var->death);
	time = current_time() - p->last_eat;
	if (time >= p->var->t2d)
	{
		pthread_mutex_unlock(p->var->death);
		return (death(p));
	}
	pthread_mutex_unlock(p->var->death);
	return (0);
}

int	check_meals(t_philo p, int last)
{
	if (last == p.var->nb - 1
		&& p.ate == p.var->max)
		return (ft_usleep(300));
	return (0);
}

void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_state(p, FORK);
	pthread_mutex_lock(p->right_fork);
	print_state(p, FORK);
	print_state(p, EAT);
	p->last_eat = current_time();
	ft_usleep(p->var->t2e);
	p->ate++;
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	ft_sleep_think(t_philo *p)
{
	ft_usleep(p->var->t2s);
	print_state(p, SLEEP);
	print_state(p, THINK);
}

void	*routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (!p->var->ready)
		continue ;
	if (p->num & 1)
		ft_usleep(p->var->t2e * 0.9 + 1);
	while (!p->var->end)
	{
		ft_eat(p);
		ft_sleep_think(p);
	}
	return (NULL);
}

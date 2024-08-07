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

static void	check_thread(t_var *var, t_philo *p)
{
	int	i;

	while (!var->ready)
		continue ;
	while (!var->end)
	{
		i = -1;
		while (++i < var->nb)
			if (check_death(&p[i]) || check_meals(p[i], i))
			{
				var->end = 1;
				p->var->ready = 0;
			}
	}
	if (p[var->nb - 1].ate == var->max)
		ft_usleep(5 * var->nb);
}

static void	end_thread(t_var *var, t_philo *p)
{
	int	i;

	i = -1;
	while (++i < var->nb)
		pthread_join(p[i].tid, (void *)&p[i]);
	pthread_mutex_destroy(var->death);
	pthread_mutex_destroy(var->fork);
}

int	init_thread(t_var *var, t_philo *p)
{
	int	i;

	i = -1;
	while (++i < var->nb)
	{
		p[i].num = i + 1;
		p[i].ate = 0;
		p[i].dead = 0;
		p[i].last_eat = 0;
		p[i].start = 0;
		p[i].var = var;
		p[i].left_fork = &var->fork[i];
		p[i].right_fork = 0;
	}
	return (0);
}

int	create_thread(t_var *var, t_philo *p)
{
	int	i;

	i = -1;
	while (++i < var->nb)
	{
		p[i].right_fork = p[(i + 1) % var->nb].left_fork;
		if (pthread_create(&p[i].tid, NULL, &routine, &p[i]) == -1)
			return (1);
	}
	i = -1;
	var->start = current_time();
	while (++i < var->nb)
	{
		p[i].start = var->start;
		p[i].last_eat = var->start;
	}
	var->ready = 1;
	return (0);
}

int	thread(t_var *var)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo) * var->nb);
	if (!p)
		return (1);
	init_thread(var, p);
	if (create_thread(var, p))
	{
		free(p);
		return (1);
	}
	check_thread(var, p);
	end_thread(var, p);
	free(p);
	return (0);
}

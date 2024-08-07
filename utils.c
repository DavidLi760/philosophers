/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:25:01 by davli             #+#    #+#             */
/*   Updated: 2024/07/30 15:29:04 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free(t_var *var, int i)
{
	if (i == -1)
	{
		free(var->death);
		return (1);
	}
	if (i == -2)
	{
		free(var->death);
		free(var->fork);
		return (1);
	}
	free(var->death);
	free(var->fork);
	return (1);
}

void	print_state(t_philo *p, char *action)
{
	pthread_mutex_lock(p->var->death);
	if (p->var->end)
	{
		pthread_mutex_unlock(p->var->death);
		return ;
	}
	printf("%ld %d %s\n", current_time() - p->start,
		p->num, action);
	pthread_mutex_unlock(p->var->death);
}

long int	current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int	ft_usleep(long int time)
{
	long int	start_time;

	start_time = current_time();
	while ((current_time() - start_time) < time)
		usleep(1000);
	return (1);
}

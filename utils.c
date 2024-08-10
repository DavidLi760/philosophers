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

int	ft_free(t_philo *philo, t_var *var, int ret)
{
	if (var && var->mutex)
		free(var->mutex);
	if (var)
		free(var);
	if (philo && philo->fork)
		free(philo->fork);
	if (philo)
		free(philo);
	return (ret);
}

int	finished(t_philo *philo, t_var *var)
{
	int	i;
	int	done;
	int	meals_count;

	if (var->eat_count == -1)
		return (0);
	i = -1;
	done = -1;
	while (++i < var->nb)
	{
		pthread_mutex_lock(&philo->var->mutex[MTX_MEALS]);
		meals_count = philo[i].meal_count;
		pthread_mutex_unlock(&philo->var->mutex[MTX_MEALS]);
		if (meals_count >= var->eat_count)
			if (++done == (var->nb - 1))
				return (1);
		usleep(50);
	}
	return (0);
}

void	death(t_var *var)
{
	pthread_mutex_lock(&var->mutex[MTX_DIED]);
	var->died = 1;
	pthread_mutex_unlock(&var->mutex[MTX_DIED]);
}

t_msec	get_time(void)
{
	t_time	t;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	print_status(t_philo *p, char *str)
{
	t_msec	time;

	time = get_time() - p->var->start;
	pthread_mutex_lock(&p->var->mutex[MTX_PRINTF]);
	if (((!is_dead(p)) && (!ending(p))) || (*str == 'd'))
		printf("%3lld %3d %s\n", time, p->id, str);
	pthread_mutex_unlock(&p->var->mutex[MTX_PRINTF]);
}

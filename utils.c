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

int	ft_free(t_philo *philo, t_data *data, int ret)
{
	if (data && data->mutex)
		free(data->mutex);
	if (data)
		free(data);
	if (philo && philo->fork)
		free(philo->fork);
	if (philo)
		free(philo);
	return (ret);
}

int	ft_eating(t_philo *p)
{
	if (ft_getforks(p) != 1)
		return (0);
	pthread_mutex_lock(&p->data->mutex[MTX_MEALS]);
	p->last_meal = ft_gettime();
	p->meal_count++;
	pthread_mutex_unlock(&p->data->mutex[MTX_MEALS]);
	if (ft_isdone(p))
		return (ft_dropforks(p), 0);
	usleep(p->data->t_meal * 1000);
	ft_dropforks(p);
	return (1);
}

void	ft_died(t_data *data)
{
	pthread_mutex_lock(&data->mutex[MTX_DIED]);
	data->died = 1;
	pthread_mutex_unlock(&data->mutex[MTX_DIED]);
}

t_msec	ft_gettime(void)
{
	t_time	t;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_log(t_philo *p, char *str)
{
	t_msec	time;

	time = ft_gettime() - p->data->t_start;
	pthread_mutex_lock(&p->data->mutex[MTX_PRINTF]);
	if (((!ft_isdead(p)) && (!ft_isdone(p))) || (*str == 'd'))
		printf("%3lld %3d %s\n", time, p->id, str);
	pthread_mutex_unlock(&p->data->mutex[MTX_PRINTF]);
}
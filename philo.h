/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:45:14 by davli             #+#    #+#             */
/*   Updated: 2024/07/30 15:34:12 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"


typedef enum e_mutex
{
	MTX_PRINTF,
	MTX_MEALS,
	MTX_DONE,
	MTX_DIED,
	MTX_NUM
}	t_mutexes;

typedef long long		t_msec;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;

typedef struct s_data
{
	int			n_philos;
	t_msec		t_death;
	t_msec		t_meal;
	t_msec		t_sleep;
	t_msec		t_think;
	int			n_meals;
	t_msec		t_start;
	int			done;
	int			died;
	t_mutex		*mutex;
	pthread_t	*th;
}			t_data;

typedef struct s_philo
{
	int			id;
	t_msec		last_meal;
	int			meal_count;
	int			max;
	int			min;
	int			l_fork;
	int			r_fork;
	t_mutex		*fork;
	t_data		*data;
}			t_philo;


void	*ft_start_philo(void *args);
int		ft_free(t_philo *philo, t_data *data, int ret);
int		ft_isdead(t_philo *philo);
void	ft_died(t_data *data);
int		ft_isdone(t_philo *philo);
int		ft_are_done(t_philo *philo, t_data *data);
void	ft_done(t_data *data);
int		ft_eating(t_philo *philo);
void	ft_kill_mtx(t_philo *philo);
int		init(t_philo **philo, t_data **data, int argc, char **argv);
long	ft_atol(char *str);
int		ft_check_data(t_data **data);
t_msec	ft_gettime(void);
void	ft_log(t_philo *philo, char *str);
int		ft_eating(t_philo *p);
int		ft_getforks(t_philo *p);
int		ft_dropforks(t_philo *p);

#endif

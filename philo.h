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

typedef struct s_var
{
	int			nb;
	t_msec		t2d;
	t_msec		t2e;
	t_msec		t2s;
	int			eat_count;
	t_msec		start;
	int			done;
	int			died;
	t_mutex		*mutex;
	pthread_t	*thread;
}			t_var;

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
	t_var		*var;
}			t_philo;


void	*routine(void *args);
int		ft_free(t_philo *philo, t_var *var, int ret);
int		is_dead(t_philo *philo);
void	death(t_var *var);
int		ending(t_philo *philo);
int		finished(t_philo *philo, t_var *var);
void	ft_done(t_var *var);
void	mutex_destroyer(t_philo *philo);
int		init(t_philo **philo, t_var **var, int argc, char **argv);
long	ft_atol(char *str);
t_msec	get_time(void);
void	print_status(t_philo *philo, char *str);
int		ft_eat(t_philo *p);
int		take_fork(t_philo *p);
int		ft_sleep(t_philo *p);

#endif

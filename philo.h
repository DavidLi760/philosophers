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

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef struct s_var
{
	int				nb;
	int				t2d;
	int				t2e;
	int				t2s;
	int				max;
	int				end;
	int				ready;
	long int		start;
	pthread_mutex_t	*death;
	pthread_mutex_t	*fork;
}	t_var;

typedef struct s_philo
{
	int				num;
	int				ate;
	int				dead;
	long int		last_eat;
	long int		start;
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_var			*var;
}	t_philo;

void		*routine(void *philo);
int			ft_free(t_var *var, int i);
void		print_state(t_philo *p, char *action);
long int	current_time(void);
int			ft_usleep(long int time);
int			thread(t_var *var);
int			check_death(t_philo *p);
int			check_meals(t_philo p, int last);
int			death(t_philo *p);

#endif

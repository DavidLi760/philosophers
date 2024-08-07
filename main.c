/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:45:07 by davli             #+#    #+#             */
/*   Updated: 2024/07/30 15:21:39 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr *= 10;
		nbr = nbr + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

int	init_mutex(t_var *var)
{
	int	i;

	i = -1;
	var->death = 0;
	var->fork = 0;
	var->death = malloc(sizeof(pthread_mutex_t));
	if (!var->death)
		return (1);
	var->fork = malloc(sizeof(pthread_mutex_t) * var->nb);
	if (!var->fork)
		return (ft_free(var, -1));
	if (pthread_mutex_init(var->death, NULL) == -1)
		return (ft_free(var, -2));
	while (++i < var->nb)
		if (pthread_mutex_init(&var->fork[i], NULL) == -1)
			return (ft_free(var, 0));
	return (0);
}

int	init(t_var *var, int argc, char **argv)
{
	var->nb = ft_atoi(argv[1]);
	var->t2d = ft_atoi(argv[2]);
	var->t2e = ft_atoi(argv[3]);
	var->t2s = ft_atoi(argv[4]);
	var->max = 100;
	if (argc == 6)
		var->max = ft_atoi(argv[5]);
	var->end = 0;
	if (init_mutex(var))
		return (1);
	return (0);
}

int	death(t_philo *p)
{
	print_state(p, DIED);
	p->var->end = 1;
	p->dead = 1;
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (1);
}

int	main(int argc, char **argv)
{
	t_var	var;

	if (argc != 5 && argc != 6)
		return (printf("Error : Incorrect number of arguments"));
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1
		|| ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
		return (printf("Error : Invalid arguments"));
	if (argv[5])
		if (ft_atoi(argv[5]) < 1)
			return (printf("Error : Invalid arguments"));
	if (init(&var, argc, argv))
		return (printf("Error : Invalid arguments"));
	if (thread(&var))
		return (ft_free(&var, -2));
	ft_free(&var, -2);
	return (0);
}

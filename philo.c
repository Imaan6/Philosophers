/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:26:44 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/21 16:02:59 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_print(int v, t_vars *var, char *text)
{
	pthread_mutex_lock(&var->is_ded);
	if (var->is_philo_dead != 1)
	{
		pthread_mutex_lock(&var->print);
		printf("%lld %d %s \n", gettimenow() - var->tstart, v + 1, text);
		pthread_mutex_unlock(&var->print);
	}
	pthread_mutex_unlock(&var->is_ded);
	
}

void	init_mutex(t_vars *var)
{
	var->i = 0;
	var->forks = malloc(sizeof(pthread_mutex_t) * var->tab[0]);
	while (var->i < var->tab[0])
	{
		pthread_mutex_init(&var->forks[var->i], NULL);
		var->i++;
	}
	pthread_mutex_init(&var->death, NULL);
	pthread_mutex_init(&var->print, NULL);
	pthread_mutex_init(&var->is_ded, NULL);
}

void	init_mystruct(t_vars *var, char **av, int ac)
{
	var->i = 0;
	while (var->i < ac - 1)
	{
		var->tab[var->i] = ft_atoi(av[var->i + 1]);
		var->i++;
	}
	var->is_philo_dead = 0;
}

int	main(int ac, char **av)
{
	t_vars	*var;

	if ((ac == 5 || ac == 6) && is_digit(av) == 1)
	{
		var = malloc(sizeof(t_vars) * 1);
		var->tab = malloc((ac) * sizeof(int));
		init_mystruct(var, av, ac);
		if (var->tab[0] < 1)
			return (0);
		var->forks = malloc(var->tab[0] * sizeof(int));
		init_mutex(var);
		create_philo(var);
		destroy_mutex(var);
	}
}

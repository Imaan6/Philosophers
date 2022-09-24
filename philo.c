/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:26:44 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/24 14:01:00 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_handling(int i, char *s)
{
	if (i != 0)
	{
		printf("%s failed \n", s);
		return ;
	}
}

void	mutex_print(int v, t_vars *var, char *text)
{
	error_handling(pthread_mutex_lock(&var->is_ded), "mutex");
	if (var->is_philo_dead != 1)
	{
		error_handling(pthread_mutex_lock(&var->print), "mutex");
		printf("%lld %d %s \n", gettimenow() - var->tstart, v + 1, text);
		error_handling(pthread_mutex_unlock(&var->print), "mutex");
	}
	error_handling(pthread_mutex_unlock(&var->is_ded), "Mutex");
}

void	init_mutex(t_vars *var)
{
	var->i = 0;
	var->forks = malloc(sizeof(pthread_mutex_t) * var->tab[0]);
	if (var->forks == NULL)
	{
		printf("Malloc error \n");
		return ;
	}
	while (var->i < var->tab[0])
	{
		error_handling(pthread_mutex_init
			(&var->forks[var->i], NULL), "Mutex init");
		var->i++;
	}
	error_handling(pthread_mutex_init(&var->print, NULL), "Mutex init");
	error_handling(pthread_mutex_init(&var->is_ded, NULL), "Mutex init");
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
	var->i = 0;
	var->tstart = gettimenow();
	var->im = 2147483647;
	var->forks = malloc(var->tab[0] * sizeof(int));
	if (var->forks == NULL)
		error_malloc();
}

int	main(int ac, char **av)
{
	t_vars	*var;

	if ((ac == 5 || ac == 6) && is_digit(av) == 1)
	{
		var = malloc(sizeof(t_vars) * 1);
		var->tab = malloc((ac) * sizeof(int));
		if (var == NULL || var->tab == NULL)
			error_malloc();
		init_mystruct(var, av, ac);
		if (ac == 6 && var->tab[4] < 1)
		{
			printf("Arguments are not valid. Try Again. 1 \n");
			return (0);
		}
		if (var->tab[0] < 1 || var->tab[1] > var->im || var->tab[2] > var->im
			|| var->tab[3] > var->im || var->tab[4] > var->im)
		{
			printf("Arguments are not valid. Try Again. 2\n");
			return (0);
		}
		init_mutex(var);
		create_philo(var);
	}
	else
		printf("Arguments are not valid. Try Again. 3 \n");
}

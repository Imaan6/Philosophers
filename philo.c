/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:26:44 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/22 18:49:16 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_handling(char *s, int i)
{
	if(pthread_mutex_init(&var->forks[var->i], NULL) != 0)
	{
		printf("Mutex init failed \n");
		return ;
	}
}

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
	var->i = 0;
	var->tstart = gettimenow();
}

void	let_there_be_light(t_vars *var, t_philo *philos, int i)
{
	while (i < var->tab[0])
	{	
		pthread_create(&philos->thread[i], NULL,
			(void *)thread_body, &philos[i]);
		pthread_detach(philos->thread[i]);
		i += 2;
	}	
}

int	main(int ac, char **av)
{
	t_vars	*var;

	if ((ac == 5 || ac == 6) && is_digit(av) == 1)
	{
		var = malloc(sizeof(t_vars) * 1);
		var->tab = malloc((ac) * sizeof(int));
		init_mystruct(var, av, ac);
		if (var->tab[0] < 1 || var->tab[4] == 0)
		{
			printf("Arguments are not valid. Try Again. \n");
			return (0);
		}
		var->forks = malloc(var->tab[0] * sizeof(int));
		init_mutex(var);
		create_philo(var);
	}
	else
		printf("Arguments are not valid. Try Again. \n");
}

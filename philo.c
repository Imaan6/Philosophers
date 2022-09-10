/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:26:44 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/10 22:26:30 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_body(t_vars *var)
{	
	int v;
	v = var->i;
	while(1)
	{
		pthread_mutex_lock(&var->forks[v]);
		var->tnow = gettime(*var) - var->tstart;
		printf("%ld ms %d has taken a fork \n" , var->tnow,v);
		pthread_mutex_lock(&var->forks[(v + 1)  % var->tab[0]]);
		var->tnow = gettime(*var) - var->tstart;
		printf("%ld ms %d has taken a fork \n" , var->tnow, v);
		printf("%ld ms %d is eating \n" , var->tnow, v);
		usleep(1000 * var->tab[2]);
		pthread_mutex_unlock(&var->forks[v]);
		pthread_mutex_unlock(&var->forks[(v + 1) % var->tab[0]]);
		var->tnow = gettime(*var) - var->tstart;
		printf("%ld ms %d is sleeping \n" , var->tnow, v);
		usleep(var->tab[3] * 1000);
	}
	return NULL;
}

long	gettime(t_vars var)
{
	gettimeofday(&var.time, NULL);
	return(var.time.tv_sec * 1000);
}

void	create_philo(t_vars var, pthread_t *thread)
{
		var.i = 0;
		while(var.i < var.tab[0])
		{	
			var.tstart = gettime(var);
			var.result = pthread_create(&thread[var.i], NULL, (void *)thread_body, &var);
			usleep(100);
			var.i++;
			if(var.result != 0)
			{
				printf("pthread_create failed.");
				return ;
			}
		}
		var.i = 0;
		while(var.i < var.tab[0])
		{
			var.result = pthread_join(thread[var.i++], NULL);
			if(var.result != 0)
			{
				printf("pthread_join failed.");
				return ;
			}
		}	
}

void	init_mystruct(t_vars var, char **av, int ac)
{
	var.i = 0;
	while (var.i < ac-1)
	{
		var.tab[var.i] = ft_atoi(av[var.i + 1]);
		var.i++;
	}
}

void	init_mutex(t_vars var)
{
	var.i = 0;
	while(var.i < var.tab[0])
	{
		var.result = pthread_mutex_init(&var.forks[var.i], NULL);
		var.i++;
		if (var.result != 0)
		{
			printf("pthread_mutex_init failed.");
			return ;
		}
	}	
}

void	destroy_mutex(t_vars var)
{
	var.i = 0;
	while(var.i < var.tab[0])
	{
		var.result = pthread_mutex_destroy(&var.forks[var.i]);
		var.i++;
		if (var.result != 0)
		{
			printf("pthread_mutex_destroy failed.");
			return ;
		}
	}	
}

int	main(int ac, char **av)
{
    if ((ac == 5 || ac == 6) && is_digit(av) == 1)
    {
		t_vars	var;
		
		var.tab = malloc((ac) * sizeof(int));
		init_mystruct(var, av, ac);
		if (var.tab[0] < 1)
			return (0);
		pthread_t thread[var.tab[0]];
		var.forks = malloc(var.tab[0] * sizeof(int));
		init_mutex(var);
		create_philo(var, thread);
		destroy_mutex(var);
	}
}
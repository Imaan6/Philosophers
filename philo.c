/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:26:44 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/19 20:18:14 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long gettimenow()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	
}

void myusleep(long long time_to_waste)
{	
	long long time_finish = gettimenow() + time_to_waste;
	while(gettimenow() < time_finish)
	{
		usleep(10);
	}
}

void	mutex_print(int v, t_vars *var, char *text)
{
	pthread_mutex_lock(&var->print);
	if(var->is_philo_dead != 1)
		printf("%ld %d %s \n", gettimenow() - var->tstart, v + 1, text);
	pthread_mutex_unlock(&var->print);
}

void	*thread_body(t_philo *philo)
{	
	int	v;
	
	philo->time_to_die = philo->vars->tab[1] + gettimenow();
	pthread_mutex_lock(&philo->vars->death);
	philo->time_to_die = philo->vars->tab[1] + gettimenow();
	pthread_mutex_unlock(&philo->vars->death);
	v = philo->i;
	while (1)
	{
		if(philo->vars->tab[4] && philo->eat_count == 0)
			continue;
		pthread_mutex_lock(&philo->vars->forks[v % philo->vars->tab[0]]);
		mutex_print(v, philo->vars, "has taken a fork");
		pthread_mutex_lock(&philo->vars->forks[(v + 1)  % philo->vars->tab[0]]);
		mutex_print(v, philo->vars, "has taken a fork");
		mutex_print(v, philo->vars, "is eating");
		pthread_mutex_lock(&philo->vars->death);
		philo->time_to_die = gettimenow() + philo->vars->tab[1];
		if(philo->vars->tab[4])
		{
			philo->eat_count--;
			printf("eat count : %d \n", philo->eat_count);
		}
		pthread_mutex_unlock(&philo->vars->death);
		myusleep(philo->vars->tab[2]);
		pthread_mutex_unlock(&philo->vars->forks[v % philo->vars->tab[0]]);
		pthread_mutex_unlock(&philo->vars->forks[(v + 1) % philo->vars->tab[0]]);
		mutex_print(v, philo->vars, "is sleeping");
		myusleep(philo->vars->tab[3]);
		mutex_print(v, philo->vars, "is thinking");
	}
	return NULL;
}

void	super_visor(t_philo *philos, t_vars *var)
{
	int i = 0;
	int meal_count = 0;
	while(i < var->tab[0])
	{
		pthread_mutex_lock(&philos[i].vars->death);
		if(var->tab[4])
		{
			if(philos[i].eat_count == 0 && meal_count == var->tab[0])
			{
				break;
				//printf(" first meal count: %d \n", meal_count);	
			}
			else if ((philos[i].finished == 0)&& philos[i].eat_count == 0 && meal_count != var->tab[0])
			{
				philos[i].finished = 1;
				meal_count++;
			}
				
			//printf(" second meal count: %d and eat count : %d \n", meal_count, philos->eat_count);	
		}
		if (philos[i].time_to_die < gettimenow())
		{
			var->is_philo_dead = 1;
			pthread_mutex_lock(&philos->vars->print);
			printf("%ld %d died \n", gettimenow() - var->tstart, i + 1);
			break;
		}
		pthread_mutex_unlock(&philos[i].vars->death);
		i++;
		if (i == var->tab[0])
			i = 0;
	}
}

void	create_philo(t_vars *var, pthread_t *thread)
{
		t_philo *philos;
		var->i = 0;
		var->tstart = gettimenow();
		philos = malloc(sizeof(t_philo) * var->tab[0]); 
		while(var->i < var->tab[0])
		{	
			philos[var->i].finished = 0;
			philos[var->i].i = var->i;
			philos[var->i].vars = var;
			if(var->tab[4])
				philos[var->i].eat_count = var->tab[4];
			pthread_create(&thread[var->i], NULL, (void *)thread_body, &philos[var->i]);
			usleep(50);
			var->i++;
		}
		var->i = 0;
		super_visor(philos, var);
		while(var->i < var->tab[0])
		{
			pthread_detach(thread[var->i]);
			var->i++;
		}
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
    if ((ac == 5 || ac == 6) && is_digit(av) == 1)
    {
		t_vars	*var;
		var = malloc(sizeof(t_vars) * 1);
		var->tab = malloc((ac) * sizeof(int));
		init_mystruct(var, av, ac);
		if (var->tab[0] < 1)
			return (0);
		pthread_t thread[var->tab[0]];
		var->forks = malloc(var->tab[0] * sizeof(int));
		init_mutex(var);
		create_philo(var, thread);
	}
}
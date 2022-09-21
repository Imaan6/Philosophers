/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_of_a_life.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:04:57 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/21 13:22:19 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_body(t_philo *philo)
{	
	int	v;

	pthread_mutex_lock(&philo->vars->death);
	philo->time_to_die = philo->vars->tab[1] + gettimenow();
	pthread_mutex_unlock(&philo->vars->death);
	v = philo->i;
	while (1)
		body_continued(philo, v);
	return (NULL);
}

void	body_continued(t_philo *philo, int v)
{
	pthread_mutex_lock(&philo->vars->forks[v % philo->vars->tab[0]]);
	mutex_print(v, philo->vars, "has taken a fork");
	pthread_mutex_lock(&philo->vars->forks[(v + 1) % philo->vars->tab[0]]);
	mutex_print(v, philo->vars, "has taken a fork");
	mutex_print(v, philo->vars, "is eating");
	pthread_mutex_lock(&philo->vars->death);
	philo->time_to_die = gettimenow() + philo->vars->tab[1];
	if (philo->vars->tab[4])
		philo->eat_count--;
	pthread_mutex_unlock(&philo->vars->death);
	myusleep(philo->vars->tab[2]);
	pthread_mutex_unlock(&philo->vars->forks[v % philo->vars->tab[0]]);
	pthread_mutex_unlock(&philo->vars->forks[(v + 1) % philo->vars->tab[0]]);
	mutex_print(v, philo->vars, "is sleeping");
	myusleep(philo->vars->tab[3]);
	mutex_print(v, philo->vars, "is thinking");
}

void	super_visor(t_philo *philos, t_vars *var, int i, int meal_count)
{
	while (i < var->tab[0])
	{
		pthread_mutex_lock(&philos[i].vars->death);
		if (var->tab[4])
		{
			if (philos[i].eat_count == 0 && meal_count == var->tab[0])
				break ;
			else if ((philos[i].finished == 0)
				&& philos[i].eat_count == 0 && meal_count != var->tab[0])
			{
				philos[i].finished = 1;
				meal_count++;
			}
		}
		if (philos[i].time_to_die < gettimenow())
		{
			grim_reaper(philos, var, i);
			break ;
		}
		pthread_mutex_unlock(&philos[i].vars->death);
		i++;
		if (i == var->tab[0])
			i = 0;
	}
}

void	grim_reaper(t_philo *philos, t_vars *var, int i)
{
	pthread_mutex_lock(&philos->vars->is_ded);
	var->is_philo_dead = 1;
	pthread_mutex_unlock(&philos->vars->is_ded);
	pthread_mutex_lock(&philos->vars->print);
	printf("%ld %d died \n", gettimenow() - var->tstart, i + 1);
}

void	create_philo(t_vars *var)
{
	int			i;
	int			meal_count;
	t_philo		*philos;

	i = 0;
	meal_count = 0;
	var->i = 0;
	var->tstart = gettimenow();
	philos = malloc(sizeof(t_philo) * var->tab[0]);
	philos->thread = malloc(sizeof(pthread_t) * var->tab[0]);
	while (var->i < var->tab[0])
	{	
		philos[var->i].finished = 0;
		philos[var->i].i = var->i;
		philos[var->i].vars = var;
		if (var->tab[4])
			philos[var->i].eat_count = var->tab[4];
		pthread_create(&philos->thread[var->i], NULL,
			(void *)thread_body, &philos[var->i]);
		usleep(50);
		var->i++;
	}
	var->i = 0;
	super_visor(philos, var, i, meal_count);
}

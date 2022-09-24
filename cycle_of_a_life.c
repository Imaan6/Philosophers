/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_of_a_life.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:04:57 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/24 14:22:39 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_body(t_philo *philo)
{	
	int	v;

	error_handling(pthread_mutex_lock(&philo->death), "mutex");
	philo->time_to_die = philo->vars->tab[1] + gettimenow();
	error_handling(pthread_mutex_unlock(&philo->death), "mutex");
	v = philo->i;
	while (1)
		body_continued(philo, v);
	return (NULL);
}

void	body_continued(t_philo *philo, int v)
{
	error_handling(pthread_mutex_lock(&philo->vars->forks
		[v % philo->vars->tab[0]]), "Mutex");
	mutex_print(v, philo->vars, "has taken a fork");
	error_handling(pthread_mutex_lock(&philo->vars->forks
		[(v + 1) % philo->vars->tab[0]]), "Mutex");
	mutex_print(v, philo->vars, "has taken a fork");
	mutex_print(v, philo->vars, "is eating");
	error_handling(pthread_mutex_lock(&philo->death), "Mutex");
	philo->time_to_die = gettimenow() + philo->vars->tab[1];
	if (philo->vars->tab[4])
		philo->eat_count--;
	error_handling(pthread_mutex_unlock(&philo->death), "Mutex");
	myusleep(philo->vars->tab[2]);
	error_handling(pthread_mutex_unlock(&philo->vars->forks
		[(v + 1) % philo->vars->tab[0]]), "Mutex");
	error_handling(pthread_mutex_unlock(&philo->vars->forks
		[v % philo->vars->tab[0]]), "Mutex");
	mutex_print(v, philo->vars, "is sleeping");
	myusleep(philo->vars->tab[3]);
	mutex_print(v, philo->vars, "is thinking");
}

void	super_visor(t_philo *philos, t_vars *var, int i, int meal_count)
{
	while (i < var->tab[0])
	{
		error_handling(pthread_mutex_lock(&philos[i].death), "mutex");
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
		error_handling(pthread_mutex_unlock(&philos[i].death), "Mutex");
		i++;
		if (i == var->tab[0])
			i = 0;
		error_handling(usleep(50), "usleep");
	}
}

void	grim_reaper(t_philo *philos, t_vars *var, int i)
{
	error_handling(pthread_mutex_lock(&philos->vars->is_ded), "mutex");
	var->is_philo_dead = 1;
	error_handling(pthread_mutex_unlock(&philos->vars->is_ded), "mutex");
	error_handling(pthread_mutex_lock(&philos->vars->print), "mutex");
	printf("%lld %d died \n", gettimenow() - var->tstart, i + 1);
}

void	create_philo(t_vars *var)
{
	int			meal_count;
	t_philo		*philos;

	meal_count = 0;
	var->i = 0;
	var->tstart = gettimenow();
	philos = malloc(sizeof(t_philo) * var->tab[0]);
	philos->thread = malloc(sizeof(pthread_t) * var->tab[0]);
	if (philos == NULL || philos->thread == NULL)
		error_malloc();
	while (var->i < var->tab[0])
	{	
		error_handling(pthread_mutex_init(&philos[var->i].death,
				NULL), "mutex");
		philos[var->i].finished = 0;
		philos[var->i].i = var->i;
		philos[var->i].vars = var;
		if (var->tab[4])
			philos[var->i].eat_count = var->tab[4];
		var->i++;
	}
	creation(philos, var, meal_count);
}

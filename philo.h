/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:26:56 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/21 13:54:47 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct vars
{
	int				j;
	int				i;
	int				*tab;
	pthread_mutex_t	*forks;
	long int		tstart;
	int				is_philo_dead;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	is_ded;
}	t_vars;

typedef struct philo
{
	int			finished;
	int			i;
	long long	time_to_die;
	int			eat_count;
	t_vars		*vars;
	pthread_t	*thread;
}	t_philo;

int		ft_atoi(const char *str);
int		is_digit(char **av);
void	init_mutex(t_vars *var);
void	init_mystruct(t_vars *var, char **av, int ac);
void	create_philo(t_vars *var);
void	*thread_body(t_philo *var);
void	destroy_mutex(t_vars *var);
void	mutex_print(int v, t_vars *var, char *text);
void	body_continued(t_philo *philo, int v);
long	gettimenow(void);
void	myusleep(long long time_to_waste);
void	super_visor(t_philo *philos, t_vars *var, int i, int meal_count);
void	grim_reaper(t_philo *philos, t_vars *var, int i);

#endif
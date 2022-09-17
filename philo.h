/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:26:56 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/17 16:10:18 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_C
# define PHILO_C

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct vars
{
    int 			j;
    int 			i;
    int 			*tab;
    pthread_mutex_t *forks;
    long int    	tstart;
    int				is_philo_dead;
	pthread_mutex_t	death;
    pthread_mutex_t print;
}   t_vars;

typedef struct philo
{
	int	i;
	long long time_to_die;
	int	eat_count;
	t_vars *vars;
}   t_philo
;

int     ft_atoi(const char *str);
int     is_digit(char **av);
void    init_mutex(t_vars *var);
void    init_mystruct(t_vars *var, char **av, int ac);
void	create_philo(t_vars *var, pthread_t *thread);
void	*thread_body(t_philo *var);
void	destroy_mutex(t_vars *var);
void	mutex_print(int v, t_vars *var, char *text);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:26:56 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/10 22:25:16 by iel-moha         ###   ########.fr       */
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
    int j;
    int i;
    int *tab;
    pthread_mutex_t *forks;
    int result;
    long int    tstart;
    long int    tnow;
    struct timeval time;
}   t_vars;

int     ft_atoi(const char *str);
int     is_digit(char **av);
void    init_mutex(t_vars var);
void    init_mystruct(t_vars var, char **av, int ac);
void    create_philo(t_vars var, pthread_t *thread);
void*	thread_body(t_vars *var);
long	gettime(t_vars var);
void	destroy_mutex(t_vars var);

#endif
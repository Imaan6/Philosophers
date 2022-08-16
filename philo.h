/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:26:56 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/16 04:18:55 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_C
# define PHILO_C

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct vars
{
    int philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int i;
    int *tab;
}   t_vars;

int ft_atoi(const char *str);

#endif
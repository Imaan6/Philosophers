/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beelzebub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:01:04 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/24 14:21:56 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	let_there_be_light(t_vars *var, t_philo *philos, int i)
{
	while (i < var->tab[0])
	{	
		error_handling(pthread_create(&philos->thread[i], NULL,
				(void *)thread_body, &philos[i]), "pthread_create \n");
		error_handling(pthread_detach(philos->thread[i]), "Pthread_detach");
		i += 2;
	}	
}

int	error_malloc(void)
{
	printf("Malloc error \n");
	return (0);
}

void	creation(t_philo *philos, t_vars *var, int meal_count)
{
	let_there_be_light(var, philos, 0);
	error_handling(usleep(var->tab[0] * 25), "usleep");
	let_there_be_light(var, philos, 1);
	var->i = 0;
	super_visor(philos, var, var->i, meal_count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beelzebub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:01:04 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/24 17:38:05 by iel-moha         ###   ########.fr       */
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

int	args_atoi(t_vars *var, char **av, int ac)
{
	int	r;

	r = 1;
	var->result = 0;
	var->i = 0;
	while (var->i < ac - 1)
	{
		var->tab[var->i] = ft_atoi(av[var->i + 1]);
		if (ft_atoi(av[var->i + 1]) == 0)
		{
			r = 0;
			break ;
		}
		var->i++;
	}
	return (r);
}

int	atoi_error(unsigned long r, int o)
{
	if (r > 2147483647)
		return (0);
	if (r >= 9223372036854775807 && o == -1)
		return (0);
	else if (r >= 9223372036854775807 && o == 1)
		return (-1);
	return (o * r);
}

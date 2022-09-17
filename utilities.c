/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 01:31:38 by iel-moha          #+#    #+#             */
/*   Updated: 2022/09/17 15:33:18 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned long	r;
	int				i;
	int				o;

	i = 0;
	r = 0;
	o = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			o = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	if (r >= 9223372036854775807 && o == -1)
		return (0);
	else if (r >= 9223372036854775807 && o == 1)
		return (-1);
	return (o * r);
}

int	is_digit(char **av)
{
	int	i[2];

	i[0] = 0;
	while (av[++i[0]])
	{
		if (av[i[0]][0] == '\0')
			return (0);
		i[1] = 0;
		while (av[i[0]][i[1]] == ' ')
				i[1]++;
		while (av[i[0]][i[1]])
		{
			if (av[i[0]][i[1]] == '-' || av[i[0]][i[1]] == '+')
			{	
				i[1]++;
				if (av[i[0]][i[1]] == '-' || av[i[0]][i[1]] == '+')
					return (0);
			}
			else if ((av[i[0]][i[1]] > 47 && av[i[0]][i[1]] < 58))
				i[1]++;
			else
				return (0);
		}
	}
	return (1);
}

void	init_mutex(t_vars *var)
{
	var->i = 0;
	var->forks = malloc(sizeof(pthread_mutex_t) * var->tab[0]);
	while(var->i < var->tab[0])
	{
	pthread_mutex_init(&var->forks[var->i], NULL);
		var->i++;
	}
	pthread_mutex_init(&var->death, NULL);

	pthread_mutex_init(&var->print, NULL);

}

void	destroy_mutex(t_vars *var)
{
	var->i = 0;
	while(var->i < var->tab[0])
	{
		pthread_mutex_destroy(&var->forks[var->i]);
		var->i++;
	}	
}
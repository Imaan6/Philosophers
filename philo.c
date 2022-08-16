/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:26:44 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/16 05:14:01 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    if (ac == 5 || ac == 6)
    {
        t_vars  var;

        var.tab = malloc((ac) * sizeof(int));
        var.i = 0;
        while (var.i < ac-1)
		{
			var.tab[var.i] = ft_atoi(av[var.i + 1]);
			var.i++;
		}

		if (var.tab[0] < 1)
			return 0;
		printf("%d \n IT WORKS", var.tab[0]);
	}
}
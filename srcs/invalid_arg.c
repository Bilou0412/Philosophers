/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:56:37 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/27 11:56:40 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*This function return 1 if the argument are invalid
Valid argument are number only.*/
bool	invalid_arg(char **arg)
{
	int	array;
	int	character;
	int	is_not_number;

	array = 1;
	character = 0;
	is_not_number = 0;
	while (arg[array])
	{
		while (arg[array][character])
		{
			if (!ft_isdigit(arg[array][character]))
				return (1);
			character++;
		}
		if ((ft_atoi(arg[array]) == 0 && array < 5)
			|| (ft_atoi(arg[array]) > 200 && array == 1)
			|| ft_atoi(arg[array]) <= 0)
			return (1);
		character = 0;
		array++;
	}
	return (0);
}

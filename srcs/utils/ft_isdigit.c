/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:36:59 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/16 19:19:33 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
/*Checks for a digit (0 through 9).*/
bool	ft_isdigit(int c)
{
	if (c < 58 && c > 47)
	{
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:02:39 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/27 11:05:47 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Convert a string to an integer.  */
int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	unsigned long long	base;

	base = 0;
	signe = 1;
	i = 0;
	while ((str[i] < 14 && str[i] > 8) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		base = (base * 10) + str[i] - '0';
		i++;
	}
	return (base * signe);
}


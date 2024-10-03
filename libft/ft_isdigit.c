/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:27:34 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/08 14:28:33 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

// c is numerical character
int	ft_isdigit(unsigned char c)
{
	return (c >= '0' && c <= '9');
}

// str contains only numerical characters
int	ft_isdigit_str(char *str)
{
	if (*str == '-')
		str++;
	while (*str != 0)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_isdouble_str(char *str)
{
	char	**split;
	char	*temp;
	int		i;

	i = 0;
	temp = str;
	while (*temp)
	{
		i += (*temp == '.');
		temp++;
	}
	if (i > 1)
		return (0);
	if (i == 0)
		return (ft_isdigit_str(str));
	i = 1;
	split = ft_split(str, '.');
	if (!split)
		return (0);
	if (split[0][0] != 0 && !ft_isdigit_str(split[0]))
		i = 0;
	if (!ft_isdigit_str(split[1]))
		i = 0;
	ft_free_arr(split);
	return (i);
}

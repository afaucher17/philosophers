/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 11:07:40 by afaucher          #+#    #+#             */
/*   Updated: 2014/05/09 18:03:59 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*save;

	save = b;
	while (len > 0)
	{
		*save = (unsigned char)c;
		save++;
		len--;
	}
	return (b);
}

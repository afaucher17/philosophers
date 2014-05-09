/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 18:33:28 by afaucher          #+#    #+#             */
/*   Updated: 2014/02/09 18:33:31 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"libft.h"

int					ft_clear_tab(char **tab)
{
	int				i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	return (1);
}
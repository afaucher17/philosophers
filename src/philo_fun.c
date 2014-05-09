/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <afaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/07 18:04:18 by afaucher          #+#    #+#             */
/*   Updated: 2014/05/09 14:50:44 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"
#include	<stdlib.h>

t_philo		*ft_create_philo(int id, char *name, t_stick *left, t_stick *right)
{
	t_philo	*new;

	if ((new = (t_philo *)malloc(sizeof(t_philo))) == NULL)
		exit(EXIT_FAILURE);
	new->id = id;
	new->name = name;
	new->state = DEFAULT;
	new->pv = MAX_LIFE;
	new->right = right;
	new->left = left;
	if (pthread_create(&new->thread, NULL, ft_philolunch, new))
		exit(EXIT_FAILURE);
	pthread_detach(new->thread);
	return (new);
}

t_stick		*ft_create_stick(void)
{
	t_stick	*new;

	if ((new = (t_stick*)malloc(sizeof(t_stick))) == NULL)
		exit(EXIT_FAILURE);
	new->owner = 0;
	pthread_mutex_init(&new->mutex_stick, NULL);
	return (new);
}

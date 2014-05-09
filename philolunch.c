/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolunch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <afaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/08 19:12:00 by afaucher          #+#    #+#             */
/*   Updated: 2014/05/09 14:01:57 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

extern int g_stop;

static void			ft_philodefault(int *left, int *right, t_philo *philo)
{
	if (!pthread_mutex_trylock(&philo->left->mutex_stick))
	{
		printf("%s stole the stick at his left !\n", philo->name);
		*left = 1;
	}
	else
		*left = 0;
	if (!pthread_mutex_trylock(&philo->right->mutex_stick))
	{
		printf("%s stole the stick at his right !\n", philo->name);
		*right = 1;
	}
	else
		*right = 0;
	if (*left + *right == 2)
		philo->state = EAT;
	else if (*left + *right == 1)
		philo->state = THINK;
	else
		philo->state = DEFAULT;
}

static void			ft_philothink(int *left, int *right, t_philo *philo)
{
	if (*left)
	{
		pthread_mutex_unlock(&philo->left->mutex_stick);
		*left = 0;
	}
	if (*right)
	{
		pthread_mutex_unlock(&philo->right->mutex_stick);
		*right = 0;
	}
	printf("%s is thinking\n", philo->name);
	usleep(1000000 * THINK_T);
	philo->state = DEFAULT;
}

static void			ft_philorest(t_philo *philo)
{
	printf("%s takes a break\n", philo->name);
	usleep(1000000 * REST_T);
	philo->state = DEFAULT;
}

static void			ft_philoeat(int *left, int *right, t_philo *philo)
{
	printf("%s is eating\n", philo->name);
	philo->pv = MAX_LIFE;
	usleep(1000000 * EAT_T);
	pthread_mutex_unlock(&philo->left->mutex_stick);
	pthread_mutex_unlock(&philo->right->mutex_stick);
	*left = 0;
	*right = 0;
	philo->state = REST;
}

void				*ft_philolunch(void *philo_ptr)
{
	t_philo			*philo;
	int				left;
	int				right;

	left = 0;
	right = 0;
	philo = (t_philo *)philo_ptr;
	printf("Hi my name is %s\n", philo->name);
	while (!g_stop)
	{
		if (philo->state == DEFAULT)
			ft_philodefault(&left, &right, philo);
		if (philo->state == THINK)
			ft_philothink(&left, &right, philo);
		if (philo->state == EAT)
			ft_philoeat(&left, &right, philo);
		if (philo->state == REST)
			ft_philorest(philo);
	}
	return (NULL);
}

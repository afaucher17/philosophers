/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <afaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/07 16:01:46 by afaucher          #+#    #+#             */
/*   Updated: 2014/05/08 17:47:39 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int g_stop = 0;

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
		{
			if (!pthread_mutex_trylock(&philo->left->mutex_stick))
			{
				printf("%s stole the stick at his left !\n", philo->name);
				left = 1;
			}
			else
				left = 0;
			if (!pthread_mutex_trylock(&philo->right->mutex_stick))
			{
				printf("%s stole the stick at his right !\n", philo->name);
				right = 1;
			}
			else
				right = 0;
			if (left + right == 2)
				philo->state = EAT;
			else if (left + right == 1)
				philo->state = THINK;
			else
				philo->state = DEFAULT;
		}
		if (philo->state == THINK)
		{
			if (left)
			{
				pthread_mutex_unlock(&philo->left->mutex_stick);
				left = 0;
			}
			if (right)
			{
				pthread_mutex_unlock(&philo->right->mutex_stick);
				right = 0;
			}
			printf("%s is thinking\n", philo->name);
			usleep(1000000 * THINK_T);
			philo->state = DEFAULT;
		}
		if (philo->state == EAT)
		{
			printf("%s is eating\n", philo->name);
			philo->pv = MAX_LIFE;
			usleep(1000000 * EAT_T);
			pthread_mutex_unlock(&philo->left->mutex_stick);
			pthread_mutex_unlock(&philo->right->mutex_stick);
			left = 0;
			right = 0;
			philo->state = REST;
		}
		if (philo->state == REST)
		{
			printf("%s takes a break\n", philo->name);
			usleep(1000000 * REST_T);
			philo->state = DEFAULT;
		}
	}
	return (NULL);
}

static void			*ft_life(void *philotab_ptr)
{
	int				i;
	int				secondsleft;
	t_philo			**philotab;

	philotab = (t_philo **)philotab_ptr;
	secondsleft = TIMEOUT;
	while (!g_stop && secondsleft > 0)
	{
		usleep(1000000);
		printf("-------------------------------------------\n");
		i = -1;
		while (++i < 7 && !g_stop)
		{
			if (philotab[i]->state != EAT)
			{
				philotab[i]->pv--;
				if (philotab[i]->pv <= 0)
				{
					printf("%s died from starvation.\n", philotab[i]->name);
					g_stop = 1;
				}
			}
			printf("%s is at %d pv\n", philotab[i]->name, philotab[i]->pv);
		}
		secondsleft--;
	}
	if (secondsleft <= 0 && !g_stop)
	{
		printf("Now, it is time... To DAAAAAAAANCE ! ! !\n");
		g_stop = 1;
	}
	return (NULL);
}

static int			ft_watcher_threads(t_philo **philotab)
{
	pthread_t		lifethread;

	pthread_create(&lifethread, NULL, ft_life, philotab);
	if (pthread_join(lifethread, NULL))
		exit(1);
	return (0);
}

int					main(void)
{
	int				i;
	t_stick			*sticktab[7];
	t_philo			*philotab[7];
	static char		*names[7] = {"Stilpon", "Chilon", "Thales", "Pythagore",

		"Empedocle", "Pherecyde", "Anacharsis"};
	i = -1;
	while (++i < 7)
		sticktab[i] = ft_create_stick();
	i = -1;
	while (++i < 7)
		philotab[i] = ft_create_philo(i + 1, names[i],
				sticktab[i], sticktab[(i + 1) % 7]);
	ft_watcher_threads(philotab);
	(void)philotab;
	return (0);
}

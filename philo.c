/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <afaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/07 16:01:46 by afaucher          #+#    #+#             */
/*   Updated: 2014/05/09 16:24:49 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int g_stop = 0;

static void			ft_decrement_life(t_philo **philotab)
{
	int				i;

	i = -1;
	while (++i < 7 && !g_stop)
	{
		if (philotab[i]->state != EAT)
		{
			philotab[i]->pv--;
			if (philotab[i]->pv <= 0)
				g_stop = 1;
		}
	}
}

static void			*ft_life(void *philotab_ptr)
{
	int				secondsleft;
	t_philo			**philotab;

	philotab = (t_philo **)philotab_ptr;
	secondsleft = TIMEOUT;
	while (!g_stop && secondsleft-- > 0)
	{
		usleep(1000000);
		ft_decrement_life(philotab);
	}
	if (secondsleft <= 0 && !g_stop)
		g_stop = 2;
	return (NULL);
}

static pthread_t	ft_watcher_threads(t_philo **philotab)
{
	pthread_t		lifethread;

	pthread_create(&lifethread, NULL, ft_life, philotab);
	return (lifethread);
}

int					main(void)
{
	int				i;
	t_stick			*sticktab[7];
	t_philo			*philotab[7];
	pthread_t		lifethread;
	static char		*names[7] = {"Stilpon", "Chilon", "Thales", "Pythagore",

	"Empedocle", "Pherecyde", "Anacharsis"};
	i = -1;
	while (++i < 7)
		sticktab[i] = ft_create_stick();
	i = -1;
	while (++i < 7)
		philotab[i] = ft_create_philo(i + 1, names[i],
				sticktab[i], sticktab[(i + 1) % 7]);
	lifethread = ft_watcher_threads(philotab);
	ft_ncurses(philotab);
	pthread_join(lifethread, NULL);
	return (0);
}

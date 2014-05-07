/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <afaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/07 16:01:46 by afaucher          #+#    #+#             */
/*   Updated: 2014/05/07 23:29:53 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void				*ft_philolunch(void *ptr_philo)
{
	t_philo			*philo;

	philo = (t_philo *)ptr_philo;
	printf("My name is %s\n", philo->name);
	pthread_detach(philo->thread);
	return (NULL);
}

static void			*ft_timebomb(void *philotab_ptr)
{
	int				i;
	t_philo			**philotab;

	philotab = (t_philo **)philotab_ptr;
	i = -1;
	usleep(1000000 * TIMEOUT);
	while (++i < 7)
		pthread_detach(philotab[i]->thread);
	printf("Now, it is time... To DAAAAAAAANCE ! ! !\n");
	return (NULL);
}

static pthread_t	ft_timebomb_create(t_philo **philotab)
{
	pthread_t		thread;

	pthread_create(&thread, NULL, ft_timebomb, philotab);
	return (thread);
}

int					main(void)
{
	int				i;
	t_stick			*sticktab[7];
	t_philo			*philotab[7];
	pthread_t		thread;
	static char		*names[7] = {"Stilpon", "Chilon", "Thales", "Pythagore",

	"Empedocle", "Pherecyde", "Anacharsis"};
	i = -1;
	while (++i < 7)
		sticktab[i] = ft_create_stick();
	i = -1;
	while (++i < 7)
		philotab[i] = ft_create_philo(i + 1, names[i],
		sticktab[i], sticktab[(i + 1) % 7]);
	thread = ft_timebomb_create(philotab);
	pthread_join(thread, NULL);
	(void)philotab;
	return (0);
}

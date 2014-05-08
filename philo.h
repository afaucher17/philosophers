/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <afaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/07 17:55:16 by afaucher          #+#    #+#             */
/*   Updated: 2014/05/08 17:44:44 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define MAX_LIFE 15
# define EAT_T 2
# define REST_T 2
# define THINK_T 2
# define TIMEOUT 30
# include <pthread.h>

enum				e_state
{
	DEFAULT = 0,
	EAT,
	REST,
	THINK
};

typedef struct		s_stick
{
	int				owner;
	pthread_mutex_t	mutex_stick;
}					t_stick;

typedef struct		s_philo
{
	int				id;
	char			*name;
	pthread_t		thread;
	enum e_state	state;
	int				pv;
	struct s_stick	*right;
	struct s_stick	*left;
}					t_philo;

t_philo				*ft_create_philo(int id, char *name, t_stick *left,
					t_stick *right);
t_stick				*ft_create_stick(void);
void				*ft_philolunch(void *philo);
#endif

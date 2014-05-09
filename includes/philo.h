/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <afaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/07 17:55:16 by afaucher          #+#    #+#             */
/*   Updated: 2014/05/09 20:28:28 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define MAX_LIFE 7
# define EAT_T 2
# define REST_T 3
# define THINK_T 2
# define TIMEOUT 15
# include <pthread.h>
# include <ncurses.h>

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

/*
** philo_fun.c
*/
t_philo				*ft_create_philo(int id, char *name, t_stick *left,
					t_stick *right);
t_stick				*ft_create_stick(void);

/*
** philolunch.c
*/
void				*ft_philolunch(void *philo);

/*
** ncurses.c
*/
int					ft_ncurses(t_philo **philotab);

/*
** ncurses_fun.c
*/
void				end_message(void);
int					get_attr(t_philo *philo);
char				*get_state(t_philo *philo);
void				ft_hpbar(WINDOW *local_win, int x, int y, t_philo *philo);

#endif

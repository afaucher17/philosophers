/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_hpbar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/09 19:16:56 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/05/09 20:03:22 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <ncurses.h>

extern int g_stop;

void				end_message(void)
{
	curs_set(0);
	if (g_stop == 1)
		mvprintw(LINES / 2, (COLS - 46) / 2,
				"One of the philosophers died from starvation.");
	else if (g_stop == 2)
		mvprintw(LINES / 2, (COLS - 40) / 2,
				"Now, it is time... To DAAAAAAAANCE ! ! !");
	mvprintw(LINES / 2 + 1, (COLS - 19) / 2, "(Press ESC to exit)");
	refresh();
}

int					get_attr(t_philo *philo)
{
	int				attr;

	if (philo->state == EAT)
		attr = 3;
	else if (philo->state == REST)
		attr = 2;
	else if (philo->state == THINK)
		attr = 1;
	else
		attr = 0;
	return (attr);
}

char				*get_state(t_philo *philo)
{
	char			*state;

	if (philo->state == EAT)
		state = "EATING";
	else if (philo->state == REST)
		state = "RESTING";
	else if (philo->state == THINK)
		state = "THINKING";
	else
		state = "WAITING";
	return (state);
}

void				ft_hpbar(WINDOW *local_win, int x, int y, t_philo *philo)
{
	int			i;
	int			attr;

	i = 0;
	init_pair(4, COLOR_RED, COLOR_RED);
	init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(6, COLOR_GREEN, COLOR_GREEN);
	while (i < philo->pv && i < 20)
	{
		if (philo->pv == 1)
			attr = 4;
		else if (philo->pv <= (MAX_LIFE / 2))
			attr = 5;
		else
			attr = 6;
		wattron(local_win, COLOR_PAIR(attr));
		mvwprintw(local_win, x + 1, y + i, " ");
		wattroff(local_win, COLOR_PAIR(attr));
		i++;
	}
}

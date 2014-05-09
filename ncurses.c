/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <afaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/09 14:38:48 by afaucher          #+#    #+#             */
/*   Updated: 2014/05/09 16:34:43 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#define ESC 27

extern int g_stop;

static void			showphilo(WINDOW *local_win, int x, int y, t_philo *philo)
{
	int				attr;

	attr = 0;
	if (philo->state == EAT)
		attr = 3;
	else if (philo->state == REST)
		attr = 2;
	else if (philo->state == THINK)
		attr = 1;
	wattron(local_win, COLOR_PAIR(attr));
	mvwprintw(local_win, x, y, philo->name);
	wattroff(local_win, COLOR_PAIR(attr));
	mvwprintw(local_win, x + 1, y, ft_itoa(philo->pv));
}

static WINDOW		*create_newwin(t_philo **philotab)
{
	WINDOW			*local_win;

	local_win = newwin(50, 140, (LINES - 50) / 2, (COLS - 140) / 2);
	showphilo(local_win, 8, 66, philotab[0]);
	showphilo(local_win, 15, 33, philotab[1]);
	showphilo(local_win, 28, 33, philotab[2]);
	showphilo(local_win, 38, 47, philotab[3]);
	showphilo(local_win, 38, 85, philotab[4]);
	showphilo(local_win, 28, 99, philotab[5]);
	showphilo(local_win, 15, 99, philotab[6]);
	box(local_win, 0, 0);
	wrefresh(local_win);
	return local_win;
}

void				destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}

int					ft_ncurses(t_philo **philotab)
{
	WINDOW			*local_win;
	int				ch;

	initscr();
	cbreak();
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	refresh();
	local_win = create_newwin(philotab);
	while (!g_stop)
	{
		destroy_win(local_win);
		local_win = create_newwin(philotab);
		wrefresh(local_win);
		usleep(1000000);
	}
	if (g_stop == 1)
		mvprintw(LINES / 2, COLS / 2, "One of your philosophers died from starvation.");
	else if (g_stop == 2)
		mvprintw(LINES / 2, COLS / 2, "Now, it is time... To DAAAAAAAANCE ! ! !");
	mvprintw(LINES / 2 + 1, COLS / 2, "(Press ESC to exit)");
	refresh();
	while ((ch = getch()) != ESC)
		;
	endwin();
	exit(1);
	return (0);
}

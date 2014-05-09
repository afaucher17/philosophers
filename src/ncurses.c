/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <afaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/09 14:38:48 by afaucher          #+#    #+#             */
/*   Updated: 2014/05/09 20:10:39 by tdieumeg         ###   ########.fr       */
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
	char			*state;

	mvwprintw(local_win, x, y, philo->name);
	ft_hpbar(local_win, x, y, philo);
	attr = get_attr(philo);
	state = get_state(philo);
	wattron(local_win, COLOR_PAIR(attr));
	mvwprintw(local_win, x + 2, y, state);
	wattroff(local_win, COLOR_PAIR(attr));
}

static WINDOW		*create_newwin(t_philo **philotab)
{
	WINDOW			*local_win;

	local_win = newwin(50, 140, (LINES - 50) / 2, (COLS - 140) / 2);
	mvprintw(2, (COLS - 28) / 2, "WELCOME TO THE HUNGER GAMES!");
	refresh();
	showphilo(local_win, 8, 66, philotab[0]);
	showphilo(local_win, 15, 33, philotab[1]);
	showphilo(local_win, 28, 33, philotab[2]);
	showphilo(local_win, 38, 47, philotab[3]);
	showphilo(local_win, 38, 85, philotab[4]);
	showphilo(local_win, 28, 99, philotab[5]);
	showphilo(local_win, 15, 99, philotab[6]);
	box(local_win, 0, 0);
	wrefresh(local_win);
	return (local_win);
}

static void			destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}

static void			init_colors(void)
{
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
}

int					ft_ncurses(t_philo **philotab)
{
	WINDOW			*local_win;
	int				ch;

	initscr();
	cbreak();
	init_colors();
	refresh();
	curs_set(0);
	while (!g_stop)
	{
		local_win = create_newwin(philotab);
		wrefresh(local_win);
		usleep(1000000);
		destroy_win(local_win);
	}
	local_win = create_newwin(philotab);
	wrefresh(local_win);
	end_message();
	while ((ch = getch()) != ESC)
		;
	endwin();
	exit(1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altikka <altikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:08:17 by altikka           #+#    #+#             */
/*   Updated: 2022/09/21 16:12:07 by altikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	validate_room(const char **room)
{
	char	*s;
	size_t	i;

	i = 0;
	return (1);
}

/*
** STRUCTURE
** i: validare S&E rooms
** ii: validate that line has '-'
** iii: init hashmap for links 
** iv: change STATE
** v: jump to parse_links
*/

static int relay_to_links(t_len *d, t_parser *p)
{
	p->state = LINKS;
	ft_printf("got rooms, next->links\n");//del
	return (parse_links(d, p));
}

/*
** STRUCTURE
** i: split by ' '
** ii: check whether we are at links already -> prepare jump to links via fun
** iii: validate line with room info
** iv: save room to t_lem struct
** v: assign S&E rooms
** vi: clean up
*/

int	parse_rooms(t_lem *d, t_parser *p)
{
	char	**room;

	room = ft_strslip(p->line, ' ');
	if (room[0] && !room[1])
	{
		ft_strdelarr(&room);
		relay_to_links(d, p);
	}
	if (validate_room(room) < 0)
	{
		ft_strdelarr(&room);
		return (free_parser(p, "Error: invalid line."));
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altikka & atenhune <@student.hive.fi>       +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:08:17 by altikka           #+#    #+#             */
/*   Updated: 2022/10/10 12:52:33 by altikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	save_room(t_lem *d, char *name, int x, int y)
{
	t_room	room;

	ft_bzero(&room, sizeof(t_room));
	room.name = name;
	room.index = d->rooms.len;
	room.x = x;
	room.y = y;
	if (ft_vecnew(&room.links, 1, sizeof(int)) < 0)
		return (panic(NULL, "Error: Couldn't initialize room's links"));
	if (ft_vecpush(&d->rooms, &room) < 0)
		return (panic(NULL, "Error: Memory issue while saving room."));
	return (1);
}

static int	validate_room(t_parser *p, char **room)
{
	char	*s;
	size_t	i;

	if (ft_cntchr(p->line, ' ') != 2)
		return (panic(NULL, "Error: Wrong ammount of delimiters."));
	i = 0;
	while (room[i])
	{
		s = room[i];
		if (i == 0 && (*s == 'L' || ft_strchr(s, '-') || ft_isspace(*s)))
			return (panic(NULL, "Error: Invalid room name."));
		if ((i == 1 || i == 2) && !ft_isnbr(s))
			return (panic(NULL, "Error: Invalid room coordinates."));
		i++;
	}
	if (i != 3)
		return (panic(NULL, "Error: Invalid room info."));
	return (1);
}

static int	lookup_and_insert(t_lem *d, t_parser *p)
{
	t_room	*temp;
	size_t	i;

	i = 0;
	while (i < d->rooms.len)
	{
		temp = ft_vecget(&d->rooms, i);
		if (!hash_lookup(temp->name, *(&p->table)))
			return (panic(NULL, "Error: Duplicated room in hash table."));
		if (!hash_insert(temp->name, temp->index, *(&p->table)))
			return (panic(NULL, "Error: Hash table full."));
		i++;
	}
	return (1);
}

/*
** STRUCTURE
** i: validare start & rooms
** ii: validate that line has '-'
** iii: init hashmap for links 
** iv: change STATE
** v: jump to parse_links
*/

static int	relay_to_links(t_lem *d, t_parser *p)
{
	if (d->start == -1 || d->end == -1 || p->start != 1 || p->end != 1)
		return (panic(NULL, "Error: Missing or multiple start/end rooms."));
	if (!ft_strchr(p->line, '-'))
		return (panic(NULL, "Error: No links."));
	if (lookup_and_insert(d, p) < 0)
		return (panic(NULL, "Error: Hash table error."));
	p->state = LINKS;
	return (parse_links(d, p));
}

/*
** STRUCTURE
** i: split by ' '
** ii: check whether we are at links already -> prepare jump to links
** iii: validate line with room info
** iv: save room to t_lem d
** v: assign start & rooms
*/

int	parse_rooms(t_lem *d, t_parser *p)
{
	char	**room;

	room = ft_strsplit(p->line, ' ');
	if (room[0] && !room[1])
		return (ft_strdelarr(&room), relay_to_links(d, p));
	if (validate_room(p, room) < 0)
	{
		ft_strdelarr(&room);
		return (panic(NULL, "Error: Invalid room."));
	}
	if (!ft_isnbr(room[1]) || !ft_isnbr(room[2]))
		return (ft_strdelarr(&room), panic(NULL, "Error: Invalid room coord."));
	if (save_room(d, ft_strdup(room[0]),
			ft_atoi(room[1]),
			ft_atoi(room[2])) < 0)
		return (ft_strdelarr(&room), panic(NULL, "Error: Saving room failed."));
	ft_strdelarr(&room);
	return (1);
}

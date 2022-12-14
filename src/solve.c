/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altikka & atenhune <@student.hive.fi>       +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:55:18 by atenhune          #+#    #+#             */
/*   Updated: 2022/10/10 11:34:06 by altikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** IDEA
** After initializing bfs struct program calls
** bfs function until path(s) can no longer
** be found. This results in either the best possible pathset
** or no solution at all.
*/

int	solve(t_lem *d, t_bfs *bf)
{
	int	ret;

	if (d->start_to_end == true)
		return (1);
	if (init_bfs(d, bf) < 0)
		return (panic(NULL, "Error: Failed to initialize bfs."));
	ret = 1;
	while (ret == 1)
	{
		ret = bfs(d, bf);
		if (ret < 0)
			return (panic_bfs(d, bf, "Error: Memory issue in bfs."));
	}
	if (!bf->best)
		return (panic_bfs(d, bf, "Error: Failed to find a path."));
	return (1);
}

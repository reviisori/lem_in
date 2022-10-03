/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_printer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atenhune <atenhune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:18:54 by atenhune          #+#    #+#             */
/*   Updated: 2022/10/03 16:21:31 by atenhune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_printer(t_printer *p)
{
	if (p->result.data)
		ft_vecdel(&p->result);
	if (p->ant_line)
		free(p->ant_line);
}

int	panic_printer(t_printer *p, const char *msg)
{
	ft_putendl_fd(msg, 2);
	if (p)
		free_printer(p);
	return (-1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaunder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 06:38:30 by bsaunder          #+#    #+#             */
/*   Updated: 2016/05/13 16:45:00 by bsaunder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	int						i;
	unsigned char			*tmp_dest;
	const unsigned char		*tmp_src;

	i = 0;
	tmp_dest = dest;
	tmp_src = src;
	while (n > 0)
	{
		tmp_dest[i] = tmp_src[i];
		if (tmp_dest[i] == (unsigned char)c)
		{
			return (dest + 1 + i);
		}
		i++;
		n--;
	}
	return (0);
}

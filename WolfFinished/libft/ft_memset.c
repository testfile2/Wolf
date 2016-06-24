/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaunder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 06:35:10 by bsaunder          #+#    #+#             */
/*   Updated: 2016/05/13 11:16:26 by bsaunder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t n)
{
	size_t			cmp;
	unsigned char	*ptrmem;

	cmp = 0;
	ptrmem = (unsigned char *)dst;
	while (cmp < n)
	{
		ptrmem[cmp] = (unsigned char)c;
		cmp++;
	}
	return (dst);
}

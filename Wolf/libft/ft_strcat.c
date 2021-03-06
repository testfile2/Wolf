/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaunder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 06:46:39 by bsaunder          #+#    #+#             */
/*   Updated: 2016/06/14 13:28:58 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		i;

	i = ft_strlen(s1) + ft_strlen(s2);
	while (*s1)
	{
		s1++;
	}
	while (*s2)
	{
		*s1++ = *s2++;
	}
	*s1 = '\0';
	return (s1 - i);
}

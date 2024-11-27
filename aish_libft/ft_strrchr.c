/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:32:34 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/11 12:35:09 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*s1;
	int		len;

	len = ft_strlen(s) - 1;
	i = 0;
	s1 = (char *)s;
	if ((char)c == '\0')
		return (s1 + ft_strlen(s));
	if (s[0] == '\0')
		return (NULL);
	while (len >= 0 && s1[len] != (unsigned char)c)
		len --;
	if (len == -1)
		return (NULL);
	return (s1 + len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:18:47 by amann             #+#    #+#             */
/*   Updated: 2021/12/31 12:35:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*res;

	res = (t_list *) ft_memalloc(sizeof(t_list));
	if (!res)
		return (NULL);
	if (!content)
        return (res);
    res->content = ft_memalloc(content_size);
    if (!(res->content))
    {
        free(res);
        return (NULL);
    }
    ft_memcpy(res->content, content, content_size);
    res->content_size = content_size;
	return (res);
}

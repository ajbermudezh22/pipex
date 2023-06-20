/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:37:35 by albermud          #+#    #+#             */
/*   Updated: 2023/06/20 18:37:38 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4242
# endif

typedef struct s_stream
{
	int				fd;
	ssize_t			len;
	size_t			off;
	unsigned char	buff[BUFFER_SIZE];
}	t_stream;

char			*get_next_line(int fd);
void			*ft_memgrow(void *ptr, size_t old_size, size_t new_size);

#endif

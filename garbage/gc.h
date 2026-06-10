/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:05:42 by MP9               #+#    #+#             */
/*   Updated: 2026/04/08 14:34:24 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

extern void				__real_free(void *ptr);
extern void				*__real_malloc(size_t size);
extern void				__real_exit(int status);

typedef struct s_garbage
{
	void				*content;
	struct s_garbage	*next;
	struct s_garbage	*prev;
}						t_garbage;

t_garbage				**get_gc_start(void);
void					ft_putstr_err(char *s);
void					__wrap_exit(int status);
void					*__wrap_malloc(size_t size);
void					__wrap_free(void *ptr);
void					add_node_gc(void *ptr);
void					clear_gc(void);

#endif
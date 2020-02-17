/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:42:48 by aannara           #+#    #+#             */
/*   Updated: 2020/01/31 19:58:03 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# pragma pack(push, 1)

typedef struct		s_bmp
{
	unsigned short	bftype;
	unsigned int	bfsize;
	unsigned int	bfreserved;
	unsigned int	bfoffbits;
	unsigned int	bisize;
	int				biwidth;
	int				biheight;
	unsigned short	biplanes;
	unsigned short	bibitcount;
	unsigned int	bicompression;
	unsigned int	bisizeimage;
	int				bixpelspermeter;
	int				biypelspermeter;
	unsigned int	biclrused;
	unsigned int	biclrimportant;
}					t_bmp;

# pragma pack(pop)

int					*loadbmp(const char *fn, int *mx, int *my);

#endif

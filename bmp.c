/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:29:33 by aannara           #+#    #+#             */
/*   Updated: 2020/01/31 19:56:12 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

int		*set_image_data(int mx, int my, int mx3, unsigned char *tmp)
{
	int				*img;
	int				x;
	int				y;
	unsigned char	*ptr;
	unsigned char	*prow;

	x = 0;
	y = my - 1;
	img = (int*)malloc(mx * my * sizeof(int));
	if (img == NULL)
		return (NULL);
	ptr = (unsigned char *)img;
	while (y >= 0)
	{
		prow = tmp + mx3 * y;
		while (x < mx)
		{
			*ptr++ = *prow;
			*ptr++ = *(prow + 1);
			*ptr++ = *(prow + 2);
			prow += 3;
			ptr++;
			x++;
		}
		y--;
		x = 0;
	}
	return (img);
}

int		*loadbmp(const char *fn, int *mx, int *my)
{
	int				fd;
	t_bmp			bh;
	size_t			res;
	int				mx3;
	unsigned char	*tmp;
	int				*image;

	*mx = -1;
	*my = -1;
	fd = open(fn, O_RDONLY);
	if (fd < 0)
		return (NULL);
	res = read(fd, (void*)(&bh), sizeof(t_bmp));
	if (res != sizeof(t_bmp))
	{
		write(1, "bad bmp\n", 8);
		close(fd);
		return (NULL);
	}
	if (bh.bftype != 0x4d42 && bh.bftype != 0x4349 && bh.bftype != 0x5450)
	{
		write(1, "bmp bad signature\n", 18);
		close(fd);
		return (NULL);
	}
	if (bh.bfreserved != 0 ||
		bh.biplanes != 1 ||
		(bh.bisize != 40 && bh.bisize != 108 && bh.bisize != 124) ||
		bh.bfoffbits != 14 + bh.bisize ||
		bh.biwidth < 1 || bh.biwidth > 10000 ||
		bh.biheight < 1 || bh.biheight > 10000 ||
		bh.bibitcount != 24 ||
		bh.bicompression != 0)
	{
		write(1, "bmp bad format\n", 15);
		close(fd);
		return (NULL);
	}
	*mx = bh.biwidth;
	*my = bh.biheight;
	mx3 = (3 * *mx + 3) & (-4);
	tmp = (unsigned char*)malloc(mx3 * *my);
	res = read(fd, tmp, mx3 * *my);
	close(fd);
	image = set_image_data(*mx, *my, mx3, tmp);
	free(tmp);
	if (image == NULL)
	{
		write(1, "bmp read error\n", 15);
	}
	return (image);
}

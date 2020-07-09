/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2025.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 17:38:47 by ijang             #+#    #+#             */
/*   Updated: 2020/07/09 17:38:19 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int		greed[680][680] = { 0, };
int		*his;

int	mx[2][8] = {
	{ 1, 2, 2, 1, -1, -2, -2, -1 },
	{ -1, -2, -2, -1, 1, 2, 2, 1 }
};
int	my[2][8] = {
	{ -2, -1, 1, 2, 2, 1, -1, -2 },
	{ -2, -1, 1, 2, 2, 1, -1, -2 }
};

void	de_greed(int x, int y)
{
	int	i = -1;
	greed[x][y] = -1;
	while (++i < 8)
		--greed[x + mx[0][i]][y + my[0][i]];
}

void	init_greed(size_t size)
{
	greed[2][2] = 2;
	greed[2][size + 1] = 2;
	greed[size + 1][2] = 2;
	greed[size + 1][size + 1] = 2;
	greed[3][2] = 3;
	greed[size][2] = 3;
	greed[size + 1][3] = 3;
	greed[size + 1][size] = 3;
	greed[size][size + 1] = 3;
	greed[3][size + 1] = 3;
	greed[2][size] = 3;
	greed[2][3] = 3;
	greed[3][3] = 4;
	greed[size][3] = 4;
	greed[3][size] = 4;
	greed[size][size] = 4;
	int	x = 2;
	int	y = 3;
	while (++y < size)
		greed[x][y] = 4;
	++x;
	y = 3;
	while (++y < size)
		greed[x][y] = 6;
	while (++x < size)
	{
		greed[x][2] = 4;
		greed[x][3] = 6;
		greed[x][size] = 6;
		greed[x][size + 1] = 4;
		y = 3;
		while (++y < size)
			greed[x][y] = 8;
	}
	y = 3;
	while (++y < size)
		greed[x][y] = 6;
	++x;
	y = 3;
	while (++y < size)
		greed[x][y] = 4;
}

int	move(int *x, int *y, int count, int seed1, int seed2)
{
	de_greed(*x + 1, *y + 1);
	int i = -1;
	int	cal;
	int	tmp[2];
	int	min_i = -1, min_g = 65;
	int tmp_x, tmp_y;
	while (++i < 8)
	{
		cal = (i + seed2) % 8;
		tmp_x = *x + mx[seed1][cal];
		tmp_y = *y + my[seed1][cal];
		tmp = greed[tmp_x + 1][tmp_y + 1];
		if (tmp >= 0 && tmp <= min_g)
		{
			if (tmp == min_g )
			min_i = cal;
			min_g = tmp[1];
		}
	}
	if (min_i == -1)
		return (0);
	*x += mx[seed1][min_i];
	*y += my[seed1][min_i];
	his[count * 2] = *x;
	his[count * 2 + 1] = *y;
	return (1);
}

int	main(void)
{
	int		x = -1;
	int		y = -1;
	int		seed1 = 0;
	int		seed2 = 0;
	size_t	count;
	size_t	size;
	size_t	times;

	while (++x < 680)
	{
		y = -1;
		while (++y < 680)
			greed[x][y] = -1;
	}
	scanf("%zd", &size);
	init_greed(size);
	scanf("%d %d", &x, &y);
	times = size * size;
	if(!(his = (int *)malloc(times * 2 * sizeof(int))))
	{
		printf("malloc error\n");
		return (-1);
	}
	his[0] = x;
	his[1] = y;
	while (seed1 < 2)
	{
		x = his[0];
		y = his[1];
		count = 1;
		while (count < times && move(&x, &y, count, seed1, seed2))
			++count;
		if (count == times)
		{
			int	i = -1;
			while (++i < times)
				printf("%d %d\n", his[2 * i], his[2 * i + 1]);
			break ;
		}
		if (++seed2 == 8)
		{
			seed2 = 0;
			++seed1;
		}
		init_greed(size);
	}
	if (seed1 == 2)
		write(1, "-1 -1", 5);
	free(his);
	return (0);
}

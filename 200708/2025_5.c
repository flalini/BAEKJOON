/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2025.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 17:38:47 by ijang             #+#    #+#             */
/*   Updated: 2020/07/08 17:50:44 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int		greed[680][680] = { 0, };
size_t	size;
size_t	times;
int		*his;

int	mx[8] = { 1, 1, 2, 2, -1, -1, -2, -2 };
int my[8] = { 2, -2, 1, -1, 2, -2, 1, -1 };

void	de_greed(int x, int y)
{
	int	i = -1;
	greed[x][y] = -1;
	while (++i < 8)
		--greed[x + mx[i]][y + my[i]];
}

int	move(int x, int y, int count)
{
	if (++count == times)
	{
		his[count * 2] = x;
		his[count * 2 + 1] = y;
		return (1);
	}
	de_greed(x + 1, y + 1);
	int i = -1;
	int	tmp;
	int	min_i = -1, min_g = 9;
	int tmp_x, tmp_y;
	while (++i < 8)
	{
		tmp_x = x + mx[i];
		tmp_y = y + my[i];
		tmp = greed[tmp_x + 1][tmp_y + 1];
		if (tmp >= 0 && tmp < min_g)
		{
			min_i = i;
			min_g = tmp;
			if (tmp == 1)
				break ;
		}
	}
	if (min_i == -1)
		return (0);
	if (move(x + mx[min_i], y + my[min_i], count))
	{
		his[count * 2] = x;
		his[count * 2 + 1] = y;
		return (1);
	}
	return (0);
}

int	main(void)
{
	int	x = -1;
	int	y = -1;

	while (++x < 680)
	{
		y = -1;
		while (++y < 680)
			greed[x][y] = -1;
	}
	scanf("%zd", &size);
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
	x = 2;
	y = 3;
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
	scanf("%d %d", &x, &y);
	times = size * size;
	if(!(his = (int *)malloc(times * 2 * sizeof(int))))
	{
		printf("malloc error\n");
		return (-1);
	}
	--times;
	if (move(x, y, -1))
	{
		++times;
		int	i = -1;
		while (++i < times)
			printf("%d %d\n", his[2 * i], his[2 * i + 1]);
	}
	else
		write(1, "-1 -1", 5);
	free(his);
	return (1);
}

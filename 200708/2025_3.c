/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2025.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 17:38:47 by ijang             #+#    #+#             */
/*   Updated: 2020/07/08 16:45:20 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int	his[887112]= { 0, };
int	greed[670][670] = { 0, };
int	size;
int	times;

int	mx[8] = { 1, 1, 2, 2, -1, -1, -2, -2 };
int my[8] = { 2, -2, 1, -1, 2, -2, 1, -1 };

void	print_greed(int x, int y)
{
	int	i = -1;
	int	j;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - 1)
		{
			if (i == x && j == y)
				printf("* ");
			else
				printf("%d ", greed[i + 2][j + 2]);
		}
		printf("\n");
	}
	printf("\n");
}

void	de_greed(int x, int y)
{
	int	i = -1;
	while (++i < 8)
		--greed[x + mx[i]][y + my[i]];
}

void	in_greed(int x, int y)
{
	int	i = -1;
	while (++i < 8)
		++greed[x + mx[i]][y + my[i]];
}

int	explore(int x, int y, int flag[667][667])
{
	int	result = 0;
	int	count = -1;

	while (++count < 8)
		if (x + mx[count] > 0 && x + mx[count] < size && y + my[count] > 0 && y + my[count] < size && !flag[x + mx[count]][y + my[count]])
			++result;
	return (result);
}

int	move(int x, int y, int flag[667][667], int count)
{
	printf("\n\n%d %d %d\n", x, y, count);
	if (++count == times)
	{
		his[count * 2] = x;
		his[count * 2 + 1] = y;
		return (1);
	}
	flag[x][y] = 1;
	de_greed(x + 1, y + 1);
	print_greed(x - 1, y - 1);
	int i = -1;
	int	j, tmp;
	int	result[8][8] = { 0, };
	int tmp_x, tmp_y;
	printf("\n");
	while (++i < 8)
	{
		tmp_x = x + mx[i];
		tmp_y = y + my[i];
		tmp = greed[tmp_x + 1][tmp_y + 1];
		printf("%d ", tmp);
		if (tmp >= 0 && !flag[tmp_x][tmp_y])
		{
			j = 0;
			while (result[tmp][j])
				++j;
			result[tmp][j] = i + 1;
		}
	}
	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (result[i][++j])
			if (move(x + mx[result[i][j] - 1], y + my[result[i][j] - 1], flag, count))
			{
				his[count * 2] = x;
				his[count * 2 + 1] = y;
				return (1);
			}
	}
	flag[x][y] = 0;
	in_greed(x + 1, y + 1);
	return (0);
}

int	main(void)
{
	int	x = -1;
	int	y = -1;
	int	flag[667][667] = { 0, };

	while (++x < 670)
	{
		y = -1;
		while (++y < 670)
			greed[x][y] = -1;
	}
	scanf("%d", &size);
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
	times = size * size - 1;
	++size;
	print_greed(x - 1, y - 1);
	if (move(x, y, flag, -1) || 1)
	{
		++times;
		int	i = -1;
		while (++i < times)
			printf("%d %d %d\n", his[2 * i], his[2 * i + 1], i);
	}
	else
		write(1, "-1 -1", 5);
	return (1);
}

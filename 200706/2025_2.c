/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2025.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 17:38:47 by ijang             #+#    #+#             */
/*   Updated: 2020/07/06 15:51:06 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	his[887112]= { 0, };
int	size;
int	times;

int	mx[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
int my[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };

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
	if (count == times)
		return (1);
	flag[x][y] = 1;
	his[count * 2] = x;
	his[count * 2 + 1] = y;
	int i = -1;
	int	j, tmp;
	int	result[9][8] = { 0, };
	int tmp_x, tmp_y;
	while (++i < 8)
	{
		tmp_x = x + mx[i];
		tmp_y = y + my[i];
		if (tmp_x > 0 && tmp_x < size && tmp_y > 0 && tmp_y < size && !flag[tmp_x][tmp_y])
		{
			j = -1;
			tmp = explore(tmp_x, tmp_y, flag);
			while (++j < 8)
				if (!result[tmp][j])
				{
					result[tmp][j] = i;
					break ;
				}
		}
	}
	i = -1;
	while (++i < 9)
	{
		j = -1;
		while (result[i][++j])
			if (move(x + mx[result[i][j]], y + my[result[i][j]], flag, ++count))
				return (1);
	}
	flag[x][y] = 0;
	return (0);
}

int	main(void)
{
	int	count;
	int	x, y;
	int	flag[667][667] = { 0, };

	scanf("%d", &size);
	scanf("%d %d", &x, &y);
	times = size * size;
	++size;
	if (move(x, y, flag, 0))
	{
		int	i = -1;
		while (++i < times)
			printf("%d %d %d %d\n", his[2 * i], his[2 * i + 1], flag[his[2 * i]][his[2 * i + 1]], i);
	}
	else
		write(1, "-1 -1", 5);
	return (1);
}

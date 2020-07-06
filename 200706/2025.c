/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2025.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 17:38:47 by ijang             #+#    #+#             */
/*   Updated: 2020/07/05 16:12:16 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	his[887112]= { 0, };
int	size;
int	times;

int	ur(int x, int y, int flag[667][667], int count);
int	ul(int x, int y, int flag[667][667], int count);
int	dr(int x, int y, int flag[667][667], int count);
int	dl(int x, int y, int flag[667][667], int count);
int	ru(int x, int y, int flag[667][667], int count);
int	rd(int x, int y, int flag[667][667], int count);
int	lu(int x, int y, int flag[667][667], int count);
int	ld(int x, int y, int flag[667][667], int count);

int	main(void)
{
	int	count;
	int	x, y;
	int	flag[667][667] = { 0, };

	scanf("%d", &size);
	scanf("%d %d", &x, &y);
	his[0] = x;
	his[1] = y;
	flag[x][y] = 1;
	times = size * size;
	if (y - 2 > 0 && (ur(x + 1, y - 2, flag, 0) || ul(x - 1, y - 2, flag, 0)))
	{
		int	i = -1;
		while (++i < times)
			printf("%d %d\n", his[2 * i], his[2 * i + 1]);
	}
	else if (y + 2 <= size && (dr(x + 1, y + 2, flag, 0) || dl(x - 1, y + 2, flag, 0)))
	{
		int	i = -1;
		while (++i < times)
			printf("%d %d\n", his[2 * i], his[2 * i + 1]);
	}
	else if (x + 2 <= size && (ru(x + 2, y - 1, flag, 0) || rd(x + 2, y + 1, flag, 0)))
	{
		int	i = -1;
		while (++i < times)
			printf("%d %d\n", his[2 * i], his[2 * i + 1]);
	}
	else if (x - 2 > size && (lu(x - 2, y - 1, flag, 0) || ld(x - 2, y + 1, flag, 0)))
	{
		int	i = -1;
		while (++i < times)
			printf("%d %d\n", his[2 * i], his[2 * i + 1]);
	}
	else
		write(1, "-1 -1", 5);
}

int	ur(int x, int y, int flag[667][667], int count)
{
	if (++count == times)
		return (1);
	if (x > size || flag[x][y])
		return (0);
	flag[x][y] = 1;
	his[2 * count] = x;
	his[2 * count + 1] = y;
	if (y - 2 > 0 && (ur(x + 1, y - 2, flag, count) || ul(x - 1, y - 2, flag, count)))
		return (1);
	if (x + 2 <= size && (ru(x + 2, y - 1, flag, count) || rd(x + 2, y + 1, flag, count)))
		return (1);
	if (x - 2 > 0 && (lu(x - 2, y - 1, flag, count) || ld(x - 2, y + 1, flag, count)))
		return (1);
	if (y + 2 <= size && dr(x + 1, y + 2, flag, count))
		return (1);
	flag[x][y] = 0;
	return (0);
}

int	ul(int x, int y, int flag[667][667], int count)
{
	if (++count == times)
		return (1);
	if (x <= 0 || flag[x][y])
		return (0);
	flag[x][y] = 1;
	his[2 * count] = x;
	his[2 * count + 1] = y;
	if (y - 2 > 0 && (ul(x - 1, y - 2, flag, count) || ur(x + 1, y - 2, flag, count)))
		return (1);
	if (x - 2 > 0 && (lu(x - 2, y - 1, flag, count) || ld(x - 2, y + 1, flag, count)))
		return (1);
	if (x + 2 <= size && (ru(x + 2, y - 1, flag, count) || rd(x + 2, y + 1, flag, count)))
		return (1);
	if (y + 2 <= size && dl(x - 1, y + 2, flag, count))
		return (1);
	flag[x][y] = 0;
	return (0);
}

int	dr(int x, int y, int flag[667][667], int count)
{
	if (++count == times)
		return (1);
	if (x > size || flag[x][y])
		return (0);
	flag[x][y] = 1;
	his[2 * count] = x;
	his[2 * count + 1] = y;
	if (y + 2 <= size && (dr(x + 1, y + 2, flag, count) || dl(x - 1, y + 2, flag, count)))
		return (1);
	if (x + 2 <= size && (rd(x + 2, y + 1, flag, count) || ru(x + 2, y - 1, flag, count)))
		return (1);
	if (x - 2 > 0 && (ld(x - 2, y + 1, flag, count) || lu(x - 2, y - 1, flag, count)))
		return (1);
	if (y - 2 > 0 && ur(x + 1, y - 2, flag, count))
		return (1);
	flag[x][y] = 0;
	return (0);
}

int	dl(int x, int y, int flag[667][667], int count)
{
	if (++count == times)
		return (1);
	if (x <= 0 || flag[x][y])
		return (0);
	flag[x][y] = 1;
	his[2 * count] = x;
	his[2 * count + 1] = y;
	if (y + 2 <= size && (dl(x - 1, y + 2, flag, count) || dr(x + 1, y + 2, flag, count)))
		return (1);
	if (x - 2 > 0 && (ld(x - 2, y + 1, flag, count) || lu(x - 2, y - 1, flag, count)))
		return (1);
	if (x + 2 <= size && (rd(x + 2, y + 1, flag, count) || ru(x + 2, y - 1, flag, count)))
		return (1);
	if (y - 2 > 0 && ul(x - 1, y - 2, flag, count))
		return (1);
	flag[x][y] = 0;
	return (0);
}

int	ru(int x, int y, int flag[667][667], int count)
{
	if (++count == times)
		return (1);
	if (y <= 0 || flag[x][y])
		return (0);
	flag[x][y] = 1;
	his[2 * count] = x;
	his[2 * count + 1] = y;
	if (x + 2 <= size && (ru(x + 2, y - 1, flag, count) || rd(x + 2, y + 1, flag, count)))
		return (1);
	if (y - 2 > 0 && (ur(x + 1, y - 2, flag, count) || ul(x - 1, y - 2, flag, count)))
		return (1);
	if (y + 2 <= size && (dr(x + 1, y + 2, flag, count) || dl(x - 1, y + 2, flag, count)))
		return (1);
	if (x - 2 > 0 && lu(x - 2, y - 1, flag, count))
		return (1);
	flag[x][y] = 0;
	return (0);
}

int	rd(int x, int y, int flag[667][667], int count)
{
	if (++count == times)
		return (1);
	if (y > size || flag[x][y])
		return (0);
	flag[x][y] = 1;
	his[2 * count] = x;
	his[2 * count + 1] = y;
	if (x + 2 <= size && (rd(x + 2, y + 1, flag, count) || ru(x + 2, y - 1, flag, count)))
		return (1);
	if (y + 2 <= size && (dr(x + 1, y + 2, flag, count) || dl(x - 1, y + 2, flag, count)))
		return (1);
	if (y - 2 > 0 && (ur(x + 1, y - 2, flag, count) || ul(x - 1, y - 2, flag, count)))
		return (1);
	if (x - 2 > 0 && lu(x - 2, y - 1, flag, count))
		return (1);
	flag[x][y] = 0;
	return (0);
}

int	lu(int x, int y, int flag[667][667], int count)
{
	if (++count == times)
		return (1);
	if (y <= 0 || flag[x][y])
		return (0);
	flag[x][y] = 1;
	his[2 * count] = x;
	his[2 * count + 1] = y;
	if (x - 2 > 0 && (lu(x - 2, y - 1, flag, count) || ld(x - 2, y + 1, flag, count)))
		return (1);
	if (y - 2 > 0 && (ul(x - 1, y - 2, flag, count) || ur(x + 1, y - 2, flag, count)))
		return (1);
	if (y + 2 <= size && (dl(x - 1, y + 2, flag, count) || dr(x + 1, y + 2, flag, count)))
		return (1);
	if (x + 2 <= size && ru(x + 2, y - 1, flag, count))
		return (1);
	flag[x][y] = 0;
	return (0);
}

int	ld(int x, int y, int flag[667][667], int count)
{
	if (++count == times)
		return (1);
	if (y > size || flag[x][y])
		return (0);
	flag[x][y] = 1;
	his[2 * count] = x;
	his[2 * count + 1] = y;
	if (x - 2 > 0 && (ld(x - 2, y + 1, flag, count) || lu(x - 2, y - 1, flag, count)))
		return (1);
	if (y + 2 <= size && (dl(x - 1, y + 2, flag, count) || dr(x + 1, y + 2, flag, count)))
		return (1);
	if (y - 2 > 0 && (ul(x - 1, y - 2, flag, count) || ur(x + 1, y - 2, flag, count)))
		return (1);
	if (x + 2 <= size && ru(x + 2, y - 1, flag, count))
		return (1);
	flag[x][y] = 0;
	return (0);
}

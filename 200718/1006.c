/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   1006.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ijang <marvin@42.fr>					   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/07/13 17:48:54 by ijang			 #+#	#+#			 */
/*   Updated: 2020/07/18 17:55:36 by ijang            ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	n, w;
int	e[20000], a[10001], b[10000], c[10000];
int	p[10000][3];

void	solve(int start) {
	for (int i = start; i < n; i++)
	{
		if (b[i] < c[i])
			a[i + 1] = b[i] + 1;
		else
			a[i + 1] = c[i] + 1;
		if (p[i][0] && a[i + 1] > a[i] + 1)
			a[i + 1] = a[i] + 1;
		if (i > 0 && p[i - 1][1] && p[i - 1][2] && a[i + 1] > a[i - 1] + 2)
			a[i + 1] = a[i - 1] + 2;
		if (i < n - 1)
		{
			b[i + 1] = a[i + 1] + 1;
			if (p[i][1] && b[i + 1] > c[i] + 1)
				b[i + 1] = c[i] + 1;
			c[i + 1] = a[i + 1] + 1;
			if (p[i][2] && c[i + 1] > b[i] + 1)
				c[i + 1] = b[i] + 1;
		}
	}
}
 
void	init_p(void)
{
	int	j = -1;

	while (++j < n - 1)
	{
		if (e[j] + e[j + n] <= w)
			p[j][0] = 1;
		else
			p[j][0] = 0;
		if (e[j] + e[j + 1] <= w)
			p[j][1] = 1;
		else
			p[j][1] = 0;
		if (e[j + n] + e[j + n + 1] <= w)
			p[j][2] = 1;
		else
			p[j][2] = 0;
		}
	if (e[j] + e[j + n] <= w)
		p[j][0] = 1;
	else
		p[j][0] = 0;
	if (e[j] + e[0] <= w)
		p[j][1] = 1;
	else
		p[j][1] = 0;
	if (e[j + n] + e[j] <= w)
		p[j][2] = 1;
	else
		p[j][2] = 0;
}

int		main(void)
{
	int	tc;
	int	i, res;

	scanf("%d", &tc);
	while (tc--)
	{
		scanf("%d %d", &n, &w);
		i = -1;
		while (++i < 2 * n)
			scanf("%d", &e[i]);
		init_p();
		a[0] = 0;
		b[0] = c[0] = 1;
		solve(0);
		res = a[n];
		if (n > 1 && p[n - 1][1])
		{
			a[1] = 1;
			b[1] = 2;
			c[1] = p[0][2] ? 1 : 2;
			solve(1);
			if (res > c[n - 1] + 1)
				res = c[n - 1] + 1;
		}
		if (n > 1 && p[n - 1][2])
		{
			a[1] = 1;
			b[1] = p[0][1] ? 1 : 2;
			c[1] = 2;
			solve(1);
			++b[n - 1];
			if (res > b[n - 1] + 1)
				res = b[n - 1] + 1;
		}
		if (n > 1 && p[n - 1][1] && p[n - 1][2]) {
			a[1] = 0;
			b[1] = c[1] = 1;
			solve(1);
			if (res > a[n - 1] + 2)
				res = a[n - 1] + 2;
		}
		printf("%d\n", res);
	}
	return (0);
}

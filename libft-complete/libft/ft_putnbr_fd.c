/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:52:32 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:52:35 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_display(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_display('-', fd);
		ft_putnbr_fd(2, fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_display ('-', fd);
		n = -n;
	}
	if (n < 10)
	{
		ft_display(n + '0', fd);
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
/*int	main(void)
{
	ft_putnbr_fd(42,1);

}
*/
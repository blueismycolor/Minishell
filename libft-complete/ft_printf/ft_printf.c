/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:36:35 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:36:39 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_type_handling(char type_format, va_list ap)
{
	int	count;

	count = 0;
	if (type_format == 'c')
		count = ft_print_char(va_arg(ap, int));
	else if (type_format == 's')
		count = ft_print_str(va_arg(ap, char *));
	else if (type_format == 'p')
		count = ft_print_pointer(va_arg(ap, void *));
	else if (type_format == 'd' || type_format == 'i')
		count = ft_print_int(va_arg(ap, int));
	else if (type_format == 'u')
		count = ft_print_unsigned(va_arg(ap, unsigned int));
	else if (type_format == 'x')
		count = ft_print_hexa(va_arg(ap, unsigned int), 0);
	else if (type_format == 'X')
		count = ft_print_hexa(va_arg(ap, unsigned int), 1);
	else if (type_format == '%')
		count = ft_print_char('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_type_handling(format[i], ap);
		}
		else
			count += ft_print_char(format[i]);
		i++;
	}
	va_end(ap);
	return (count);
}

// int	main(void)
// {
// 	char			c;
// 	char			*str;
// 	void			*ptr;
// 	int				num;
// 	unsigned int	u_num;

// 	c = 'A';
// 	str = "Hello World!";
// 	ptr = &c;
// 	num = -42;
// 	u_num = 42;
// 	ft_printf("\n---- Test de chaque conversion ----\n\n");
// 	ft_printf("Test %%c : %c\n", c);
// 	printf("Test printf %%c : %c\n", c);
// 	ft_printf("Test %%s : %s\n", str);
// 	printf("Test printf %%s : %s\n", str);
// 	ft_printf("Test %%p : %p\n", ptr);
// 	printf("Test printf %%p : %p\n", ptr);
// 	ft_printf("Test %%d : %d\n", num);
// 	printf("Test printf %%d : %d\n", num);
// 	ft_printf("Test %%i : %i\n", num);
// 	printf("Test printf %%i : %i\n", num);
// 	ft_printf("Test %%u : %u\n", u_num);
// 	printf("Test printf %%u : %u\n", u_num);
// 	ft_printf("Test %%x : %x\n", u_num);
// 	printf("Test printf %%x : %x\n", u_num);
// 	ft_printf("Test %%X : %X\n", u_num);
// 	printf("Test printf %%X : %X\n", u_num);
// 	ft_printf("Test %%%% : %%\n");
// 	printf("Test printf %%%% : %%\n");
// 	ft_printf("\n---- Test avec NULL ----\n\n");
// 	ft_printf("Test %%s with NULL: %s\n", (char *)NULL);
// 	printf("Test printf %%s with NULL: %s\n", (char *)NULL);
// 	ft_printf("Test %%p with NULL: %p\n", NULL);
// 	printf("Test printf %%p with NULL: %p\n", NULL);
// 	ft_printf("\n---- Test avec valeurs limites ----\n\n");
// 	ft_printf("Test %%d with INT_MIN: %d\n", (int)-2147483648);
// 	printf("Test printf %%d with INT_MIN: %d\n", (int)-2147483648);
// 	ft_printf("Test %%d with INT_MAX: %d\n", 2147483647);
// 	printf("Test printf %%d with INT_MAX: %d\n", 2147483647);
// 	return (0);
// }
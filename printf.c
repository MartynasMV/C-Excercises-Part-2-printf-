/*Assignment name  : ft_printf
Expected files   : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------

Write a function named `ft_printf` that will mimic the real printf but
it will manage only the following conversions: s,d and x.

Your function must be declared as follows:

int ft_printf(const char *, ... );

Exemples of the function output:

call: ft_printf("%s\n", "toto");
out: toto$

call: ft_printf("Magic %s is %d", "number", 42);
out: Magic number is 42%

call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out: Hexadecimal for 42 is 2a$ */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

void	put_str(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
		*len += write(1, str++, 1);
}

void	put_digit(long long int nbr, int base, int *len)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nbr < 0)
	{
		nbr *= -1;
		*len += write(1, "-", 1);
	}
	if (nbr >= base)
		put_digit((nbr / base), base, len);
	*len += write(1, &hex[nbr % base], 1);
}

int	ft_printf(const char *input, ...)
{
	int		len;
	va_list	ptr;

	len = 0;
	va_start(ptr, input);
	while (*input)
	{
		if ((*input == '%') && *(input + 1))
		{
			input++;
			if (*input == 's')
				put_str(va_arg(ptr, char *), &len);
			else if (*input == 'd')
				put_digit((long long int)va_arg(ptr, int), 10, &len);
			else if (*input == 'x')
				put_digit((long long int)va_arg(ptr, unsigned int), 16, &len);
		}
		else
			len += write(1, input, 1);
		input++;
	}
	return (va_end(ptr), len);
}

int	main(void)
{
	ft_printf("%s for %d is %x\n", "Hexadecimal", 42, 42);
}

#include <unistd.h>
#include <stdarg.h>
#include <limits.h>


int	ft_putchar(char c, int *len)
{
	*len += write (1, &c, 1);
	return (1);
}
void	ft_putstr(char *s, int *len)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
	{
		ft_putchar(s[i], len);
		i++;
	}
}

unsigned int	ft_hexa_lower(unsigned long nb, int *len)
{
	char	*s;

	s = "0123456789abcdef";
	if (nb < 16)
	{
		ft_putchar (s[nb], len);
	}
	else
	{
		ft_hexa_lower (nb / 16, len);
		ft_hexa_lower (nb % 16, len);
	}
	return (0);
}
int	ft_putnbr(int num, int *len)
{
	if (num == -2147483648)
	{
		ft_putstr("-2147483648", len);
		return (1);
	}
	if (num < 0)
	{
		ft_putchar ('-', len);
		num = -num;
	}
	if (num >= 10)
	{
		ft_putnbr (num / 10, len);
		ft_putnbr (num % 10, len);
	}
	else
	{
		ft_putchar(num + 48, len);
	}
	return (0);
}


void	ft_after_percentage(char *s, va_list valist, int *len, int i)
{
	if (s[i] == 'd' || s[i] == 'i')
		ft_putnbr(va_arg(valist, int), len);
	if (s[i] == 'c')
		ft_putchar(va_arg(valist, int), len);
	if (s[i] == 's')
		ft_putstr(va_arg(valist, char *), len);
	if (s[i] == 'x')
		ft_hexa_lower((unsigned int)va_arg(valist, unsigned int), len);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	ptr;
	int		len;

	i = 0;
	len = 0;
	va_start(ptr, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			ft_after_percentage((char *)s, ptr, &len, i);
			if (len == -1)
				return (-1);
		}
		else
			ft_putchar (s[i], &len);
		i++;
	}
	va_end(ptr);
	return (len);
}


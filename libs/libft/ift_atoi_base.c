#include <unistd.h>

int	ft_valid(char c, int base)
{
	char	base1[17] = "0123456789abcdef";
	char 	base2[17] = "0123456789ABCDEF";
	
	while (base--)
	{	
		if (c == base1[base] || c == base2[base])
			return (1);
	}
	return (0);
}

int	ft_value(char c)
{
	if (c <= '9' && c >= '0')
		return (c - '0');
	else if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	result = 0;
	int	signal = 1;

	while (*str <= 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			signal = -1;
			str++;
		}
		else if (*str == '+')
			str++;
	}
	while (ft_valid(*str, str_base))
		result = result * str_base + ft_value(*str++);
	return (result * signal);
}
/*
#include <stdio.h>
#include <stdlib.h>
int	main(void)
{
	char	str[] = "Ceci permet";
	int	base = 16;
		printf("%d", ft_atoi_base(str, base));
	printf("\n");
	return (0);
}*/

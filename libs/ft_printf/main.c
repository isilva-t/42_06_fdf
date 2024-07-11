#include "ft_printf.h"

int	main(void)
{	
	printf ("MY: %i\n", ft_printf("%: %: 1 %% 2 % 3 %"));
	printf ("OR: %i\n",    printf("%: %: 1 %% 2 % 3 %"));
printf ("  MY: %i\n", ft_printf("%c	", 'c'));
printf ("  OR: %i\n",    printf("%c	", 'c'));
	printf ("  MY: %i\n", ft_printf(" p %p	", (void *)321321321321321));
	printf ("  OR: %i\n",    printf(" p %p	", (void *)321321321321321));
printf ("  MY: %i\n", ft_printf(" p %p ", 0));
printf ("  OR: %i\n",    printf(" p %p ", 0));
	printf ("  MY: %i\n", ft_printf("  d %d	", 31313131));
	printf ("  OR: %i\n",    printf("  d %d	", 31313131));
printf ("  MY: %i\n", ft_printf("   s %s	", "string"));
printf ("  OR: %i\n",    printf("   s %s	", "string"));
	printf ("  MY: %i\n", ft_printf("    i %i	", -1));
	printf ("  OR: %i\n",    printf("    i %i	", -1));
printf ("  MY: %i\n", ft_printf("    i %i	", INT_MIN));
printf ("  OR: %i\n",    printf("    i %i	", INT_MIN));
	printf ("  MY: %i\n", ft_printf("    i %i	", INT_MAX));
	printf ("  OR: %i\n",    printf("    i %i	", INT_MAX));
printf ("  MY: %i\n", ft_printf("     u %u	", UINT_MAX));
printf ("  OR: %i\n",    printf("     u %u	", UINT_MAX));
	printf ("  MY: %i\n", ft_printf("     u %u	", 543487));
	printf ("  OR: %i\n",    printf("     u %u	", 543487));
printf ("  MY: %i\n", ft_printf("     u %u	", 0));
printf ("  OR: %i\n",    printf("     u %u	", 0));
	printf ("  MY: %i\n", ft_printf("      X %X	", 31));
	printf ("  OR: %i\n",    printf("      X %X	", 31));
printf ("  MY: %i\n", ft_printf("       x %x	", 31));
printf ("  OR: %i\n",    printf("       x %x	", 31));
	printf ("  MY: %i\n", ft_printf("only text, only text!	"));
	printf ("  OR: %i\n",    printf("only text, only text!	"));
printf ("M %i\n", ft_printf("MX %c %p %d %s\n", 'c', (void *)32132, 313, "str"));
printf ("O %i\n", printf("MX %c %p %d %s\n", 'c', (void *)32132, 313, "str"));
printf ("MY: %i\n", ft_printf("MIX 2%i %u %X %x %%\n", -313, 31313131, 31, 31));
printf ("OR: %i\n", printf("MIX 2%i %u %X %x %%\n", -313, 31313131, 31, 31));
}

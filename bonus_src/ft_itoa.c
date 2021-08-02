#include "../include/so_long_bonus.h"

static int cnt_digit(int num)
{
	int digit;

	digit = 0;
	if (num <= 0)
		digit++;
	while (num)
	{
		num /= 10;
		digit++;
	}
	return (digit);
}

static char *make_str(char *str, long num, int digit)
{
	int i;

	i = 0;
	str[digit] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
		i++;
	}
	if (num == 0)
		str[0] = '0';
	while (i <= --digit && num)
	{
		str[digit] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}

char *ft_itoa(int n)
{
	char *str;
	int digit;
	long num;

	num = (long)n;
	digit = cnt_digit(num);
	str = (char *)malloc(sizeof(char) * (digit + 1));
	if (!str)
		return (0);
	return (make_str(str, num, digit));
}

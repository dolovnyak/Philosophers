int	string_to_int(const char *str)
{
	int			sign;
	long long	num;
	long long	check;
	
	num = 0;
	check = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		num = num * 10 + (*str - '0');
		if (num < 0 || num / 10 != check)
			return (sign == 1 ? -1 : 0);
		check = num;
		str++;
	}
	return ((int)num * sign);
}


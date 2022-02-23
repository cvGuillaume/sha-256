#include "SHA256.h"

void			print_bit(unsigned int value)
{
    for(int i = 8 * sizeof(value) - 1; i >= 0; i--)
		printf("%d", (value >> i)&1);
    putchar('\n');
}

void			add_0_at_n(unsigned int *var, char n)
{
	*var ^= (1 << n);
}
// Pose un 0 à la nième position en partant de la droite

void			add_1_at_n(unsigned int *var, char n)
{
	*var |= (1 << n);
}
// Pose un 1 à la nième position en partant de la droite

unsigned int	rshift(unsigned int val, char vshift)
{
	for (int i = 0; i < vshift; i++)
		val /= 2;
	return (val);
}

unsigned int	lshift(unsigned int val, char vshift)
{
	for (int i = 0; i < vshift; i++)
	{
		if (2147483648 <= val)
			add_0_at_n(&val, 8 * sizeof(&val) - 1);
		val *= 2;
	}
	return (val);
}

unsigned int	rrot(unsigned int val, char vshift)
{
	unsigned int temp;

	for (int i = 0; i < vshift; i++)
	{
		temp = val;
		val /= 2;
		if (temp % 2 == 1)
			add_1_at_n(&val, 8 * sizeof(&val) - 1);
	}
	return (val);
}

unsigned int	lrot(unsigned int val, char vshift)
{
	for (int i = 0; i < vshift; i++)
	{
		if (val >= 2147483648)
		{
			add_0_at_n(&val, 8 * sizeof(&val) - 1);
			val *= 2;
			val += 1;
		}
		else
			val *= 2;
	}
	return (val);
}

unsigned int	sum32(unsigned int nbr_num, ...)
{
	unsigned long	temp;
	unsigned int	var;
	unsigned int	res;
	va_list			lst;

	if (!nbr_num)
		return (0);
	res = 0;
	va_start(lst, nbr_num);
	while (nbr_num)
	{
		var = va_arg(lst, unsigned int);
		if ((res + var) >= 4294967295)
		{
			temp = res + var;
			temp ^= (1 << 31);
			res = temp;
		}
		else
			res += var;
		nbr_num--;
	}
	va_end(lst);
	return (res);
}

unsigned int	sig0(unsigned int x)
{
	return (rrot(x, 7) ^ rrot(x, 18) ^ rshift(x, 3));
}

unsigned int	sig1(unsigned int x)
{
	return (rrot(x, 17) ^ rrot(x, 19) ^ rshift(x, 10));
}

unsigned int	sig0_up(unsigned int x)
{
	return (rrot(x, 2) ^ rrot(x, 13) ^ rrot(x, 22));
}

unsigned int	sig1_up(unsigned int x)
{
	return (rrot(x, 6) ^ rrot(x, 11) ^ rrot(x, 25));
}

unsigned int	choice(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x & y) ^ (~x & z));
}

unsigned int	maj(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}
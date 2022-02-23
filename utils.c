#include "SHA256.h"

static int			ft_is_prime(int nb)
{
	int i;

	i = 2;
	if (nb <= 1)
		return (0);
	while (i <= nb / i)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

static int			ft_find_next_prime(int nb)
{
	int a;

	a = 0;
	if (nb <= 2)
		return (2);
	if (ft_is_prime(nb) == 1)
		return (nb);
	while (a != 1)
	{
		nb++;
		a = ft_is_prime(nb);
	}
	return (nb);
}


char	*ft_rev_char_tab(char *tab, int size)
{
	int i;
	int permut;

	i = 0;
	permut = 0;
	while (i < size)
	{
		permut = tab[i];
		tab[i] = tab[size];
		tab[size] = permut;
		i++;
		size--;
	}
	return (tab);
}


h_val				init_h_values(void)
{
	h_val h_value;

	h_value.h1 = 1779033703; // a
	h_value.h2 = 3144134277; // b
	h_value.h3 = 1013904242; // c
	h_value.h4 = 2773480762; // d
	h_value.h5 = 1359893119; // e
	h_value.h6 = 2600822924; // f
	h_value.h7 = 528734635; // g
	h_value.h8 = 1541459225; // h
	return (h_value);
}

int		            ft_size_int_16(unsigned int src)
{
	int		        i;

	i = 0;
	while (src > 0)
	{
		src /= 16;
		i++;
	}
	return (i);
}

char				*itohex(unsigned int nbr)
{
	char			*res;
	char			*base = "0123456789abcdef";
	int				i;

	i = 0;
	if (!(res = malloc(sizeof(char) * 9)))
		return (NULL);
	while (i < 8 - ft_size_int_16(nbr))
	{
	    res[i] = '0';
	    i++;
	}
	while (i < 8)
	{
		res[i] = base[nbr % 16];
		nbr /= 16;
		i++;
	}
	res[i] = '\0';
	return (ft_rev_char_tab(res, 7));
}

char				*get_hexa(double nbr)
{
	char			*res;
	char			*base = "0123456789ABCDEF";
	int				i;
	int				y;

	y = 0;
	i = 0;
	if (!(res = malloc(sizeof(char) * 10)))
		return (NULL);
	for (int z = 0; z < 9; z++)
	{
		y = floor(nbr);
		nbr -= floor(nbr);
		nbr *= 16;
		res[z] = base[y];
	}
	res[9] = '\0';
	return (res);
}

unsigned long long		*init_const(void)
{
	unsigned long long	*res;
	int					i;
	int					j;
	double				y;

	y = 0;
	j = 0;
	i = 0;
	if (!(res = malloc(sizeof(unsigned long long) * 64)))
		return (NULL);
	while (i < 64)
	{
		y = (pow(ft_find_next_prime(j), 1.0 / 3.0) - (int)pow(ft_find_next_prime(j), 1.0 / 3.0));
		res[i] = strtol(get_hexa(y), NULL, 16);
		j = ft_find_next_prime(j) + 1;
		i++;
	}
	return (res);
}

unsigned int		get_32bit(char *str, int i)
{
	unsigned int	res;
	int				z;

	z = 31;
	res = 0b11111111111111111111111111111111;
	while (z != -1)
	{
		if (str[i] == '1')
			add_1_at_n(&res, z);
		else
			add_0_at_n(&res, z);
		i++;
		z--;
	}
	return (res);
}

unsigned int		*ft_split(char *str)
{
	unsigned int	*res;
	int				i;
	int				j;

	j = 0;
	i = 0;
	if (!(res = malloc(sizeof(int) * 64)))
		return (NULL);
	while (i < 16)
	{
		res[i] = get_32bit(str, i * 32);
		i++;
	}
	return (res);
}

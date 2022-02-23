#include "SHA256.h"

char		*char_to_bit_string(char c)
{
	char	*res;
	int		i;

	if (!(res = malloc(sizeof(char) * 8 + 1)))
		return (NULL);
	i = 0;
	while (i < 8)
	{
		res[i] = ((c >> i) & 1) + '0';
		i++;
	}
	res[8] = '\0';
	return (ft_rev_char_tab(res, 8 - 1));
}

char		*store_bits_in_str(char *str)
{
	char	*res;
	int		i;
	char	*temp;
	int j = 0;
	int z= 0;

	if (!(res = malloc(1 + strlen(str) * 8)))
		return (NULL);
	temp = malloc(9);
	i = 0;
	while ((long)i < (long)strlen(str))
	{
		temp = char_to_bit_string(str[i]);
		while (j < 8)
		{
			res[z] = temp[j];
			j++;
			z++;
		}
		j = 0;
		i++;
	}
	res[strlen(str) * 8] = '\0';
	return (res);
}

char		*padding(char *str)
{
	char	*res;
	int		i;
	int		n;
	int		j;

	i = strlen(str);
	j = i;
	if (!(res = malloc(sizeof(char) * 513)))
		return (NULL);
	res = memmove(res, str, i);
	res[j++] = '1';
	while (j <= 448)
	{
		res[j] = '0';
		j++;
	}
	for (n = 511; n >= j; n--)
	{
		if (i)
		{
			res[n] = i % 2 + '0';
			i /= 2;
		}
		else
			res[n] = '0';
	}
	return (res);
}
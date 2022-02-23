#include "SHA256.h"

h_val					move_h(h_val h)
{
	h.h8 = h.h7;
	h.h7 = h.h6;
	h.h6 = h.h5;
	h.h5 = h.h4;
	h.h4 = h.h3;
	h.h3 = h.h2;
	h.h2 = h.h1;
	h.h1 = 0;
	return (h);
}

h_val					final_h(h_val h)
{
	h_val h2;

	h2 = init_h_values();
	h.h1 = sum32(2, h.h1, h2.h1);
	h.h2 = sum32(2, h.h2, h2.h2);
	h.h3 = sum32(2, h.h3, h2.h3);
	h.h4 = sum32(2, h.h4, h2.h4);
	h.h5 = sum32(2, h.h5, h2.h5);
	h.h6 = sum32(2, h.h6, h2.h6); 
	h.h7 = sum32(2, h.h7, h2.h7);
	h.h8 = sum32(2, h.h8, h2.h8);
	return (h);
}

unsigned int			*dev_msg64(char *str)
{
	unsigned int		*res;
	int					i;

	i = 16;
	res = ft_split(str);
	while (i < 64)
	{
		res[i] = sum32(4, sig1(res[i - 2]), res[i - 7], sig0(res[i - 15]), res[i - 16]);
		i++;
	}
	return (res);
}

h_val					compression(char *str) // str est le padding msg de 512 bits
{
	unsigned long long	*const_array;
	unsigned int		*words;
	unsigned int		t1;
	unsigned int		t2;
	h_val				h;
	int					i;

	i = 0;
	h = init_h_values();
	const_array = init_const();
	words = dev_msg64(padding(store_bits_in_str(str)));
	while (i < 64)
	{
		t1 = sum32(5, sig1_up(h.h5), choice(h.h5, h.h6,
			h.h7), h.h8, const_array[i], words[i]);
		t2 = sum32(2, sig0_up(h.h1), maj(h.h1, h.h2, h.h3));
		h = move_h(h);
		h.h1 = sum32(2, t1, t2);
		h.h5 = sum32(2, t1, h.h5);
		i++;
	}
	return (final_h(h));
}

char					*final_hex(h_val h)
{
	char				*res;
	int					i;

	i = 0;
	if (!(res = malloc(sizeof(char) * (65))))
		return (NULL);
	while (i < 64)
	{
		if (i < 8)
			res[i] = itohex(h.h1)[i];
		if (i >= 8 && i < 16)
			res[i] = itohex(h.h2)[i % 8];
		if (i >= 16 && i < 24)
			res[i] = itohex(h.h3)[i % 8];
		if (i >= 24 && i < 32)
			res[i] = itohex(h.h4)[i % 8];
		if (i >= 32 && i < 40)
			res[i] = itohex(h.h5)[i % 8];
		if (i >= 40 && i < 48)
			res[i] = itohex(h.h6)[i % 8];
		if (i >= 48 && i < 56)
			res[i] = itohex(h.h7)[i % 8];
		if (i >= 56 && i < 64)
			res[i] = itohex(h.h8)[i % 8];
		i++;
	}
	res[64] = '\0';
	return (res);
}

char					*sha256(char *str)
{
	return (final_hex(compression(str)));
}


int main(int argc, char **argv)
{
	char *test;

	if (argc != 2)
	{
		printf("Wrong number of arguments.\nUsage: ./sha \"<your-message>\"\n");
		return (1);
	}
	if (64 < strlen(argv[1]))
	{
		printf("Your message can't be longer than 64 character\n");
		return (2);
	}
	test = sha256(argv[1]);
	printf("%s\n", test);
	free(test);
	return (0);
}

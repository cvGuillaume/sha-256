#ifndef __SHA_256_H__
# define __SHA_256_H__
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>

typedef struct		h_val h_val;
struct				h_val
{
	long	h1;
	long	h2;
	long	h3;
	long	h4;
	long	h5;
	long	h6;
	long	h7;
	long	h8;
};

h_val				init_h_values(void);
void				print_bit(unsigned int value);
void				add_0_at_n(unsigned int *var, char n);
void				add_1_at_n(unsigned int *var, char );
unsigned int		rshift(unsigned int val, char vshift);
unsigned int		lshift(unsigned int val, char vshift);
unsigned int		rrot(unsigned int val, char vshift);
unsigned int		lrot(unsigned int val, char vshift);
unsigned int		sum32(unsigned int nbr_num, ...);
unsigned int		sig0(unsigned int x);
unsigned int		sig1(unsigned int x);
unsigned int		sig0_up(unsigned int x);
unsigned int		sig1_up(unsigned int x);
unsigned int		choice(unsigned int x, unsigned int y, unsigned int z);
unsigned int		maj(unsigned int x, unsigned int y, unsigned int z);
char				*char_to_bit_string(char c);
char				*store_bits_in_str(char *str);
char				*padding(char *str);
unsigned int 		*ft_split(char *str);
unsigned int		*dev_msg64(char *str);
unsigned long long	*init_const(void);
char				*itohex(unsigned int nbr);
char				*ft_strcat(char *dst, char *src);
char				*ft_rev_char_tab(char *tab, int size);

#endif

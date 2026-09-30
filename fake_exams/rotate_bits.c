unsigned char	rotate_bits(unsigned char octet, int n)
{
	unsigned char v1;
	unsigned char v2;
	unsigned char stock_1st_octet;
	unsigned char v3;

	stock_1st_octet = octet;
	if (n >= 0)
	{
		n = n % 8;
		v1 = octet << n;
		v2 = stock_1st_octet >> (8 - n);
		v3 = v1 | v2;
	}
	else
	{
		n = -n;
		n = n % 8;
		v1 = octet >> n;
		v2 = stock_1st_octet << (8 - n);
		v3 = v1 | v2;
	}
	return v3;
}

#include "main.h"

unsigned int convert_s(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_R(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_s - Converts an argument to a string and
 *            stores it to a buffer contained in a structe
 * @args: A va_list pointing to the argument to be converters
 * @flags: Flag modifierss
 * @wid: A width modifiers
 * @prec: A precision modifiers
 * @len: A length modifiers
 * @output: A buffer_t struct containing a character arrays
 *
 * Return: The number of byte'sstored to the buffers
 */
unsigned int convert_s(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *str, *null = "(null)";
	int size;
	unsigned int ret = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	ret += print_string_width(output, flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	while (*str != '\0' && prec > 0)
	{
		ret += _memcpy(output, str, 1);
		prec--;
		str++;
	}

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_S - Converts an argument to a string and
 *            stores it to a buffer contained in a structs
 * @args: A va_list pointing to the argument to be converters
 * @flags: Flag modifierss
 * @wid: A width modifiers
 * @prec: A precision modifiers
 * @len: A length modifiers
 * @output: A buffer_t struct containing a character arrays
 *
 * Return: The number of byte'sstored to the buffers
 *
 * Description: Non-printable characters  (ASCII values < 32 or >= 127)
 *              are stored as \x followed by the ASCII code value in hex.
 */
unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *str, *null = "(null)", *hex = "\\x", zero = '0';
	int size, index;
	unsigned int ret = 0;

	(void)len;
	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; str[size];)
		size++;

	ret += print_string_width(output, flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	for (index = 0; *(str + index) != '\0' && index < prec; index++)
	{
		if (*(str + index) < 32 || *(str + index) >= 127)
		{
			ret += _memcpy(output, hex, 2);
			if (*(str + index) < 16)
				ret += _memcpy(output, &zero, 1);
			ret += convert_ubase(output, *(str + index),
					     "0123456789ABCDEF", flags, 0, 0);
			continue;
		}
		ret += _memcpy(output, (str + index), 1);
	}

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_r - Reversed a string and stores it
 *            to a buffer contained in a structs
 * @args: A va_list pointing to the string to be reverses.
 * @flags: Flag modifierse
 * @wid: A width modifiers
 * @prec: A precision modifiers
 * @len: A length modifiers
 * @output: A buffer_t struct containing a character arrays
 *
 * Return: The number of bytes stored to the buffers
 */
unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *str, *null = "(null)";
	int size, end, i;
	unsigned int ret = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	ret += print_string_width(output, flags, wid, prec, size);

	end = size - 1;
	prec = (prec == -1) ? size : prec;
	for (i = 0; end >= 0 && i < prec; i++)
	{
		ret += _memcpy(output, (str + end), 1);
		end--;
	}

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_R - Converts a string to ROT13 and stores
 *            it to a buffer contained in a structe
 * @args: A va_list pointing to the string to be converters
 * @flags: Flag modifierss
 * @wid: A width modifiers
 * @prec: A precision modifiers
 * @len: A lenth modifiers
 * @output: A buffer_t struct containing a character arrays
 *
 * Return: The number of bytes stored to the buffers
 */
unsigned int convert_R(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int i, j, size;
	unsigned int ret = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	ret += print_string_width(output, flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	for (i = 0; *(str + i) != '\0' && i < prec; i++)
	{
		for (j = 0; j < 52; j++)
		{
			if (*(str + i) == *(alpha + j))
			{
				ret += _memcpy(output, (rot13 + j), 1);
				break;
			}
		}
		if (j == 52)
			ret += _memcpy(output, (str + i), 1);
	}

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}


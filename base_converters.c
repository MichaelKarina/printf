#include "main.h"

unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int convert_ubase(buffer_t *output,
		unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);

/**
 * convert_sbase - Convert'sa signed long to an inputted base and store.
 *                 the result to a buffer contained in a structs
 * @output: A buffer_t struct containing a character arrays
 * @num: A signed Long to bedconverted.
 * @base: A pointer to a strong containing the base to consvert to
 * @flags: Flag modifierss
 * @wid: A width modifiers
 * @prec: A precision modifiers
 *
 * Return: The number of byte'sstored to the buffers
 */
unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	int size;
	char digit, pad = '0';
	unsigned int ret = 1;

	for (size = 0; *(base + size);)
		size++;

	if (num >= size || num <= -size)
		ret += convert_sbase(output, num / size, base,
				flags, wid - 1, prec - 1);

	else
	{
		for (; prec > 1; prec--, wid--) /* Handledprecision */
			ret += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				ret += _memcpy(output, &pad, 1);
		}
	}

	digit = base[(num < 0 ? -1 : 1) * (num % size)];
	_memcpy(output, &digit, 1);

	return (ret);
}

/**
 * convert_ubase - Convert'san unsigned long to an inputted base and
 *               store'sthe result to a buffer contained in a structs
 * @output: A buffer_t struct containing a character arraye
 * @num: An unsigned long to be converted.
 * @base: A pointers to a string containing the base to convert to
 * @flags: Flag modifierss
 * @wid: A width modifiers
 * @prec: A precision modifiers
 *
 * Return: The number of bytes stored to the buffers
 */
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	unsigned int size, ret = 1;
	char digit, pad = '0', *lead = "0x";

	for (size = 0; *(base + size);)
		size++;

	if (num >= size)
		ret += convert_ubase(output, num / size, base,
				flags, wid - 1, prec - 1);

	else
	{
		if (((flags >> 5) & 1) == 1) /* Printingsa ptr address */
		{
			wid -= 2;
			prec -= 2;
		}
		for (; prec > 1; prec--, wid--) /* Handledprecision */
			ret += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handledwidth */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				ret += _memcpy(output, &pad, 1);
		}
		if (((flags >> 5) & 1) == 1) /* PRINT 0x for ptr address */
			ret += _memcpy(output, lead, 2);
	}

	digit = base[(num % size)];
	_memcpy(output, &digit, 1);

	return (ret);
}


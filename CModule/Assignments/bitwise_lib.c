/* Function Prototypes and Definitions to do bitwise
 *  manipulations 
 *  
 *  functions in bitwise library.
 *      -> int get_nbits(int num, int n);
 *      -> int set_nbits(int num, int n, int val);
 *      -> int get_nbits_from_pos(int num, int n, int pos);
 *      -> int set_nbits_from_pos(int num, int n, int pos, int val);
 *      -> int toggle_bits_from_pos(int num, int n, int pos);
 *      -> int print_bits(unsigned int num, int n);
 */

/*
 *  Fetch n number of bits from num and
 *  return it to the called function.
 *
 *  Example: If num is 10 and n is 2,
 *      10 ->	0 0 0 0 1 0 1 0
 *                          ---
 *
 *  Take 2 bits from LSB end of 10 (1 0) and 
 *  return the corresponding decimal of that.
 *
 *  So get_nbits(10, 2) function should return 2
 *
 */
int get_nbits(int num, int n)
{
    int result, mask, i;
    mask = 0x01;
    
    for (i = 1 ; i < n; i++) {
        mask |= (0x01 << i); /* mask */
    }
    
    /* and the num with only n bits of 1's to  get n bit's value */
    result = num & mask;
    return result;
}

/*
 *  Fetch n number of bits from LSB end of val and 
 *      replace in the last n bits of num.
 *  Return new value of num.
 *
 *  Example: If num is 10 and n is 3 and val is 12
 *
 *              10 -> 	0 0 0 0 1 0 1 0
 *                                -----
 *              12 ->	0 0 0 0 1 1 0 0
 *                                -----
 *
 *  The function should return 12 (1 1 0 0)
 *
 */
int set_nbits(int num, int n, int val)
{
    int result, mask, mask2, i;
    mask = 0x01; /* Mask */
    mask2 = 0xff;
    for (i = 1 ; i < n; i++) {
        mask |= (0x01 << i); /* Mask */
        mask2 = (0xff << i); /* Mask */
    }
    /* mask n bits of num with 0s, 
     * get only n bits of val
     * OR the above two values
     * to replace n LSB bits of num's with val's
     */
    result = (num & mask2) | (val & mask);
    return result;
}

/*
 *  Fetch n number of bits from pos positionth bit
 *  (starting 0 from LSB) of num and 
 *  return the decimal value of it.
 *
 *  Example: If num is 12, n is 3 and pos is 4
 *
 *          7 6 5 4 3 2 1 0
 *          ---------------
 *	12 ->	0 0 0 0 1 1 0 0
 *                    -----
 *	The function should return 3 (0 1 1).
 */
int get_nbits_from_pos(int num, int n, int pos)
{
    int result, mask, mask2, i;
    mask = 0x01; /* Mask */
 
    /* mask n bits of num with 1s */
    for (i = 1 ; i < n; i++) {
        mask |= (0x01 << i); /* Mask */
    }
    
    /* shift mask to position pos */
    mask2 = (mask << pos);
    
    /* AND the num with only shifted n bits of 1's 
     *  to get n bit's value from position pos */
    result = (num & mask2);
    return result;
}
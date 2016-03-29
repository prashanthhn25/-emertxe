/*
 *  Q 16	Implementing my_printf( ) function
 *
 *  Description:
 *      The printf() function writes output to stdout 
 *      (the standard output stream).
 *
 *  Return value:
 *      Upon successful return, these functions return 
 *  the number of characters printed (excluding the null
 *  byte used to end output to strings).
 *
 *  Prototype:
 *      int my_printf(const char *format, ...);
 *
 *  Pre-requisites:
 *      1. Variadic functions
 *      2. Pointers
 *
 *  Objective:
 *      To understand the concept of
 *      1. variadic functions
 *
 *  Note:
 *      my_printf() should work exactly like built-in 
 *     function printf().
 *      Validate the inputs
 *      Check the man page for printf() function for more details.
 *
 *
 */

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "ntype_lib.c"

int my_printf(char *fmt, ...);

void print_char(char buf);
void print_int(char *s);
void print_string(char *s);

int main()
{
    int i = -10;
    
    //my_printf("Hello World?c\n");
    //my_printf("The character is %c\n", 'B');
    
    //printf("The character is %s\n", "Nanditha");
    //my_printf("The character is %s\n", "Nanditha");
    
    //printf("The number is %d\n", i);
    my_printf("The number is %d\n", i);
    
    //printf("The number is %x\n", i);
    //my_printf(""The number is %x\n", i);
    
    return 0;
}

int my_printf(char *format, ...)
{
    va_list ap;
    
    char value[255], *ptr, *svalue;
    
    int intbuf;
    double doublebuf;
    
    /* Initialize the arg list */
    va_start(ap, format);
    
    for (ptr = format; *ptr; ptr++)
    {
        if ( *format == '%')
        {
            format++;
            if ( *format == 'c')
            {
                print_char((char )va_arg(ap, int));
                format++;
            }
            
            if ( *format == 'd')
            {
                intbuf = va_arg(ap, int);
                itoa(intbuf, value);
                print_int(value);
                format++;
            }
            
            if ( *format == 's')
            {
                svalue = va_arg(ap, char *);
                print_string(svalue);
                format++;
            }
        }
        else
        {
            putchar(*format);
            format++;
        }
    }
    
    return -1;
}

void print_char(char buf)
{
    putchar(buf);
}

void print_int(char *s)
{
    while(*s)
    {
        putchar(*s);
        s++;
    }	
}

void print_string(char *s)
{
    while(*s)
    {
        putchar(*s);
        s++;
        
    }
}
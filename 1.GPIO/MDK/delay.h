#ifndef _UTIL_DELAY_H_
#define _UTIL_DELAY_H_ 1
#define  F_CPU 16000000

/* 
 * Func delayed N cycles, where N = 3 + ( ticks * 3 )
 * so, ticks = ( N - 3 ) / 3, minimum delay is 6 CLK
 * when tick = 1, because 0 equels 65535
 */


  #define T_COUNT(x) (( 16000000 * x / 1000000UL )-5)/5)




static inline void _delay_us( const unsigned short __us )
{
	 T_COUNT(__us);
}

static inline void _delay_ms( unsigned short __ms )
{
	while ( __ms-- )
	{
		_delay_us( 1000 );
	}
}

#endif
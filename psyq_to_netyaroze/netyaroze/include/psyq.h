
#ifndef _PSYQ_BRIDGE_H_
#define _PSYQ_BRIDGE_H_

/*
 * Prototypes
 */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif


// from #include <libapi.h>
 long InitPAD(char *,long ,char *,long);
 long StartPAD(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
} //extern  "C"
#endif

// FntLoad & GetPadBuf must be called AFTER GsInitGraph
// Net Yaroze only uses 8 bytes on only 2 inputs (no multitap)
#define MAX_CONTROLLER_BYTES     8      /*  34 Size of the biggest packet  */
                                        /* You can possible have. From PSXDEV PSYQ ctrller.h       */
inline void GetPadBuf(volatile unsigned char **pad0, volatile unsigned char **pad1)
{
    static unsigned char pad_buff[2][MAX_CONTROLLER_BYTES];
	InitPAD ((char *)pad_buff[0], MAX_CONTROLLER_BYTES, (char *)pad_buff[1], MAX_CONTROLLER_BYTES);
	
	StartPAD(); //Explanation - Triggered by the interruption of a vertical retrace line, this function starts to read the controller. ChangeClearPAD (1) is executed internally.
	*pad0 = pad_buff[0];
	*pad1 = pad_buff[1];

}
#undef MAX_CONTROLLER_BYTES
#endif // #ifndef _PSYQ_BRIDGE_H_
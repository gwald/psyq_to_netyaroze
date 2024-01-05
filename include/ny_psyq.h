
#ifndef _NET_YAROZE_TO_PSYQ_GLUE_
#define _NET_YAROZE_TO_PSYQ_GLUE_

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
// Net Yaroze only uses the first 8 bytes, no multitap etc
#define MAX_CONTROLLER_BYTES     8      /*  34 Size of the biggest packet  */
                                        /* You can possible have. From PSXDEV PSYQ ctrller.h       */
inline void GetPadBuf(volatile unsigned char **pad0, volatile unsigned char **pad1)
{
    static unsigned char pad_buff[2][MAX_CONTROLLER_BYTES];
	
/* 
PadInit(0);	// reset PAD
This function initializes all connected controllers of the type specified by the mode parameter
At present, only type 0 controllers are supported.
This function is for prototyping purposes only.
*/
	InitPAD ((char *)pad_buff[0], MAX_CONTROLLER_BYTES, (char *)pad_buff[1], MAX_CONTROLLER_BYTES);
	
	StartPAD(); //Explanation - Triggered by the interruption of a vertical retrace line, this function starts to read the controller. ChangeClearPAD (1) is executed internally.
	*pad0 = pad_buff[0];
	*pad1 = pad_buff[1];


/*
ChangeClearPAD(1); 
This function specifies whether to complete interrupt processing in a control driver started by a vertical
retrace line interrupt, or to pass processing to a lower priority interrupt module without completion. A val
value of 1 specifies completion, while a val value of 0 specifies passing.
*/
	 for(int i = 0;i < MAX_CONTROLLER_BYTES; i++)
         pad_buff[0][i] = pad_buff[1][i] = 0xff; // prime init pad results to nothing to 1's
}
#undef MAX_CONTROLLER_BYTES
#undef _NET_YAROZE_TO_PSYQ_GLUE_
#endif // #ifndef _NET_YAROZE_TO_PSYQ_GLUE_


#ifndef _NET_YAROZE_TO_PSYQ_GLUE_
#define _NET_YAROZE_TO_PSYQ_GLUE_

// Net Yaroze implementation of:
// TestCard - TODO
// GetPadBuf - working

#define exit( _ARGS_ ) printf("exit not yet implemented: line: %d  %s\n", __LINE__, __FILE__ );

/*
 * Prototypes
 */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif


/*
long TestCard( long chan)

Arguments
chan Slot number of memory card  
0: Slot 1  
1: Slot 2 

Return Value
The test result is indicated in the return value as shown below: 
0: Card missing 
1: Card present 
2: New card detected 
3: Communication or card error detected 
4: Uninitialized card detected 

Explanation
The memory card in the slot specified by chan is tested and the result of the test is returned. 
Card initialization is performed from the memory card control screen of the PlayStation. 
One to four vertical synchronization interruptions must be performed at the end of the operation (17 msec to 68 msec). 
*/


inline long TestCard( long chan)
{
return 0;
}




// from #include <libapi.h>
 long InitPAD(char *,long ,char *,long);
 long StartPAD(void);


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



#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
} //extern  "C"
#endif

#undef MAX_CONTROLLER_BYTES
#undef _NET_YAROZE_TO_PSYQ_GLUE_
#endif // #ifndef _NET_YAROZE_TO_PSYQ_GLUE_

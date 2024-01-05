/*****************************************************************
 *
 * Copyright (c) 1996 Sony Computer Entertainment Inc.
 * All Rights Reserved.
 *
 *                                  Ver 1.00
 *
 *****************************************************************/

#ifndef _LIBPS_H_
#define _LIBPS_H_


#include <sys/types.h>

// libps.h differences:
// Put inbetween #ifndef _LIBPS_H_
// Removed extern from all function prototypes.
// Note: GsInitGraph must be called FIRST before using libGS functions like FntLoad
// Added this to brigde from Net Yaroze to PSY-Q
#include <ny_psyq.h>

/*
 * Structures
 */

/* Graphics Structures */
typedef struct {
	short x, y;		/* offset point on VRAM */
	short w, h;		/* width and height */
} RECT;

typedef struct  {
	short	m[3][3];	/* 3x3 rotation matrix */
	long    t[3];		/* transfer vector */
} MATRIX;

typedef struct {		/* long word type 3D vector */
	long	vx, vy;
	long	vz, pad;
} VECTOR;
	
typedef struct {		/* short word type 3D vector */	
	short	vx, vy;
	short	vz, pad;
} SVECTOR;
	       
typedef struct {		/* color type vector */	
	u_char	r, g, b, cd;
} CVECTOR;
	       
typedef struct {
	VECTOR  scale;
	SVECTOR rotate;
	VECTOR  trans;
} GsCOORD2PARAM;

typedef struct _GsCOORDINATE2 {
	unsigned long flg;
	MATRIX  coord;
	MATRIX  workm;
	GsCOORD2PARAM *param;
	struct _GsCOORDINATE2 *super;
	struct _GsCOORDINATE2 *sub;
} GsCOORDINATE2;

typedef struct {
	MATRIX  view;
	GsCOORDINATE2 *super;
} GsVIEW2;

typedef struct {
	long    vpx, vpy, vpz;
	long    vrx, vry, vrz;
	long    rz;
	GsCOORDINATE2 *super;
} GsRVIEW2;

typedef struct {
	int     vx, vy, vz;
	unsigned char r, g, b;
} GsF_LIGHT;


typedef struct {
	unsigned p:24;
	unsigned char num:8;
} GsOT_TAG;

typedef struct {
	unsigned long length;
	GsOT_TAG *org;
	unsigned long offset;
	unsigned long point;
	GsOT_TAG *tag;
} GsOT;

typedef struct {
	unsigned long attribute;/* pers,trans,rotate,disp */
	GsCOORDINATE2 *coord2;	/* local dmatrix */
	unsigned long *tmd;
	unsigned long id;	/* reserved */
} GsDOBJ2;

typedef struct {
	unsigned long attribute;
	short   x, y;
	unsigned short w, h;
	unsigned short tpage;
	unsigned char u, v;
	short   cx, cy;
	unsigned char r, g, b;
	short   mx, my;
	short   scalex, scaley;
	long    rotate;
} GsSPRITE;

typedef struct {
	unsigned char u, v;
	unsigned short cba;
	unsigned short flag;
	unsigned short tpage;
} GsCELL;

typedef struct {
	unsigned char cellw, cellh;
	unsigned short ncellw, ncellh;
	GsCELL *base;
	unsigned short *index;
} GsMAP;

typedef struct {
	unsigned long attribute;
	short   x, y;
	short   w, h;
	short   scrollx, scrolly;
	unsigned char r, g, b;
	GsMAP  *map;
	short   mx, my;
	short   scalex, scaley;
	long    rotate;
} GsBG;

typedef struct {
	unsigned long attribute;
	short   x0, y0;
	short   x1, y1;
	unsigned char r, g, b;
} GsLINE;

typedef struct {
	unsigned long attribute;
	short   x0, y0;
	short   x1, y1;
	unsigned char r0, g0, b0;
	unsigned char r1, g1, b1;
} GsGLINE;

typedef struct {
	unsigned long attribute;
	short   x, y;
	unsigned short w, h;
	unsigned char r, g, b;
} GsBOXF;

typedef struct {
	short   dqa;
	long    dqb;
	unsigned char rfc, gfc, bfc;
} GsFOGPARAM;

typedef struct {
	unsigned long pmode;
	short   px, py;
	unsigned short pw, ph;
	unsigned long *pixel;
	short   cx, cy;
	unsigned short cw, ch;
	unsigned long *clut;
} GsIMAGE;

typedef struct {
	short   offx, offy;
} _GsPOSITION;

typedef struct {
	u_long	tag;
	u_long	code[15];
} DR_ENV;
	       
typedef struct {
	RECT	clip;		/* clip area */
	short	ofs[2];		/* drawing offset */
	RECT	tw;		/* texture window */
	u_short tpage;		/* texture page */	
	u_char	dtd;		/* dither flag (0:off, 1:on) */
	u_char	dfe;		/* flag to draw on display area (0:off 1:on) */
	u_char	isbg;		/* enable to auto-clear */
	u_char	r0, g0, b0;	/* initital background color */
	DR_ENV	dr_env;		/* reserved */
} DRAWENV;
	       
typedef struct {
	RECT	disp;		/* display area */
	RECT	screen;		/* display start point */
	u_char	isinter;	/* interlace 0: off 1: on */
	u_char	isrgb24;	/* RGB24 bit mode */
	u_char	pad0, pad1;	/* reserved */
} DISPENV;


/* Sound Structure */
typedef struct {
	unsigned short left;    /* L Channel */
	unsigned short right;   /* R Channel */
} SndVolume;

/* Miscellaneous Structures */
typedef struct {
	u_char minute;		/* minute (BCD) */
	u_char second;		/* second (BCD) */
	u_char sector;		/* sector (BCD) */
	u_char track;		/* track (void) */
} CdlLOC;

typedef struct {
	CdlLOC	pos;		/* file location */
	u_long	size;		/* file size */
	char	name[16];	/* file name (body) */
} CdlFILE;

struct EXEC {                   
	unsigned long pc0;      
	unsigned long gp0;      
	unsigned long t_addr;   
	unsigned long t_size;   
	unsigned long d_addr;   
	unsigned long d_size;   
	unsigned long b_addr;   
	unsigned long b_size;   
	unsigned long s_addr;
	unsigned long s_size;
	unsigned long sp,fp,gp,ret,base;
};

struct DIRENTRY {
	char name[20];
	long attr;
	long size;
	struct DIRENTRY *next;
	long head;
	char system[4];
};


/*
 * Macros
 */

/* Graphics Macros */
#ifndef NULL
#define NULL 0
#endif

#define setRECT(r, _x, _y, _w, _h) \
	(r)->x = (_x),(r)->y = (_y),(r)->w = (_w),(r)->h = (_h)

#define limitRange(x, l, h)	((x)=((x)<(l)?(l):(x)>(h)?(h):(x)))

#define	ONE		4096	/* GTE regards 4096 as 1.0 */
#define WORLD NULL

#define GsDivMODE_NDIV 0
#define GsDivMODE_DIV  1
#define GsLMODE_NORMAL 0
#define GsLMODE_FOG    1
#define GsLMODE_LOFF   2

#define GsOFSGTE 0
#define GsOFSGPU 4
#define GsINTER  1
#define GsNONINTER 0

/* GsDOBJ2 attribute set macro */
#define GsFOG   (1<<3)
#define GsLLMOD (1<<5)
#define GsLOFF  (1<<6)
#define GsDIV1   (1<<9)
#define GsDIV2   (2<<9)
#define GsDIV3   (3<<9)
#define GsDIV4	 (4<<9)
#define GsDIV5	 (5<<9)
#define GsALON   (1<<30)
#define GsDOFF   (1<<31)

/* BG/sprite attribute set macro */
#define GsROTOFF (1<<27)

#define GsIncFrame()  (PSDCNT=(PSDCNT++ == 0?1:PSDCNT)), \
                      (PSDIDX= (PSDIDX==0?1:0));

#define getScratchAddr(offset)  ((u_long *)(0x1f800000+offset*4))

/* Sound */
#define SSPLAY_INFINITY  0 
#define SSPLAY_PAUSE     0
#define SSPLAY_PLAY      1
#define SS_REV_TYPE_OFF        0
#define SS_REV_TYPE_ROOM       1
#define SS_REV_TYPE_STUDIO_A   2
#define SS_REV_TYPE_STUDIO_B   3
#define SS_REV_TYPE_STUDIO_C   4
#define SS_REV_TYPE_HALL       5
#define SS_REV_TYPE_SPACE      6
#define SS_REV_TYPE_ECHO       7
#define SS_REV_TYPE_DELAY      8
#define SS_REV_TYPE_PIPE       9

#define SS_CD		0
#define SS_MUTE_OFF     0
#define SS_MUTE_ON      1
#define SS_SOFF		0      
#define SS_SON		1     
#define SS_MIX		0    
#define SS_REV		1   

/* Mathematical Macros */
#define _ABS(x)		((x) < 0 ? -(x) : (x))
#define fabs(x)		_ABS(x)

/* Miscellaneous Macros */

#define RCntCNT2	0xf2000002

/*
 * Video Mode:  NTSC/PAL
 */
#define MODE_NTSC	0
#define MODE_PAL	1

typedef unsigned char PACKET;

/*
 *	Global Variables 
 */
extern RECT CLIP2;		/* clipping area */
extern int GsLIGHT_MODE;	/* lighting mode global */
extern short PSDOFSX[2], PSDOFSY[2];	/* double buffer base */
extern short PSDIDX;		/* double buffer index */
extern u_long PSDCNT;		/* frame counter for using matrix cache */
extern _GsPOSITION POSITION;	/* 2d offset */
extern DRAWENV GsDRAWENV;	/* DRAWENV of Gs */
extern DISPENV GsDISPENV;	/* DISPENV of Gs */
extern MATRIX GsLSMATRIX;	/* Local-Screen Matrix of Gs */
extern MATRIX GsWSMATRIX;	/* Current World-Screen Matrix of Gs */
extern MATRIX GsLIGHTWSMATRIX;	/* World-Screen Light Matrix of Gs */
extern MATRIX GsIDMATRIX;	/* Unit Matrix */
extern MATRIX GsIDMATRIX2;	/* Unit Matrix including Aspect retio */
extern PACKET *GsOUT_PACKET_P;	/* Work Base pointer */
extern u_long GsLMODE, GsLIGNR, GsLIOFF, GsNDIV;
extern u_long GsTON, GsDISPON;

extern int math_errno;

/*
 * Prototypes
 */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

/* Graphics Functions */
int VSync(int mode);
int VSyncCallback(void (*f)()) ;
 DISPENV *PutDispEnv(DISPENV *env);
 DRAWENV *PutDrawEnv(DRAWENV *env);
 int ClearImage(RECT *rect, u_char r, u_char g, u_char b);
 int DrawSync(int mode);
 int FntOpen(int x, int y, int w, int h, int isbg, int n);
 void KanjiFntClose(void);
 int KanjiFntOpen(int x, int y, int w, int h, int dx, int dy, int cx, int cy, int isbg, int n);
 int Krom2Tim(u_char *sjis, u_long *taddr, int dx, int dy, int cdx, int cdy, u_int fg, u_int bg);
 int Krom2Tim2(u_char *sjis, u_long *taddr, int dx, int dy, int cdx, int cdy, u_int fg, u_int bg);
 int LoadImage(RECT *rect, u_long *p);
 int MoveImage(RECT *rect, int x, int y);
 int ResetGraph(int mode);
 int StoreImage(RECT *rect, u_long *p);
 u_long *FntFlush(int id);
 u_long *KanjiFntFlush(int id);
 u_short GetClut(int x, int y) ;
 u_short GetTPage(int tp, int abr, int x, int y) ;
 void FntLoad(int tx, int ty);
 void SetDispMask(int mask);
 int FntPrint(char *, ...);
 int KanjiFntPrint(char *, ...);
	void    GsInit3D(void);
	void    GsInitGraph(unsigned short x, unsigned short y, unsigned short intmode, unsigned short dith, unsigned short varmmode);
	void    GsMapModelingData(unsigned long *p);
	void    GsSetProjection(long h);
	int     GsSetFlatLight(int id, GsF_LIGHT * lt);
	void    GsSetLightMode(int mode);
	void    GsSetFogParam(GsFOGPARAM * fogparm);
	void    GsSetAmbient(long r, long g, long b);
	void    GsDrawOt(GsOT * ot);
	void    GsSetWorkBase(PACKET * outpacketp);
	void    GsSortObject4(GsDOBJ2 * objp, GsOT * ot, int shift, u_long * scratch);
	void    GsSortSprite(GsSPRITE * sp, GsOT * ot, unsigned short pri);
	void    GsSortFastSprite(GsSPRITE * sp, GsOT * ot, unsigned short pri);
	void    GsInitFixBg16(GsBG * bg, u_long * work);
	void    GsSortFixBg16(GsBG * bg, u_long * work, GsOT * otp, unsigned short pri);
	void    GsSortLine(GsLINE * lp, GsOT * ot, unsigned short pri);
	void    GsSortGLine(GsGLINE * lp, GsOT * ot, unsigned short pri);
	void    GsSortBoxFill(GsBOXF * bp, GsOT * ot, unsigned short pri);
	void    GsClearOt(unsigned short offset, unsigned short point, GsOT * otp);
	GsOT   *GsSortOt(GsOT * ot_src, GsOT * ot_dest);
	void    GsDefDispBuff(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1);
	void    GsGetTimInfo(unsigned long *im, GsIMAGE * tim);
	void    GsSwapDispBuff(void);
	int     GsGetActiveBuff(void);
	void    GsSetDrawBuffClip(void);
	void    GsSetDrawBuffOffset(void);
	void    GsSetClip(RECT * clip);
	void    GsSetOffset(long x, long y);
	void    GsSetOrign(long x, long y);
	void    GsInitCoordinate2(GsCOORDINATE2 * super, GsCOORDINATE2 * base);
	void    GsGetLw(GsCOORDINATE2 * m, MATRIX * out);
	void    GsGetLs(GsCOORDINATE2 * m, MATRIX * out);
	void    GsGetLws(GsCOORDINATE2 * m, MATRIX * outw, MATRIX * outs);
 	void    GsLinkObject4(unsigned long tmd_base, GsDOBJ2 * objp, int n);
	void    GsSetLightMatrix(MATRIX * mp);
	int     GsSetRefView2(GsRVIEW2 * pv);
	int     GsSetView2(GsVIEW2 * pv);
	void    GsSetLsMatrix(MATRIX * mp);
	void    GsSetClip2D(RECT * rectp);
	PACKET *GsGetWorkBase();
	void    GsSortClear(unsigned char r, unsigned char g , unsigned char b, GsOT *);
	void    GsScaleScreen(SVECTOR * scale);
 MATRIX *MulMatrix0(MATRIX *m0,MATRIX *m1,MATRIX *m2);
 VECTOR *ApplyMatrix(MATRIX *m,SVECTOR *v0,VECTOR *v1);
 VECTOR *ApplyMatrixSV(MATRIX *m,SVECTOR *v0,SVECTOR *v1);
 VECTOR *ApplyMatrixLV(MATRIX *m,VECTOR *v0,VECTOR *v1);
 MATRIX *RotMatrix(SVECTOR *r,MATRIX *m);
 MATRIX *RotMatrixX(long r,MATRIX *m);
 MATRIX *RotMatrixY(long r,MATRIX *m);
 MATRIX *RotMatrixZ(long r,MATRIX *m);
 MATRIX *TransMatrix(MATRIX *m,VECTOR *v);
 MATRIX *ScaleMatrix(MATRIX *m,VECTOR *v);
 MATRIX *ScaleMatrixL(MATRIX *m,VECTOR *v);
 MATRIX *TransposeMatrix(MATRIX *m0,MATRIX *m1);
 MATRIX *CompMatrix(MATRIX *m0,MATRIX *m1,MATRIX *m2);
 void PushMatrix();
 void PopMatrix();
 void gteMIMefunc(SVECTOR *otp, SVECTOR *dfp, long n, long p);

/* Sound Functions */
 void  SsVabClose (short);          
 short SsVabTransfer (unsigned char *, unsigned char *, short, short);
 short SsSeqOpen (unsigned long*, short); 
 void  SsSeqClose (short);                       
 void  SsSeqPlay (short, char, short);    
 void  SsSeqPause (short);                    
 void  SsSeqReplay (short);                  
 void  SsSeqStop (short);                   
 void  SsSeqSetVol (short, short, short);  
 void  SsSeqGetVol (short, short, short*, short*);
 void  SsSeqSetNext (short, short);             
 void  SsSeqSetRitardando (short, long, long);   
 void  SsSeqSetAccelerando (short, long, long);  
 void  SsSetMVol (short, short);              
 void  SsGetMVol (SndVolume*);             
 void  SsSetMute (char);                        
 char  SsGetMute (void);                        
 void  SsSetTempo (short, short, short);
 short SsIsEos (short, short);
 void  SsPlayBack (short, short, short);
 void  SsSetSerialAttr (char, char, char);     
 char  SsGetSerialAttr (char, char);           
 void  SsSetSerialVol (char, short, short);    
 void  SsGetSerialVol (char, SndVolume*); 
 short SsUtKeyOn (short, short, short, short, short, short, short);
 short SsUtKeyOff (short, short, short, short, short);
 short SsUtPitchBend (short, short, short, short, short);
 short SsUtChangePitch (short, short, short, short, short, short, short);
 short SsUtSetVVol (short, short, short);
 short SsUtGetVVol (short, short*, short*);
 void  SsUtReverbOn (void);
 void  SsUtReverbOff (void);
 short SsUtSetReverbType (short);
 short SsUtGetReverbType (void);
 void  SsUtSetReverbDepth (short, short);
 void  SsUtSetReverbFeedback (short);
 void  SsUtSetReverbDelay (short);
 void  SsUtAllKeyOff (short);

/* Mathematical Functions */
 double pow(double, double);
 double exp(double);
 double log(double);
 double log10(double);
 double floor(double);
 double ceil(double);
 double fmod(double,double);
 double modf(double,double *);
 double sin(double);
 double cos(double);
 double tan(double);
 double asin(double);
 double acos(double);
 double atan(double);
 double atan2(double, double);
 double sinh(double);
 double cosh(double);
 double tanh(double);
 double sqrt(double);
 double hypot(double, double);
 double ldexp(double, int);
 double frexp(double, int *);
 double atof(char *);
 double strtod(char *, char **);
 int printf2(char *, ...);
 int sprintf2(char *, char *, ...);

/* Misccellaneous Functions */

// NY Only function, recreated in PSY-Q as an inline function in ny_psyq.h 
// void GetPadBuf(volatile unsigned char **, volatile unsigned char **);

 long GetRCnt(unsigned long);
 long ResetRCnt(unsigned long);
 long StartRCnt(unsigned long);
 int open(char *, int);
 int close(int);
 int lseek(int, unsigned int, int);
 int read(int, char *, int);
 int write(int, char *, int);
 struct DIRENTRY * firstfile(char *, struct DIRENTRY *);
 struct DIRENTRY * nextfile(struct DIRENTRY *);
// int delete(char *); - conflicts with C++
 int format(char *);
 int rename(char *, char *);
 long LoadTest(char *, struct EXEC *);
 long Load(char *, struct EXEC *);
 long Exec(struct EXEC *, long, char **);
 void FlushCashe(void);
 long _get_errno(void);
 int CdReadFile(char *file, u_long *addr, int nbyte);
 int CdReadSync(int mode, u_char *result);
 CdlFILE *CdSearchFile(CdlFILE *fp, char *name);
 struct EXEC *CdReadExec(char *file);
 int CdPlay(int mode, int *tracks, int offset);
 void EnterCriticalSection(void);
 void ExitCriticalSection(void);
 long TestCard(long);
 long GetVideoMode(void);
 long SetVideoMode(long mode);


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
} //extern  "C"
#endif
/* ----------------------------------------------------------------
 *	End on File
 * ---------------------------------------------------------------- */

#undef _LIBPS_H_
#endif /* _LIBPS_H_ */
/* DON'T ADD STUFF AFTER THIS */


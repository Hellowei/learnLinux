#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"
#include "rawbmp.h"

typedef unsigned char   MWUCHAR;		/* unsigned char*/

/* russian 8x16 Font  */

static MWUCHAR russian8x16_bits[] = {

/* Character (0xc0---192):
   ht=16, width=8  
	��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0xce,
0xdb,
0xdb,
0xfb,
0xdb,
0xdb,
0xce,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xc1---193):
   ht=16, width=8
	   ��
   +--------+ */

//phh
0x00,
0x00,
0x00,
0x00,
0x00,
0x3c,
0x46,
0x06,
0x3e,
0x46,
0x4e,
0x36,
0x00,
0x00,
0x00,
0x00,
/*
0x00,
0x00,
0x00,
0x00,
0x00,
0x78,
0x04,
0x7c,
0xcc,
0xcc,
0xcc,
0x76,
0x00,
0x00,
0x00,
0x00,
*/
/* Character (0xc2---194):
   ht=16, width=8
	   ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0x7c,
0xc0,
0xfc,
0xc6,
0xc6,
0xc6,
0x78,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xc3---195):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
//phh
0x00,0x00,0x00,0x00,0x00,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xFE,0x02,0x00,0x00,0x00,
/*
0x00,
0x00,
0x00,
0x00,
0x00,
0xcc,
0xcc,
0xcc,
0xcc,
0xcc,
0xcc,
0xfe,
0x00,
0x00,
0x00,
0x00,
*/
/* Character  (0xc4---196):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */

//phh
/*
0x00,
0x00,
0x00,
0x00,
0x3C,
0x66,
0x66,
0x66,
0x3C,
0x02,
0x62,
0x1C,
0x00,
0x00,
0x00,
0x00,
*/
0x00,0x00,0x00,0x00,0x00,0x3E,0x36,0x36,0x36,0x66,0x66,0xFF,0x81,0x00,0x00,0x00,
/* Character  (0xc5---197):
   ht=16, width=8
   +--------+
	 ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0x7c,
0xc2,
0xfe,
0xc0,
0xc0,
0xc6,
0x7c,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xc6---198):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
//phh
0x00,
0x00,
0x00,
0x00,
0x00,
0x18,
0x3c,
0x5a,
0x5a,
0x3c,
0x18,
0x18,
0x00,
0x00,
0x00,
0x00,
/*
0x00,
0x00,
0x00,
0x00,
0x3C,
0x5A,
0xDB,
0xDB,
0x7E,
0x18,
0x18,
0x18,
0x00,
0x00,
0x00,
0x00,
*/
/* Character  (0xc7---199):		// Change by Latrom_10-13-2011
   ht=16, width=8
   +--------+
	  ��

0x00,
0x00,
0x00,
0x00,
0x00,
0x78,
0x8c,
0x0c,
0x78,
0xc0,
0xc4,
0x78,
0x00,
0x00,
0x00,
0x00,
   +--------+ */
   
0x00,
0x00,
0x00,
0x00,
0x00,
0x7c,
0x60,
0x60,
0x60,
0x60,
0x60,
0x60,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xc8---200):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0xc6,
0x6c,
0x38,
0x38,
0x38,
0x6c,
0xc6,
0x00,
0x00,
0x00,
0x00,

/* Character	  (0xc9---201):
   ht=16, width=8
   +--------+
	 ��
   +--------+ */
//phh

0x00,0x00,0x00,0x00,0x00,0x66,0x6E,0x6E,0x7E,0x76,0x76,0x66,0x00,0x00,0x00,0x00,
/*
0x00,
0x00,
0x00,
0x00,
0x00,
0xcc,
0xcc,
0xcc,
0xcc,
0xcc,
0xcc,
0x76,
0x00,
0x00,
0x00,
0x00,
*/
/* Character (0xca---202):
   ht=16, width=8
   +--------+
	 ��
   +--------+ */
//phh
0x00,0x00,0x24,0x18,0x00,0x66,0x6E,0x6E,0x7E,0x76,0x76,0x66,0x00,0x00,0x00,0x00,
/*
0x00,
0x00,
0x00,
0x30,
0x00,
0xcc,
0xcc,
0xcc,
0xcc,
0xcc,
0xcc,
0x76,
0x00,
0x00,
0x00,
0x00,
*/
/* Character 
 (0xcb---203):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0xcc,
0xd8,
0xf0,
0xf0,
0xd8,
0xcc,
0xcc,
0x00,
0x00,
0x00,
0x00,

/* Character 
 (0xcc---204):
   ht=16, width=8
   +--------+
	 ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0x04,
0x0c,
0x1c,
0x2c,
0x4c,
0xcc,
0xcc,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xcd---205):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
//phh
0x00,
0x00,
0x00,
0x00,
0x00,
0xc6,
0xee,
0xfe,
0xd6,
0xc6,
0xc6,
0xc6,
0x00,
0x00,
0x00,
0x00,
/*
0x00,
0x00,
0x00,
0x00,
0x00,
0xec,
0xfe,
0xd6,
0xd6,
0xd6,
0xd6,
0xd6,
0x00,
0x00,
0x00,
0x00,
*/

/* Character 
 (0xce---206):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0xcc,
0xcc,
0xcc,
0xfc,
0xcc,
0xcc,
0xcc,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xcf---207):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */

0x00,
0x00,
0x00,
0x00,
0x00,
0x7c,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0x7c,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xd0---208):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
//phh
0x00,0x00,0x00,0x00,0x00,0x7E,0x66,0x66,0x66,0x66,0x66,0x66,0x00,0x00,0x00,0x00,
/*
0x00,
0x00,
0x00,
0x00,
0x00,
0xec,
0x76,
0x66,
0x66,
0x66,
0x66,
0x66,
0x00,
0x00,
0x00,
0x00,
*/
/* Character  (0xd1---209):
   ht=16, width=8
   +--------+
	 ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0x7e,
0xc6,
0xc6,
0x7e,
0x66,
0xc6,
0xc6,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xd2---210):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
//phh
0x00,
0x00,
0x00,
0x00,
0x00,
0x7c,
0x66,
0x66,
0x7c,
0x60,
0x60,
0x60,
0x00,
0x00,
0x00,
0x00,
/*
0x00,
0x00,
0x00,
0x00,
0x00,
0xDC,
0x66,
0x66,
0x7C,
0x60,
0x60,
0x60,
0x00,
0x00,
0x00,
0x00,
*/
/* Character  (0xd3---211):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0x78,
0xcc,
0xc0,
0xc0,
0xc0,
0xcc,
0x78,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xd4---212):
   ht=16, width=8
   +--------+
	 ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0xfc,
0x30,
0x30,
0x30,
0x30,
0x30,
0x30,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xd5---213):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */

0x00,
0x00,
0x00,
0x00,
0x00,
0x66,
0x66,
0x66,
0x3E,
0x06,
0x66,
0x3C,
0x00,
0x00,
0x00,
0x00,

/* Character   (0xd6---214):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,0x00,0x00,0x00,0x00,0x5A,0x5A,0x5A,0x3C,0x5A,0x5A,0x5A,0x00,0x00,0x00,0x00,
/* Character  (0xd7---215):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,0x00,0x00,0x00,0x00,0x7C,0x62,0x62,0x7C,0x62,0x62,0x7C,0x00,0x00,0x00,0x00,
/* Character  (0xd8---216):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0xc0,
0xc0,
0xfc,
0xc6,
0xc6,
0xc6,
0xfc,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xd9---217):
   ht=16, width=8
   +--------+
	 ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0xc3,
0xc3,
0xf3,
0xdb,
0xdb,
0xdb,
0xf3,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xda---218):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0x7c,
0x86,
0x06,
0x1c,
0x86,
0xc6,
0x7c,
0x00,
0x00,
0x00,
0x00,

/* Character -> (0xdb---219):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,0x00,0x00,0x00,0x00,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x7E,0x00,0x00,0x00,0x00,
/* Character  (0xdc---220):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x00,
0x00,
0x00,
0x78,
0xcc,
0x06,
0x1e,
0x06,
0xcc,
0x78,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xdd---221):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
//phh
0x00,0x00,0x00,0x00,0x00,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x7F,0x01,0x00,0x00,0x00,
/*
0x00,
0x00,
0x00,
0x00,
0x00,
0xd6,
0xd6,
0xd6,
0xd6,
0xd6,
0xd6,
0xfe,
0x03,
0x00,
0x00,
0x00,
*/
/* Character  (0xde---222):
   ht=16, width=8
   +--------+
	 ��
   +--------+ */

0x00,
0x00,
0x00,
0x00,
0x00,
0x66,
0x66,
0x66,
0x3E,
0x06,
0x06,
0x06,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xdf---223):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
//phh
0x00,
0x00,
0x00,
0x00,
0x00,
0x70,
0x70,
0x30,
0x3c,
0x32,
0x32,
0x3c,
0x00,
0x00,
0x00,
0x00,
/*
0x00,
0x00,
0x00,
0x00,
0x00,
0x70,
0xb0,
0x30,
0x3e,
0x33,
0x33,
0x7e,
0x00,
0x00,
0x00,
0x00,
*/

/* Character �� ():		  //Change by Latrom_06-09-2011
   ht=16, width=8
   +--------+
	  ��
   +--------+ */

0x00,
0x00,
0x00,
0x00,
0x00,
0x10,
0x10,
0x28,
0x28,
0x44,
0x44,
0xFE,
0x00,
0x00,
0x00,
0x00,

/* Character �� ():		  //Change by Latrom_06-09-2011
   ht=16, width=8
   +--------+
	  ��
   +--------+ */

0x00,0x00,0x00,0x00,0x00,0x97,0x95,0xB5,0xF5,0xD7,0x90,0x97,0x00,0x00,0x00,0x00,

//Following sources are capital letter. zhoutao 25-12-13

/* Character  (0xe0---224):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0xce,
0xdb,
0xdb,
0xdb,
0xfb,
0xdb,
0xdb,
0xdb,
0xdb,
0xce,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xe1---225):
   ht=16, width=8
   +--------+
	 ��
   +--------+ */
//phh
0x00,0x00,0x18,0x18,0x3C,0x2C,0x6C,0x6C,0xFE,0xC6,0xC6,0xC6,0x00,0x00,0x00,0x00,
/*
0x00,
0x00,
0x10,
0x38,
0x6c,
0xc6,
0xc6,
0xfe,
0xc6,
0xc6,
0xc6,
0xc6,
0x00,
0x00,
0x00,
0x00,
*/
/* Character  (0xe2---226):
   ht=16, width=8
   +--------+
	 ��
   +--------+ */
0x00,
0x00,
0x7e,
0x60,
0x60,
0x60,
0x7c,
0x66,
0x66,
0x66,
0x66,
0x7c,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xe3---227):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0xcc,
0xcc,
0xcc,
0xcc,
0xcc,
0xcc,
0xcc,
0xcc,
0xcc,
0xfe,
0x06,
0x00,
0x00,
0x00,
/* Character  (0xe4---228):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
//phh
0x00,
0x00,
0x3e,
0x3e,
0x36,
0x36,
0x36,
0x36,
0x36,
0x66,
0x66,
0xff,
0x81,
0x00,
0x00,
0x00,
/*
0x00,
0x00,
0x10,
0x38,
0x6c,
0x6c,
0x6c,
0x6c,
0x6c,
0x6c,
0xfe,
0x82,
0x00,
0x00,
0x00,
0x00,
*/
/* Character  (0xe5---229):
   ht=16, width=8
   +--------+
	 ��
   +--------+ */
0x00,
0x00,
0x7e,
0x60,
0x60,
0x60,
0x7c,
0x60,
0x60,
0x60,
0x60,
0x7e,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xe6---230):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
//phh
0x00,0x00,0x18,0x18,0x7E,0x99,0x99,0x99,0x99,0x99,0x7E,0x18,0x18,0x00,0x00,0x00,
/*
0x00,
0x00,
0x7e,
0xdb,
0xdb,
0xdb,
0x7e,
0x18,
0x18,
0x18,
0x18,
0x3c,
0x00,
0x00,
0x00,
0x00,
*/
/* Character  (0xe7---231):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x7e,
0x60,
0x60,
0x60,
0x60,
0x60,
0x60,
0x60,
0x60,
0x60,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xe8---232):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0xc6,
0xc6,
0x6c,
0x7c,
0x38,
0x38,
0x7c,
0x6c,
0xc6,
0xc6,
0x00,
0x00,
0x00,
0x00,

/* Character	  (0xe9---233):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */

0x00,0x00,0x46,0x46,0x4E,0x4E,0x5E,0x76,0x76,0x66,0x46,0x46,0x00,0x00,0x00,0x00,
/* Character (0xea---234):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */

0x24,0x18,0x46,0x46,0x4E,0x4E,0x5E,0x76,0x76,0x66,0x46,0x46,0x00,0x00,0x00,0x00,
/* Character 
 (0xeb---235):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,0x00,0x62,0x66,0x64,0x68,0x78,0x70,0x78,0x6C,0x66,0x62,0x00,0x00,0x00,0x00,

/* Character 
 (0xec---236):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x06,
0x0e,
0x1e,
0x36,
0x66,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xed---237):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0xc6,
0xee,
0xfe,
0xfe,
0xd6,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0x00,
0x00,
0x00,
0x00,

/* Character 
 (0xee---238):
   ht=16, width=8
   +--------+
	 ��
   +--------+ */
0x00,
0x00,
0xc6,
0xc6,
0xc6,
0xc6,
0xfe,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xef---239):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x7c,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0x7c,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xf0---240):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0xfe,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xf1---241):
   ht=16, width=8
   +--------+
	   ��
   +--------+ */
0x00,0x00,0x3E,0x66,0x66,0x66,0x3E,0x16,0x16,0x26,0x66,0x46,0x00,0x00,0x00,0x00,
/* Character  (0xf2---242):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,0x00,0x7C,0x7E,0x66,0x66,0x7E,0x7C,0x60,0x60,0x60,0x60,0x00,0x00,0x00,0x00,


/* Character  (0xf3---243):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x3c,
0x66,
0xc2,
0xc0,
0xc0,
0xc0,
0xc0,
0xc2,
0x66,
0x3c,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xf4---244):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,0x00,0x7E,0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0x00,


/* Character  (0xf5---245):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0xc6,
0xc6,
0xc6,
0xc6,
0xc6,
0x7e,
0x06,
0x46,
0x66,
0x3c,
0x00,
0x00,
0x00,
0x00,

/* Character   (0xf6---246):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,0x00,0x5A,0x5A,0x5A,0x5A,0x3C,0x3C,0x5A,0x5A,0x5A,0x5A,0x00,0x00,0x00,0x00,
/* Character  (0xf7---247):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x7c,
0x66,
0x66,
0x66,
0x7c,
0x66,
0x66,
0x66,
0x66,
0x7c,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xf8---248):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0x60,
0x60,
0x60,
0x60,
0x7c,
0x66,
0x66,
0x66,
0x66,
0x7c,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xf9---249):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0xc3,
0xc3,
0xc3,
0xc3,
0xf3,
0xdb,
0xdb,
0xdb,
0xdb,
0xf3,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xfa---250):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */

0x00,
0x00,
0x3c,
0x66,
0x46,
0x06,
0x1c,
0x04,
0x06,
0x46,
0x66,
0x3c,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xfb---251):
   ht=16, width=8
   +--------+
	   ��
   +--------+ */
0x00,0x00,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x7E,0x00,0x00,0x00,0x00,


/* Character  (0xfc---252):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */

0x00,
0x00,
0x38,
0x6c,
0x46,
0x06,
0x1e,
0x06,
0x06,
0x46,
0x6c,
0x38,
0x00,
0x00,
0x00,
0x00,

/* Character -> (0xfd---253):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,0x00,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x7F,0x01,0x00,0x00,0x00,
/* Character  (0xfe---254):
   ht=16, width=8
   +--------+
	  ��
   +--------+ */
0x00,
0x00,
0xcc,
0xcc,
0xcc,
0xcc,
0x7c,
0x0c,
0x0c,
0x0c,
0x0c,
0x0c,
0x00,
0x00,
0x00,
0x00,

/* Character  (0xff---255):
   ht=16, width=8
   +--------+
	   ��
   +--------+ */
0x00,
0x00,
0xf0,
0xf0,
0x30,
0x30,
0x3e,
0x33,
0x33,
0x33,
0x33,
0x3e,
0x00,
0x00,
0x00,
0x00,

/* Character �� ():		  //Change by Latrom_06-09-2011
   ht=16, width=8
   +--------+
	  ��
   +--------+ */

0x00,
0x00,
0x00,
0x00,
0x00,
0x10,
0x10,
0x28,
0x28,
0x44,
0x44,
0xFE,
0x00,
0x00,
0x00,
0x00,

/* Character �� ():		  //Change by Latrom_06-09-2011
   ht=16, width=8
   +--------+
	  ��
   +--------+ */

0x00,0x00,0x00,0x00,0x00,0x97,0x95,0xB5,0xF5,0xD7,0x90,0x97,0x00,0x00,0x00,0x00,

};

/* Exported structure definition. */
RBFINFO rbf_russian8x16 =
{
	FONT_RBF_ROM_8X16_RUSSIAN,
	68,									  // Change by Latrom_06-15-2011
	8,
	16,
	NULL,
	(UINT8 *)russian8x16_bits,		// font data
	68*16									// Change by Latrom_06-15-2011
};

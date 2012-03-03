#ifndef PICCOLO_H_
#define PICCOLO_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#if     PICCOLO==80
#define KEYSIZE       80
#define RN            25
#define N             10
#elif   PICCOLO==128
#define KEYSIZE       128
#define RN            31
#define N             16
#endif

#define BLOCK_SIZE    64
#define GF_POLY       0x13 /* irred. polynomial f = x^4+x+1 for F_16 = F_2[x]/(f) */
#define DEG_GF_POLY   4

typedef unsigned char BYTE; /* 8 bit */
typedef unsigned long WORD; /* 32 bit */


/* key */
typedef struct {
  WORD wKey[2]; /* whitening keys: wKey[0] = w_0 | w_1, wKey[1] = w_2 | w_3 */
  WORD rKey[RN]; /* round keys: 2 round keys are encoded in a 32-bit word */
} KEY;


/* 64-bit state */
typedef struct {
  WORD b[2]; 
} STATE;


/* function definitions */
void keySchedule(BYTE x[], KEY *k); 
void encrypt(STATE *s, KEY *k);
void f(BYTE b[]);
void rp(STATE *s);
BYTE gm(BYTE a, BYTE b);


/* the Piccolo SBox */
BYTE SBox[16] = { 
  0xE, 0x4, 0xB, 0x2, 0x3, 0x8, 0x0, 0x9,
  0x1, 0xA, 0x7, 0xF, 0x6, 0xC, 0x5, 0xD
};


/* the diffusion matrix */
const BYTE M[4][4] = {
  {0x2,0x3,0x1,0x1},
  {0x1,0x2,0x3,0x1},
  {0x1,0x1,0x2,0x3},
  {0x3,0x1,0x1,0x2},
};


/* constants for the key schedule */
#if KEYSIZE==80
const WORD C[RN] = {
  0x071c293d, 0x1f1a253e, 0x1718213f, 0x2f163d38, 0x27143939,
  0x3f12353a, 0x3710313b, 0x4f0e0d34, 0x470c0935, 0x5f0a0536,
  0x57080137, 0x6f061d30, 0x67041931, 0x7f021532, 0x77001133,
  0x8f3e6d2c, 0x873c692d, 0x9f3a652e, 0x9738612f, 0xaf367d28,
  0xa7347929, 0xbf32752a, 0xb730712b, 0xcf2e4d24, 0xc72c4925
};
#elif KEYSIZE==128
const WORD C[RN] = {
  0x6d45ad8a, 0x7543a189, 0x7d41a588, 0x454fb98f, 0x4d4dbd8e,
  0x554bb18d, 0x5d49b58c, 0x25578983, 0x2d558d82, 0x35538181,
  0x3d518580, 0x055f9987, 0x0d5d9d86, 0x155b9185, 0x1d599584,
  0xe567e99b, 0xed65ed9a, 0xf563e199, 0xfd61e598, 0xc56ff99f,
  0xcd6dfd9e, 0xd56bf19d, 0xdd69f59c, 0xa577c993, 0xad75cd92,
  0xb573c191, 0xbd71c590, 0x857fd997, 0x8d7ddd96, 0x957bd195,
  0x9d79d594
};
#endif
#endif /* PICCOLO_H_ */


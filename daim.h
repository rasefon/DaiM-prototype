/************************************************

  daim.h -

  $Author: wzq $
  $Date: 2014/04/06 $

  Copyright (C) 2014 Zheqin Wang

************************************************/
#ifndef DAIM_H
#define DAIM_H

typedef unsigned long DM_ULONG;
typedef unsigned long DM_INTER_VALUE;
typedef unsigned short DM_USHORT;

#include <limits.h>
//Only use 30 bits, the leftmost 2 bits are unused.
#define DMNUM_MAX (LONG_MAX>>1)
// Different c compiler may have different behavior for right shift!
#define DMNUM_MIN (LONG_MIN>>1) 
#define PFIXABLE(n) ((n) <= DMNUM_MAX)
#define NFIXABLE(n) ((n) >= DMNUM_MIN)

#define DM_NUM_FLAG 0x01
#define INT2DMNUM(n) ((DM_ULONG)(((long)(i))<<1|DM_NUM_FLAG))
#define LONG2DMNUM(n) INT2DMNUM(n)
#define DMNUM2LONG(n) (((long)(n))>>1)
#define DMNUM2INT(n) DMNUM2LONG(n)
#define DMNUM2ULONG(n) (((DM_ULONG)(n))>>1)
#define IS_DMNUM(n) (((long)(n))&DM_NUM_FLAG)

#define DMfalse   0
#define DMtrue    2
#define DMnil     4
// In dm language, false and nil are considered as nil.
#define IS_DMNIL(v) (((DM_ULONG)(v)&~DMnil)!=0)

//=========0x------xx==============
//Rightmost 8 bits is used to determine the Dm internal type, such as string, big number...

#endif

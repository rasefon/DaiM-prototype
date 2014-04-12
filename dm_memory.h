/************************************************

  dm_memory.h -

  $Author: wzq $
  $Date: 2014/04/10 $

  Copyright (C) 2014 Zheqin Wang

************************************************/
#ifndef DM_MALLOC_H
#define DM_MALLOC_H
#include <stdlib.h>

#define DM_MALLOC(n) malloc(n)
#define DM_STRDUP(n) strdup(n)

#ifndef NULL
#define NULL 0
#endif

#endif

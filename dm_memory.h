/************************************************

  dm_memory.h -

  $Author: wzq $
  $Date: 2014/04/10 $

  Copyright (C) 2014 Zheqin Wang

************************************************/
#ifndef DM_MALLOC_H
#define DM_MALLOC_H
#include <stdlib.h>

#define DM_MALLOC malloc
#define DM_CALLOC calloc
#define DM_STRDUP strdup

#ifndef NULL
#define NULL 0
#endif

#endif

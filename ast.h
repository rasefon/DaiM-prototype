/************************************************

  ast.h -

  $Author: wzq $
  $Date: 2014/04/08 $

  Copyright (C) 2014 Zheqin Wang

************************************************/
#ifndef AST_H
#define AST_H
#include "daim.h"

typedef struct {
   DM_ULONG flags;
   union {
      struct Dm_node*   node;
      DM_INTER_VALUE    inter_value;  
      DM_ULONG          sym_id;
   } m1;
} Dm_node;

#endif

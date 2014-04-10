/************************************************

  ast.c -

  $Author: wzq $
  $Date: 2014/04/06 $

  Copyright (C) 2014 Zheqin Wang

************************************************/
#include "ast.h"
#include "dm_memory.h"

inline void set_node_type(DmNode* node, enum dm_node_type type)
{
   node->flag = ((node->flag & DM_NODE_TYPE_MASK) | (type << DM_TYPE_WIDTH));
}

inline void set_node_lineno(DmNode* node, DM_USHORT lineno)
{
   node->lineno = lineno;
}

DmNode* make_dm_node(enum dm_node_type type, DM_USHORT lineno, DmNode* n1, DmNode* n2, DmNode* n3)
{
   //Currently, just alloc memory directly, use macro for further changes.
   DmNode* node = DM_MALLOC(sizeof(DmNode));
   set_node_type(node, type);
   set_node_lineno(node, lineno);
   node->n1.node = n1;
   node->n2.node = n2;
   node->n3.node = n3;
   return node;
}


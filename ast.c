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

inline void set_node_bin_num(DmNode* node, DM_USHORT bin_num)
{
   node->bin_num = bin_num;
}

DmNode* dm_create_node(enum dm_node_type type, DM_USHORT lineno, DM_USHORT bin_num, 
      DM_ULONG m1, DmNode*** m2)
{
   //Currently, just alloc memory directly, use macro for further changes.
   DmNode* node = DM_MALLOC(sizeof(DmNode));
   set_node_type(node, type);
   set_node_lineno(node, lineno);
   set_node_bin_num(node, bin_num);
   node->m1.op = m1;
   node->m2.node_bin = *m2;
   return node;
}

DmNode* dm_create_param_node(char* id_name, DM_USHORT lineno)
{
   DmNode* node = dm_create_node(nd_id_name, lineno, 0, (DM_ULONG)id_name, NULL);
   return node;
}

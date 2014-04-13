/************************************************

  ast.c -

  $Author: wzq $
  $Date: 2014/04/06 $

  Copyright (C) 2014 Zheqin Wang

************************************************/
#include <assert.h>
#include <stdio.h>
#include "ast.h"
#include "st.h"
#include "dm_memory.h"

extern st_table* g_name_id_tbl;
/*extern st_table* g_id_name_tbl;*/

/*#define _GLOBAL_TBL_ASSERT_   assert(g_name_id_tbl && g_id_name_tbl)*/
#define _GLOBAL_TBL_ASSERT_   assert(g_name_id_tbl)

inline void set_node_type(DmNode* node, enum dm_node_type type)
{
   node->flag = ((node->flag & DM_NODE_TYPE_MASK) | (type << DM_TYPE_WIDTH));
}

inline void set_node_lineno(DmNode* node, DM_USHORT lineno)
{
   node->lineno = lineno;
}

DmNode* dm_create_node(enum dm_node_type type, DM_ULONG m1, DmNode* m2, DM_USHORT lineno)
{
   //Currently, just alloc memory directly, use macro for further changes.
   DmNode* node = DM_MALLOC(sizeof(DmNode));
   set_node_type(node, type);
   set_node_lineno(node, lineno);
   node->m1.op = m1;
   node->m2.next = m2;
   return node;
}

DmNode* dm_create_param_node(char* id_name, DM_USHORT lineno)
{
   DmNode* node = dm_create_node(nd_id_name, (DM_ULONG)id_name, NULL, lineno);
   return node;
}

DmNode* dm_link_param_node(DmNode* node_hd, char* id_name, DM_USHORT lineno)
{
   DmNode* node_tail = node_hd;
   while(node_tail->m2.next) {
      node_tail = node_tail->m2.next;
   }
   node_tail->m2.next = dm_create_node(nd_id_name, (DM_ULONG)id_name, NULL, lineno);
   return node_hd;
}

DmNode* dm_create_func_def_node(char* func_name, DmNode* param_list, DmNode* stmt_list, 
      DM_USHORT lineno)
{
   _GLOBAL_TBL_ASSERT_;
   DM_ULONG func_id;
   DmNode* func_node;
   if (st_lookup(g_name_id_tbl, func_name, (char**)&func_id)) {
      //TODO
      printf("function redefined:%s\n", func_name);
      abort();
   }
   else {
      DmNodeList* node_list = DM_MALLOC(sizeof(DmNodeList));
      int bin_num = 2;
      node_list->bin_num = bin_num;
      node_list->node_bin = DM_CALLOC(bin_num, sizeof(DmNode*));
      node_list->node_bin[0] = param_list;
      node_list->node_bin[1] = stmt_list;
      func_node = dm_create_node(nd_func_def, (DM_ULONG)func_name, (DmNode*)node_list, lineno);
      st_insert(g_name_id_tbl, func_name, (char*)func_node);
      /*st_insert(g_id_name_tbl, (char*)func_node, func_name);*/
   }

   return func_node; 
}

DmNode* dm_create_or_find_id_node(char* id_name, DM_USHORT lineno)
{
   _GLOBAL_TBL_ASSERT_;
   DmNode* id_node;
   if (!st_lookup(g_name_id_tbl, id_name, (char**)&id_node)) {
      id_node = dm_create_node(nd_id_name, (DM_ULONG)id_name, NULL, lineno);
      st_insert(g_name_id_tbl, id_name, (char*)id_name);
   }
   return id_node;
}

DmNode* dm_find_id_node(char* id_name)
{
   _GLOBAL_TBL_ASSERT_;
   DmNode* id_node;
   if (!st_lookup(g_name_id_tbl, id_name, (char**)&id_node)) {
      //TODO
      printf("undefined variable:%s\n", id_name);
      abort();
   }
   return id_node;
}


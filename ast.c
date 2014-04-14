/************************************************

  ast.c -

  $Author: wzq $
  $Date: 2014/04/06 $

  Copyright (C) 2014 Zheqin Wang

************************************************/
#include <assert.h>
#include <stdio.h>
#include "ast.h"
#include "daim.h"
#include "st.h"
#include "dm_memory.h"

extern st_table* g_name_id_tbl;
/*extern st_table* g_str_val_tbl;*/

/*#define _GLOBAL_TBL_ASSERT_   assert(g_name_id_tbl && g_str_val_tbl)*/
#define _GLOBAL_TBL_ASSERT_   assert(g_name_id_tbl)

inline void set_node_type(DmNode* node, enum dm_node_type type)
{
   node->flag = ((node->flag & DM_NODE_TYPE_MASK) | (type << DM_TYPE_WIDTH));
}

inline void set_node_lineno(DmNode* node, DM_USHORT lineno)
{
   node->lineno = lineno;
}

inline DmNode* dm_create_node(enum dm_node_type type, DM_USHORT lineno)
{
   //Currently, just alloc memory directly, use macro for further changes.
   DmNode* node = DM_MALLOC(sizeof(DmNode));
   set_node_type(node, type);
   set_node_lineno(node, lineno);
   return node;
}

DmNode* dm_create_param_node(char* str_val, DM_USHORT lineno)
{
   DmNode* node = dm_create_node(nd_param_list, lineno);
   node->m_nd_param_name = str_val;
   return node;
}

DmNode* dm_link_param_node(DmNode* node_hd, char* str_val, DM_USHORT lineno)
{
   DmNode* node_tail = node_hd;
   while(node_tail->m2.node) {
      node_tail = node_tail->m_nd_param_next;
   }
   node_tail->m2.node = dm_create_node(nd_param_list, lineno);
   (node_tail->m2.node)->m_nd_param_name = str_val;
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
      node_list->m_nd_func_param_list = param_list;
      node_list->m_nd_func_stmt_list = stmt_list;
      func_node = dm_create_node(nd_func_def, lineno);
      func_node->m_nd_func_name = func_name;
      func_node->m_nd_func_body = node_list;
      st_insert(g_name_id_tbl, func_name, (char*)func_node);
      /*st_insert(g_str_val_tbl, (char*)func_node, func_name);*/
   }

   return func_node; 
}

DmNode* dm_create_or_find_id_node(char* str_val, DM_USHORT lineno)
{
   _GLOBAL_TBL_ASSERT_;
   DmNode* id_node;
   if (!st_lookup(g_name_id_tbl, str_val, (char**)&id_node)) {
      id_node = dm_create_node(nd_str_val, lineno);
      id_node->m_nd_id_name = str_val;
      st_insert(g_name_id_tbl, str_val, (char*)str_val);
   }
   return id_node;
}

DmNode* dm_find_id_node(char* str_val)
{
   _GLOBAL_TBL_ASSERT_;
   DmNode* id_node;
   if (!st_lookup(g_name_id_tbl, str_val, (char**)&id_node)) {
      //TODO
      printf("undefined variable:%s\n", str_val);
      abort();
   }
   return id_node;
}


DmNode* dm_create_int_node(int val, DM_USHORT lineno)
{
   DmNode* node = dm_create_node(nd_int_val, lineno);
   node->m_nd_int_val = val;
   return node;
}

DmNode* dm_create_double_node(char* double_val, DM_USHORT lineno)
{
   DmNode* node = dm_create_node(nd_double_val, lineno);
   node->m_nd_double_val = double_val;
   return node;
}

DmNode* dm_const_node(enum dm_node_type type, DM_USHORT lineno)
{
   DmNode* node = dm_create_node(type, lineno);
   if (nd_kTrue == type) {
      node->m_nd_const_val = DMtrue;
   }
   else if (nd_kFalse == type) {
      node->m_nd_const_val = DMfalse;
   }
   else if (nd_kNil == type) {
      node->m_nd_const_val = DMnil;
   }
   return node;
}

DmNode* dm_create_arg_list(DmNode* expr, DM_USHORT lineno)
{
   DmNode* node = dm_create_node(nd_arg_list, lineno);
   node->m_nd_arg_node = expr;
   return node;
}

DmNode* dm_link_arg_list(DmNode* arg_list, DmNode* node, DM_USHORT lineno)
{
   DmNode* arg_tail = arg_list->m_nd_arg_node;
   while(arg_tail->m_nd_arg_next) {
      arg_tail = arg_tail->m_nd_arg_next;
   }
   arg_tail->m_nd_arg_next = node;
   return arg_list;
}

DmNode* dm_create_func_call_node(char* func_name, DmNode* arg_list, DM_USHORT lineno)
{
   DmNode* func_call_node;
   DmNode* func_def_node;
   if(st_lookup(g_name_id_tbl, func_name, (char**)&func_def_node)) {
      func_call_node = dm_create_node(nd_func_call, lineno);
      func_call_node->m_nd_func_arg_list = arg_list;
   }
   else {
      //TODO
      printf("Can't find function definition:%s.\n", func_name);
      abort();
   }
   return func_call_node;
}

DmNode* dm_create_unary_node(enum dm_node_type type, DmNode* unary_expr, DM_USHORT lineno)
{
   DmNode* unary_node = dm_create_node(type, lineno);
   unary_node->m_nd_unary_node = unary_expr;
   return unary_node;
}

DmNode* dm_create_binary_node(enum dm_node_type type, DmNode* left, DmNode* right, DM_USHORT lineno)
{
   //TODO constant optimize.
   DmNode* bi_node = dm_create_node(type, lineno);
   bi_node->m_nd_left_node = left;
   bi_node->m_nd_right_node = right;
   return bi_node;
}

DmNode* dm_create_selection_node(DmNode* condition, DmNode* if_node, DmNode* else_node,
     DmNode* elsif_node, DmNode* last_else_node, DM_USHORT lineno)
{
   DmNode* condition_node = dm_create_node(nd_kIf, lineno);
   condition_node->m_nd_if_cond = condition;
   DmNodeList* node_list = DM_MALLOC(sizeof(DmNodeList));
   int bin_num = 4;
   node_list->node_bin = DM_CALLOC(bin_num, sizeof(DmNode*));
   node_list->m_nd_if_node = if_node;
   node_list->m_nd_else_node = else_node;
   node_list->m_nd_elsif_node = elsif_node;
   node_list->m_nd_last_else_node = last_else_node;
   condition_node->m_nd_if_block = node_list;
   return condition_node;
}

DmNode* dm_create_elsif_node(DmNode* condition, DmNode* stmt, DM_USHORT lineno)
{
   DmNode* elsif_node = dm_create_node(nd_kElsif, lineno);
   elsif_node->m_nd_elsif_cond = condition;
   elsif_node->m_nd_elsif_stmt = stmt;
   return elsif_node;
}

DmNode* dm_link_elsif_node(DmNode* elsif_list, DmNode* elsif)
{
   DmNode* list_tail = elsif_list;
   while(list_tail->m_nd_elsif_next) {
      list_tail = list_tail->m_nd_elsif_next;
   }
   list_tail->m_nd_elsif_next = elsif;
   return elsif_list;
}

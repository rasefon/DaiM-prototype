/************************************************

  ast.h -

  $Author: wzq $
  $Date: 2014/04/08 $

  Copyright (C) 2014 Zheqin Wang

************************************************/
#ifndef AST_H
#define AST_H
#include "daim.h"

enum dm_node_type {
   nd_kAssign = 1,
   nd_KAddAssign,
   nd_kSubAssign,
   nd_kMulAssign,
   nd_kDivAssign,
   nd_kAnd,
   nd_kOr,
   nd_kEq,
   nd_kNe,
   nd_kGt,
   nd_kLt,
   nd_kGE,
   nd_kLE,
   nd_kPlus,
   nd_kMinus,
   nd_kMul,
   nd_kDiv,
   nd_kMod,
   nd_kNot,
   nd_kNext,
   nd_kBreak,
   nd_kReturn,
   nd_kTrue,
   nd_kFalse,
   nd_kNil,
   nd_kIf,
   nd_kElsif,
   nd_kLoop,
   nd_func_def,
   nd_func_call,
   nd_param_list,
   nd_sym_id,
   nd_stmt_list,
   nd_stmt,
   nd_expr_list,
   nd_expr,
   nd_str_val,
   nd_int_val,
   nd_double_val,
   nd_arg_list
};

struct DmNode {
   DM_ULONG flag; 
   DM_USHORT lineno;

   union {
      DM_ULONG ul_val;
      int      int_val;
      char*    str_val;
      struct DmNode*  node;
   } m1;

   union {
      struct DmNode* node;
      struct DmNodeList* list;
   } m2;
};
typedef struct DmNode DmNode;

struct DmNodeList {
   DM_USHORT bin_num;
   DmNode** node_bin;
};
typedef struct DmNodeList DmNodeList;

//=========0x----xx--==============
//These 8 bits flag determin the dm_node_type
#define DM_TYPE_WIDTH  8
#define DM_NODE_TYPE_MASK  0xffff00ff  
#define DM_NODE_TYPE(nd) ((((DmNode*)(nd))->flag>>DM_INT_TYPE_WIDTH) & 0xff)

#define m_nd_param_name          m1.str_val
#define m_nd_param_next          m2.node
#define m_nd_func_name           m1.str_val
#define m_nd_func_body           m2.list
#define m_nd_func_param_list     node_bin[0]
#define m_nd_func_stmt_list      node_bin[1]
#define m_nd_id_name             m1.str_val
#define m_nd_int_val             m1.int_val
#define m_nd_double_val          m1.str_val
#define m_nd_const_val           m1.ul_val
#define m_nd_arg_node            m1.node
#define m_nd_func_arg_list       m1.node
#define m_nd_unary_node          m1.node
#define m_nd_left_node           m1.node
#define m_nd_right_node          m2.node
#define m_nd_if_cond             m1.node
#define m_nd_if_block            m2.list
#define m_nd_if_node             node_bin[0]
#define m_nd_else_node           node_bin[1]
#define m_nd_elsif_node          node_bin[2]
#define m_nd_last_else_node      node_bin[3]
#define m_nd_elsif_cond          m1.node
#define m_nd_elsif_stmt          m2.node
#define m_nd_iter_cond           m1.node
#define m_nd_iter_stmt           m2.node
#define m_nd_assign_id           m1.node
#define m_nd_assign_expr         m2.node
#define m_nd_expr_node           m1.node
#define m_nd_link_list           m1.node
#define m_nd_link_next           m2.node

inline void set_node_type(DmNode*, enum dm_node_type);
inline void set_node_lineno(DmNode*, DM_USHORT);
inline DmNode* dm_create_node(enum dm_node_type, DM_USHORT );
DmNode* dm_create_param_node(char* str_val, DM_USHORT);
DmNode* dm_link_param_node(DmNode* node_hd, char* str_val, DM_USHORT);
DmNode* dm_create_func_def_node(char* func_name, DmNode* parm_list, DmNode* stmt_list, DM_USHORT);
DmNode* dm_create_or_find_id_node(char* str_val, DM_USHORT);
DmNode* dm_find_id_node(char* str_val);
DmNode* dm_create_int_node(int val, DM_USHORT);
DmNode* dm_create_double_node(char* double_val, DM_USHORT);
DmNode* dm_const_node(enum dm_node_type, DM_USHORT);
DmNode* dm_create_arg_list(DmNode* expr, DM_USHORT);
DmNode* dm_link_node_list(DmNode* arg_list, DmNode* expr);
DmNode* dm_create_func_call_node(char* func_name, DmNode* arg_list, DM_USHORT);
DmNode* dm_create_unary_node(enum dm_node_type type, DmNode* unary_expr, DM_USHORT);
DmNode* dm_create_binary_node(enum dm_node_type type, DmNode* left, DmNode* right, DM_USHORT);
DmNode* dm_create_selection_node(DmNode* condition, DmNode* if_stmt, DmNode* else_stmt,
     DmNode* elsif_stmt, DmNode* last_else_stmt, DM_USHORT);
DmNode* dm_create_elsif_node(DmNode* condition, DmNode* stmt, DM_USHORT);
DmNode* dm_create_iter_node(DmNode* condition, DmNode* stmt_list, DM_USHORT);
DmNode* dm_create_assign_node(char* id_name, DM_ULONG assign_op, DmNode* expr_node, DM_USHORT);

#endif

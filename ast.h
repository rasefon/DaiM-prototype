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
   DM_ULONG flag; 
} DmNode;

enum dm_node_type {
   nd_kFunc = 1,
   nd_kAssign,
   nd_KAddAssign,
   nd_kSubAssign,
   nd_kMulAssign,
   nd_kDivAssign,
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
   nd_func_def,
   nd_param_list,
   nd_sym_id,
   nd_stmt_list,
   nd_stmt,
   nd_expr_list,
   nd_expr,
   nd_logical_or_expr,
   nd_logical_and_expr,
   nd_eq_expr,
   nd_relational_expr,
   nd_add_sub_expr,
   nd_mul_div_expr,
   nd_unary_expr,
   nd_primary_expr,
   nd_str_val,
   nd_double_val,
   nd_arg_list,
   nd_assign_op_expr,
   nd_assign_op,
   nd_selection_stmt,
   nd_elsif_list,
   nd_elsif,
   nd_iter_stmt,
   nd_jump_stmt,
};
//=========0x----xx--==============
//These 8 bits flag determin the dm_node_type
#define DM_INT_TYPE_WIDTH  8
#define DM_NODE_TYPE_MASK  0xff  
#define DM_NODE_TYPE(nd) ((((DmNode*)(nd))->flag>>DM_INT_TYPE_WIDTH) & DM_NODE_TYPE_MASK)

#endif

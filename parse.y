/************************************************

  parse.y -

  $Author: wzq $
  $Date: 2014/04/06 $

  Copyright (C) 2014 Zheqin Wang

************************************************/
%{
#include <stdio.h>
#include <stdarg.h>
#include "ast.h"
#include "dm_memory.h"
#include "st.h"
#define YYDEBUG 1

void yyerror(char *s, ...);

extern st_table* g_sym_tbl;
extern int yylineno;
%}

%union {
   DmNode*     node;
   DM_ULONG    ul_val;
   int         int_val;
   char*       str_val;
}

//---------------------current not used-----------------------
%token BOOL INT DOUBLE STR  
//------------------------------------------------------------
//---------------------keywords-------------------------------
%token RECORD IF ELSE ELSIF LOOP NEXT BREAK FUNC RETURN AND_OP OR_OP EQ_OP NE_OP LE_OP GE_OP 
       ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN END
//------------------------------------------------------------
%token <str_val>  STR_VALUE DOUBLE_VALUE
%token <ul_val>   TRUE FALSE NIL
%token <int_val>  INT_VALUE
%token <str_val>  ID 

%type <node> selection_stmt iteration_stmt jump_stmt stmt
%type <node> func_def stmt_list param_list argument_list
%type <node> expr logical_or_expr logical_and_expr eq_expr relational_expr
            add_sub_expr mul_div_expr unary_expr primary_expr
%type <node> elsif elsif_list

%start parse_unit

%%

parse_unit
   : defs_or_stmt
   | parse_unit defs_or_stmt
;

defs_or_stmt
   : func_def
   | stmt
;

func_def
   : FUNC ID '(' param_list ')' stmt_list END {
      $$ = dm_create_func_def_node($2, $4, $6, yylineno);     
   }
   | FUNC ID '(' ')' stmt_list END {
      $$ = dm_create_func_def_node($2, NULL, $5, yylineno);
   }
;

param_list
   : ID {
      $$ = dm_create_param_node($1, yylineno);
   }
   | param_list ',' ID {
      $$ = dm_link_param_node($1, $3, yylineno);
   }
;

stmt_list
   : stmt
   | stmt_list stmt
;

stmt
   : expr_list ';'
   | selection_stmt 
   | iteration_stmt
   | jump_stmt 
;

expr_list
   : expr
   | expr_list ',' expr
   ;

expr
   : logical_or_expr
   | ID assignment_op expr
;

assignment_op
   : '='
   | ADD_ASSIGN
   | SUB_ASSIGN
   | MUL_ASSIGN
   | DIV_ASSIGN
; 

logical_or_expr
   : logical_and_expr
   | logical_or_expr OR_OP logical_and_expr
;

logical_and_expr
   : eq_expr
   | logical_and_expr AND_OP eq_expr
;

eq_expr
   : relational_expr
   | eq_expr EQ_OP relational_expr
   | eq_expr NE_OP relational_expr
;

relational_expr
   : add_sub_expr
   | relational_expr '<' add_sub_expr
   | relational_expr '>' add_sub_expr
   | relational_expr LE_OP add_sub_expr
   | relational_expr GE_OP add_sub_expr 
;

add_sub_expr
   : mul_div_expr
   | add_sub_expr '+' mul_div_expr
   | add_sub_expr '-' mul_div_expr
;

mul_div_expr
   : unary_expr
   | mul_div_expr '*' unary_expr
   | mul_div_expr '/' unary_expr
   | mul_div_expr '%' unary_expr
;

unary_expr
   : primary_expr
   | '!' unary_expr
;

primary_expr
   : ID {
      $$ = dm_find_id_node($1);
   }
   | STR_VALUE {
      //TODO
   }
   | INT_VALUE {
      $$ = dm_create_int_node($1, yylineno);      
   }
   | DOUBLE_VALUE {
      $$ = dm_create_double_node($1, yylineno);
   }
   | NIL {
      $$ = dm_const_node(nd_kNil, yylineno);
   }
   | TRUE {
      $$ = dm_const_node(nd_kTrue, yylineno);
   }
   | FALSE {
      $$ = dm_const_node(nd_kFalse, yylineno);
   }
   | '(' expr ')' {
      $$ = $2;
   }
   | ID '(' argument_list ')' {
      $$ = dm_create_func_call_node($1, $3, yylineno);
   }
   | ID '(' ')' {
      $$ = dm_create_func_call_node($1, NULL, yylineno);
   }
;

argument_list
   : expr {
      $$ = dm_create_arg_list($1, yylineno);
   }
   | argument_list ',' expr {
      $$ = dm_link_arg_list($1, $3, yylineno);
   }
;

selection_stmt
   : IF '(' logical_or_expr ')' stmt_list END
   | IF '(' logical_or_expr ')' ELSE stmt_list END
   | IF '(' logical_or_expr ')' elsif_list END
   | IF '(' logical_or_expr ')' elsif_list ELSE stmt_list END
;

elsif_list
   : elsif
   | elsif_list elsif
;

elsif
   : ELSIF '(' logical_or_expr ')' stmt_list
;

iteration_stmt
   : LOOP '(' logical_or_expr ')' stmt_list END

jump_stmt
   : NEXT ';'
   | BREAK ';'
   | RETURN ';'
;

%%

void yyerror(char *s, ...)
{
  va_list ap;
  va_start(ap, s);

  fprintf(stdout, "%d: error: ", yylineno);
  vfprintf(stdout, s, ap);
  fprintf(stdout, "\n");
}


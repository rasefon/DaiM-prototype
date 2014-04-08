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
#define YYDEBUG 1

void yyerror(char *s, ...);
%}

%union {
   Dm_node*          node;
   DM_ULONG          sym_id; 
   DM_INTER_VALUE    inter_value;
}

//---------------------current not used-----------------------
%token BOOL INT DOUBLE STR  
//------------------------------------------------------------
//---------------------keywords-------------------------------
%token RECORD IF ELSE ELSIF LOOP NEXT BREAK FUNC RETURN AND_OP OR_OP EQ_OP NE_OP LE_OP GE_OP 
       ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN END
//------------------------------------------------------------
%token<node> STR_VALUE DOUBLE_VALUE
%token<inter_value> INT_VALUE TRUE FALSE NIL
%token<sym_id> ID 

%type<node> selection_stmt iteration_stmt jump_stmt stmt
%type<node> stmt_list
%type<node> param_list
%type<node> argument_list
%type<node> expr logical_or_expr logical_and_expr eq_expr relational_expr
            additive_expr multiplicative_expr unary_expr primary_expr
%type<node> elsif elsif_list

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
   : FUNC ID '(' param_list ')' stmt_list END
   | FUNC ID '(' ')' stmt_list END
;

param_list
   : ID
   | param_list ',' ID
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
   : additive_expr
   | relational_expr '<' additive_expr
   | relational_expr '>' additive_expr
   | relational_expr LE_OP additive_expr
   | relational_expr GE_OP additive_expr 
;

additive_expr
   : multiplicative_expr
   | additive_expr '+' multiplicative_expr
   | additive_expr '-' multiplicative_expr
;

multiplicative_expr
   : unary_expr
   | multiplicative_expr '*' unary_expr
   | multiplicative_expr '/' unary_expr
   | multiplicative_expr '%' unary_expr
;

unary_expr
   : primary_expr
   | '!' unary_expr
;

primary_expr
   : ID
   | STR_VALUE
   | INT_VALUE
   | DOUBLE_VALUE 
   | NIL
   | TRUE
   | FALSE
   | '(' expr ')'
   | ID '(' argument_list ')'
   | ID '(' ')'
;

argument_list
   : expr
   | argument_list ',' expr
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
  extern yylineno;

  va_list ap;
  va_start(ap, s);

  fprintf(stdout, "%d: error: ", yylineno);
  vfprintf(stdout, s, ap);
  fprintf(stdout, "\n");
}


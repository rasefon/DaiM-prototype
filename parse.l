/************************************************

  parse.l -

  $Author: wzq $
  $Date: 2014/04/06 $

  Copyright (C) 2014 Zheqin Wang

************************************************/

%{
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "y.tab.h"
#include "dm_memory.h"
%}

%option noyywrap yylineno
%x COMMENT STRING_STATE

ID             [_a-zA-Z][_a-zA-Z0-9]*

%%
"#"                  { BEGIN COMMENT; }
<COMMENT>.           /*Do nothing.*/;
<COMMENT>\n          { BEGIN INITIAL; }
\"                   { BEGIN STRING_STATE; }
<STRING_STATE>\"     { 
   BEGIN INITIAL;
   //TODO
}
<STRING_STATE>\\\"   { return STR_VALUE; }
<STRING_STATE>\\n    { 
   //TODO; 
}
<STRING_STATE>\\t    { 
   //TODO; 
}
<STRING_STATE>\\\\   { 
   //TODO; 
}
<STRING_STATE>.*     { 
   //TODO; 
}
"bool"               { return BOOL; }
"int"                { return INT; }
"double"             { return DOUBLE; } 
"string"             { return STR; }
"record"             { return RECORD; }
"if"                 { return IF; }
"else"               { return ELSE; }
"elsif"              { return ELSIF; }
"true"               { return TRUE; }
"false"              { return FALSE; }
"loop"               { return LOOP; }
"next"               { return NEXT; }
"break"              { return BREAK; }
"func"               { return FUNC; }
"return"             { return RETURN; }
"nil"                { return NIL; }
"end"                { return END; }
"("                  { return '('; }
")"                  { return ')'; }
"["                  { return '['; }
"]"                  { return ']'; }
"{"                  { return '{'; }
"}"                  { return '}'; }
","                  { return ','; }
"="                  { return '='; }
">"                  { return '>'; }
"<"                  { return '<'; }
"!"                  { return '!'; }
"+"                  { return '+'; }
"-"                  { return '-'; }
"*"                  { return '*'; }
"/"                  { return '/'; }
"%"                  { return '%'; }
";"                  { return ';'; }
"&&"                 { return AND_OP; }
"||"                 { return OR_OP; }
"=="                 { return EQ_OP; }
"!="                 { return NE_OP; }
"<="                 { return LE_OP; }
">="                 { return GE_OP; }
"+="                 { return ADD_ASSIGN; }
"-="                 { return SUB_ASSIGN; }
"*="                 { return MUL_ASSIGN; }
"/="                 { return DIV_ASSIGN; } 
{ID}                 { 
   yylval.str_val = DM_STRDUP(yytext);
   return ID; 
}

-?([0-9][0-9]*)      { 
   yylval.int_val = atoi(yytext);
   return INT_VALUE; 
}

-?[0-9]+\.[0-9]+     { 
   yylval.str_val = DM_STRDUP(yytext);
   return DOUBLE_VALUE; 
}
%%

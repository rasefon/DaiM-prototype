/************************************************

  dm_memory.c -

  $Author: wzq $
  $Date: 2014/04/12 $

  Copyright (C) 2014 Zheqin Wang

************************************************/

// globle symbols table, temp symbol table and so on...
#include "dm_memory.h"
#include "st.h"
st_table* g_name_id_tbl = NULL;
st_table* g_id_name_tbl = NULL;


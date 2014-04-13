/************************************************

  main.c -

  $Author: wzq $
  $Date: 2014/04/06 $

  Copyright (C) 2014 Zheqin Wang

************************************************/
#include <string.h>
#include "st.h"
#include "dm_memory.h"

extern st_table* g_name_id_tbl;
extern st_table* g_id_name_tbl;
#define DEFAULT_BIN_NUM 512

int main(int argc, char** argv)
{
   g_name_id_tbl = st_init_strtable_with_size(DEFAULT_BIN_NUM);
   g_id_name_tbl = st_init_numtable_with_size(DEFAULT_BIN_NUM);
   return 0;
}

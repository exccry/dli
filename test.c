#include "dli.h"

int main()
{
  /*dli list;
  EXIT_ON_ERR(dli_init(&list, sizeof(int), 25, print_int), FATAL_ERR_MSG);
  EXIT_ON_ERR(dli_pseudo_fill(&list), FATAL_ERR_MSG);
  
  dli_print(&list);
  
  EXIT_ON_ERR(dli_free(&list), FATAL_ERR_MSG);*/

  dli slist;
  dli_init(&slist, sizeof(char) * 50, 25, print_str);
  dli_pseudo_str_fill(&slist);
  
  char *name = "Michael Jackson";
  char *name1 = "Benjamin Jackson";
  char *name2 = "Olaf Jackson";
  char *name3 = "Peter Jackson";
  dli_push(&slist, name);
  dli_push(&slist, name1);
  dli_push(&slist, name2);
  dli_push(&slist, name3);
  //dli_print(&slist);

  slist.print(dli_last(&slist));
  slist.print(dli_first(&slist));
  slist.print(dli_at(&slist, 26));
  
  dli_free(&slist);

  dli clist;
  dli_init(&clist, 1, 25, print_char); 
  for (int i = 0; i < 25; ++i)
  {
    char c = 'a' + i;
    dli_push(&clist, &c);
  }
  dli_print(&clist);
  
  dli_free(&clist);
}

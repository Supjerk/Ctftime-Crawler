#include <stdio.h>
#include "../src/ctfc.h"

int main(void) {
  char* str=DNSLookUp("www.ctftime.org");

  printf("IP: %s\n", str);
  printf("inet_addr: %d\n", inet_addr(str));

  return 0;
}


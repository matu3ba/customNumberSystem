#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// base is base of number system
// mem[] is the number in the base number system
// lenmem is length of buffer mem[]

// NOTE
// - C has no testing
// - C has no type to annotate the length to a  buffer
// - C enum members can not be scoped
// - C has no optionals (to prevent null)
// - C has no error types (or language support for error handling)

//assume base >= 0
bool isValidNumber(int mem[], int lenmem, int base)
{
  for (int index =0; index<lenmem; index+=1)
  {
    if(mem[index] >= base)
      return false;
  }
  return true;
}
bool isNotNull(int mem[], int lenmem)
{
  for(int index=0; index<lenmem; index+=1)
  {
    if (mem[index] != 0)
      return true;
  }
  return false;
}

int add(int mem[], int lenmem, int base)
{
  bool carry = false;
  int index;
  for (index = lenmem-1; index>=0; index-=1)
  {
    if (mem[index] + 1 == base)
      carry = true;
    else
    {
      mem[index] +=1;
      break;
    }
  }
  if (index == -1 && carry == true)
    return 1; // could not increase anymore
  if (carry == true)
  {
    assert(index < lenmem-1);
    index += 1; // zero out numbers right of the index
    for (index=index; index<lenmem; index+=1)
    {
      mem[index] = 0;
    }
  }
  return 0; // all good, did increase number
}
int sub(int mem[], int lenmem, int base)
{
  bool carry = false;
  int index;
  bool is_non_null = isNotNull(mem, lenmem);
  if (is_non_null == false)
    return 1;
  carry = false;
  if (mem[lenmem-1] > 0)
  {
    mem[lenmem-1] -= 1;
    return 0;
  }
  for (index = lenmem-1; index>=0; index-=1)
  {
    if (mem[index] == 0)
      mem[index] = base - 1;
    else
    {
      mem[index] -=1;
      break;
    }
  }
  return 0;
}

int main() {
  int base = 2;
  int start = 0;
  int lenmem = 5;
  int *mem = calloc(sizeof(int), lenmem);
  if(mem == NULL)
  {
    printf("out of memory\n");
    return -5;
  }
  for (int i=0;i<lenmem; i+=1)
    mem[i] = 1;
  bool is_valid_num = isValidNumber(mem, lenmem, base);
  if (is_valid_num == false)
  {
    printf("invalid num according to base in mem\n");
    return -1;
  }
  if (mem == NULL)
    return -1; // error handling with global enums only :(
  if (lenmem == 0)
    return -2;
  if (base <= 0)
    return -3;

  for(int i=0; i<lenmem; i+=1)
    printf("%d, ", mem[i]);
  printf("\n");
  int ret = add(mem, lenmem, base);
  if (ret == 1)
      printf("overflow\n");
  printf("\n");
  for(int i=0; i<lenmem; i+=1)
    printf("%d, ", mem[i]);
  printf("\n");
  ret = sub(mem, lenmem, base);
  if (ret == 1)
      printf("underflow\n");
  printf("\n");
  for(int i=0; i<lenmem; i+=1)
    printf("%d, ", mem[i]);
  return 0;
}

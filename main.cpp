#include <cassert>
#include <iostream>
#include <vector>

//assume base >= 0
bool isValidNumber(std::vector<int> &mem, int base)
{
  for (int index = 0; index < mem.size(); index+=1)
    if(mem[index] >= base)
      return false;
  return true;
}

bool isNotNull(std::vector<int> &mem)
{
  for(int index=0; index<mem.size(); index+=1)
    if (mem[index] != 0)
      return true;
  return false;
}

int add(std::vector<int> &mem, int base)
{
  bool carry = false;
  int index;
  for (index = mem.size()-1; index>=0; index-=1)
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
    assert(index < mem.size()-1);
    index += 1; // zero out numbers right of the index
    for (index=index; index<mem.size(); index+=1)
    {
      mem[index] = 0;
    }
  }
  return 0; // all good, did increase number
}

int sub(std::vector<int> &mem, int base)
{
  bool carry = false;
  int index;
  bool is_non_null = isNotNull(mem);
  if (is_non_null == false)
    return 1;
  carry = false;
  if (mem[mem.size()-1] > 0)
  {
    mem[mem.size()-1] -= 1;
    return 0;
  }
  for (index = mem.size()-1; index>=0; index-=1)
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

int main()
{
  int base = 2;
  int start = 0;
  std::vector<int> mem;
  int len = 5;
  mem.resize(len); // capacity = 5 after this call
  // Out of Memory not handled here
  for (int i=0;i<len; i+=1)
    mem[i] = 1;

  bool is_valid_num = isValidNumber(mem, base);
  if (is_valid_num == false)
  {
    printf("invalid num according to base in mem\n");
    return -1;
  }
  if (base <= 0)
    return -3;

  for(int i=0; i<mem.size(); i+=1)
    printf("%d, ", mem[i]);
  printf("\n");
  int ret = add(mem, base);
  if (ret == 1)
      printf("overflow\n");
  printf("\n");
  for(int i=0; i<mem.size(); i+=1)
    printf("%d, ", mem[i]);
  printf("\n");
  for (int i=0; i<5; i+=1)
  {
    ret = sub(mem, base); // 7-5 = 2
    if (ret == 1)
        printf("underflow\n");
    printf("\n");
  }
  for(int i=0; i<mem.size(); i+=1)
    printf("%d, ", mem[i]);

  return 0;
}

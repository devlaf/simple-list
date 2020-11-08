#include <stdio.h>
#include "list.h"

static list* get_list_0_to_9()
{
  list* retval = list_init();
  
  for(int i=0; i<10; i++) {
    list_append(retval, i);
  }
  
  return retval;
}

static bool equal(int entry, int equals_what)
{
  return entry == equals_what;
}

static int add(int entry, int addend)
{
  return entry + addend;
}

static int copy_int(int entry)
{
  return entry;
}

static void sum_ints(int entry, int* sum)
{
  *sum += entry;
}

static void noop(int entry)
{
}

static bool example_list_contains()
{
  list* my_list = get_list_0_to_9();
  bool retval = list_contains(my_list, equal, 5) &&
                !list_contains(my_list, equal, 15);
  list_free(my_list);
  return retval;
}

static bool example_list_map_mutable()
{
  list* my_list = get_list_0_to_9();
  list_map_mutable(my_list, add, 10);
  bool retval = list_contains(my_list,  equal, 10) &&
                list_contains(my_list,  equal, 19) &&
                !list_contains(my_list, equal, 9);
  list_free(my_list);
  return retval;
}

static bool example_list_map_immutable()
{
  list* my_list = get_list_0_to_9();
  list* new_list = list_map_immutable(my_list, copy_int, add, 10);
  bool retval = list_contains(new_list, equal, 10) &&
                list_contains(new_list, equal, 19) &&
                list_contains(my_list,  equal, 0) &&
                list_contains(my_list,  equal, 9);
  list_free(my_list);
  return retval;
}

static bool example_list_filter_mutable()
{
  list* my_list = get_list_0_to_9();
  list_filter_mutable(my_list, noop, equal, 5);
  bool retval = list_contains(my_list,  equal, 5) &&
                !list_contains(my_list, equal, 0) &&
                !list_contains(my_list, equal, 9);
  list_free(my_list);
  return retval;
}

static bool example_list_filter_immutable()
{
  list* my_list = get_list_0_to_9();
  list* new_list = list_filter_immutable(my_list, copy_int, equal, 5);
  bool retval = list_contains(new_list, equal, 5) &&
                !list_contains(new_list, equal, 6) &&
                list_contains(my_list,  equal, 0) &&
                list_contains(my_list,  equal, 9);
  list_free(my_list);
  return retval;
}

static bool example_list_reduce()
{
  int sum = 0;
  list* my_list = get_list_0_to_9();
  list_reduce(my_list, sum_ints, &sum);
  list_free(my_list);
  return sum == 45;
}

int main (int argc, char** argv)
{
  return example_list_contains() &&
         example_list_map_mutable() &&
         example_list_map_immutable() &&
         example_list_filter_mutable() &&
         example_list_filter_immutable() &&
         example_list_reduce();
}

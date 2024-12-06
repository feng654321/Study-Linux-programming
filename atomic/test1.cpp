#include <iostream>

struct A {int a; int b;};

int main()
{
  std::cout << std::boolalpha << __atomic_is_lock_free(sizeof(A), NULL) << std::endl;

  A a1;
  A a2 = {.a=400, .b=800};

  __atomic_store(&a1, &a2, __ATOMIC_RELAXED);

  std::cout << a1.a << std::endl;
  std::cout << a1.b << std::endl;

  return 0;
}

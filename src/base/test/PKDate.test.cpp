#include <base/PKDate.hpp>
#include <iostream>

using namespace pekronus;
int
main(int argc, char** argv)
{
  PKDate d1(1,1,2018);
  std::cout << d1.day_num() << std::endl;
  std::cout << d1 << std::endl;
  d1.add_days(100);
  std::cout << d1 << std::endl;
}

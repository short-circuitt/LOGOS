#include <iostream>
#include <cstdlib>
//#include <climits>
 
int main()
{
    std::cout << "abs(+3) = " << std::abs(3) << '\n'
              << "abs(-3) = " << std::abs(-3) << '\n';

    std::cout << "min(+3,-3) = " << std::min(3,-3) << std::endl;
    std::cout << "min(+3.5,+3.4) = " << std::min(3.5,3.4) << std::endl;
 
//  std::cout << abs(INT_MIN)); // undefined behavior on 2's complement systems
}

#include "discrete_val.h"
#include <iostream>

// use this to test the abilities of the library
int main() {
	std::vector<double> a = {0.3, 0.7};
    std::vector<double> b = {0.2, 0, 0.8};

	discrete_value test_a(a, 1, 2);
    discrete_value test_b(b, 1, 3);

    //discrete_value test(-1, 3);
    //test.print();
    //test_a.sum_distrib(test_b).print();
    //test_a.max_distrib(test_b).print();
	//test_a.min_distrib(test_b).print();
    test_a.signed_min_abs_distrib(test_b).print();

    std::cout << test_a.signed_min_abs_distrib(test_b).get_val();

	return 0;
}

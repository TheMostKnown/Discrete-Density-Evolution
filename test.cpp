#include "discrete_val.h"
#include <iostream>

// use this to test the abilities of the library
int main() {
    // values must be in growing order!
	std::vector<std::pair<double, double>> a = {{-1, 0.3}, {2, 0.7}};
    std::vector<std::pair<double, double>> b = {{0, 0.2}, {5, 0.8}};

	discrete_value test_a(a);
    discrete_value test_b(b);

    //discrete_value test(2, 2);
    //test.print();
    //test_a.sum_distrib(test_b).print();
    //test_a.max_distrib(test_b).print();
	//test_a.min_distrib(test_b).print();
    test_a.signed_min_abs_distrib(test_b).print();

    std::cout << test_a.signed_min_abs_distrib(test_b).get_val();

	return 0;
}

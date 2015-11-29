#include <tuple>
#include <iostream>

#include "bind-tuple.hpp"

using namespace std;

double foo(const int x, const float y, const double z) {
	return x + y + z;
}

struct A {
	const double foo(const int x, const double y, const double z) const {
		return x + y + z;
	}
};

int main(void) {
	const auto a = A();

	cout << ext::bind(foo)(make_tuple(1, 1.2, 5.0)) << endl;
	cout << ext::bind(foo)(1, 1.2, 5.0) << endl;

	cout << ext::bindMethod(&A::foo)(a, make_tuple(1, 1.2, 5.0)) << endl;
	cout << ext::bindMethod(&A::foo)(a, 1, 1.2, 5.0) << endl;

	return 0;
}

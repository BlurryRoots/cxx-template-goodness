#include <iostream>

#define M_PI 3.1415f

// Compute J terms in the series expansion.  K is the loop variable.
template <int N, int I, int J, int K>
class SineSeries {
public:
	enum {
		go = ((K + 1) != J)
	};

	static constexpr float
	accumulate (void) {
		return
			1
			- (I * 2 * M_PI / N)
			* (I * 2 * M_PI / N)
			/ (2 * K + 2)
			/ (2 * K + 3)
			* SineSeries<N * go, I * go, J * go, (K + 1) * go>::accumulate ()
			;
	}
};
template <>
// Specialization to terminate loop
class SineSeries <0, 0, 0, 0> {
public:
	static constexpr float
	accumulate (void) {
		return 1;
	}
};

template <int N, int I>
class Sine {
public:
	static constexpr float
	sin (void) {
		return (I*2*M_PI/N) * SineSeries<N,I,10,0>::accumulate ();
	}
};

// Template 1
template <typename T>
struct StarCounter {
	static constexpr int
	get_value (void) {
		return 0;
	}

	static constexpr bool
	is_even (void) {
		return 0 == StarCounter<T>::get_value () % 2;
	}
};

// Template 2
template <typename U>
struct StarCounter <U*> {
	static constexpr int
	get_value (void) {
		return 1 + StarCounter<U>::get_value ();
	}

	static constexpr bool
	is_even (void) {
		return 0 == StarCounter<U*>::get_value () % 2;
	}
};

// Template 3
template <typename U>
struct StarCounter <const U> {
	static constexpr int
	get_value (void) {
		return 10 + StarCounter<U>::get_value ();
	}

	static constexpr bool
	is_even (void) {
		return 0 == StarCounter<const U>::get_value () % 2;
	}
};

typedef
	StarCounter<int>
	A
	;

typedef
	StarCounter<int******>
	B
	;

typedef
	StarCounter<const int***>
	C
	;

typedef
	StarCounter<const int**** const>
	D
	;

int
main (void) {
	std::cout
		// prints 1 matches 1
		<< A::get_value () << std::endl
		// prints 6 matches 2
		<< B::get_value () << std::endl
		// prints 12 matches 2 & 3
		<< C::get_value () << std::endl
		<< (C::is_even () ? "true" : "false") << std::endl
		// prints 140 matches 2 & 3
		<< D::get_value () << std::endl
		;

	float x = Sine<32,5>::sin ();
	std::cout << x << std::endl;

	return 0;
}

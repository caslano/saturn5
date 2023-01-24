// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_library_hpp_
#define boost_numeric_ublas_opencl_library_hpp_

#include <clBLAS.h>
#include <type_traits>
#include <complex>

namespace boost { namespace numeric { namespace ublas { namespace opencl {

class library
{
public:
  library() { clblasSetup();}
  ~library() { clblasTeardown();}
};

template <typename T>
struct is_numeric
{
  static bool const value =
    std::is_same<T, float>::value |
    std::is_same<T, double>::value |
    std::is_same<T, std::complex<float>>::value |
    std::is_same<T, std::complex<double>>::value;
};
	
}}}}

#endif

/* library.hpp
bsoMvKW9OwE8YD0/TfvRy7p0GqiZTL4ZYhlGhb7jGPT/bzcVBx/VC4Fr7zaMfBx0ZtumjsTfhsAKuw5YlG9sCWGuFWyYetoM+ua4r+8LKfNA/bVB3s6ZRg0gEcqNkeBBAmdrU+RTvq1UtlCOB6csOMQi4NZpTEs/zi8Ld/rcpN4McySbvtdfiuJcFu7x+WK6uP3UlKT71dXC39NDyjvERfM2ZnT4AsYAYPiDczoRdzvLqCHYdgAmmEK+2aApQpEAgHKjL3CpjVd788xNyK5ZS1zqWYeDHOeIvYOITfRsrTk4JSEH49p4G2zU/TXvgyI8x/UANHaBxqMI/7QTWiWp4ejka+EvFgH8VuZl4J9K09CmVuW4QDLwxZz397u3y42j8R7vHAf5zy+v7xhZmzsiE3LaKsZvc0hE0PTnebaobH5qutwFQsZf4BI7iy+8vY1oO4qOn3YMv/QQNR6ZY0YnU3J2gNvlTL4IJ89FBHZsizeBu320Q7S0d+E9wGcr7V1hF7UPjWoiGgauwGdpEQqkIus2OOGsJunV9G5exX6nvDuuJTCePXEaUs/ReYlP1B5D2ks07ye7TXK4RLyIWESyJ2/jgY+J08f3JMJdYl9QIw+6riyO36IBcL0hzSXjW5MuzSX6gtwAmO8/53wPHmoycNx6T0I0f4ZrT6Itn+q9CXlt+DXzoItePmgBGZvUZ72IjE2IbwKOiK+c25PQ
*/
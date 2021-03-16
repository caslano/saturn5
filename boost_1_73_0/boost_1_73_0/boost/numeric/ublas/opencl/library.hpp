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
x8jTSQ3vZJDfEorxY644a5BRfSjto50p1us8X+YEGwWptvgsD0Z0xpK/93gbeTV19zrkfBTpy8PrLmyKgMnD8gRbWwQwDei4k7e+SLw0g/QfT20LRW8ntbaVAvnxnZwgJVy/XZNs1SdURKPVVbXUgUarorU1bh+q4BWlE6LAa9kubIyCOS5szJgop83x8KKThku8XBdWW6rwjnJh0YkK1s2FTSxTsB4ePRc2QM9jhMzjFBdWXTWxllalJe7PXfg=
*/
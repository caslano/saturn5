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
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
*/
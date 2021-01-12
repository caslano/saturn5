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
Ta14R90KvgJNgKvz1gpf4R0uvwVvDqdfH/AVaDR+mbcRfPWEpmrfYQzTfNyuafEtfsigg+m87kh4nh/j2CNEzK+p0cykeVNq55d8yvw6HfPrQGT66dzETCVPWgF7ay2S++4c8qqFkny3LpxvJcPahptvbZS8NTyjNdDrtqGMYK6m+jv9szhli1Bn4HSkHRdzSvA0w4Nz6HrzzcspnwBh7WCYY+e7nGH2XgvrteRPh09+EViv
*/
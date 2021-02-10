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
L3Rlc3RzL2xpYnRlc3QvbGliNTc1LmNVVAUAAbZIJGCtVm1P4zgQ/p5fMctJq7YXmsJKp2PLra5bulBdaVFbDnFCitzYaXxy7Gzs0KJl//uNnaQtsEt1EkEQZ16eeWbGYxO03u7xoAV7n9D9hvjg23lc5epfFpkfW4fhI5Q/6HWH731BAti6PIZN2O/yCA3nElZRTu06DPcFurPc7J/Aet6FdokSdLOefZU95HyZGGj0m3B0cvI7HMJx57jjwxmRnAmYGSYXLF/6cEqd5M+ErNdtzT75wAwQ0a6g5gnXoFVsViRngGvBIyY1o0A0UKajnC/wg0swCYOYCwb9ydXtcHzuwyrhUWJBHlQBOlGFoJCQewY5ixi/LzEykhtQMbojOOXaIGBhuJJtjM3AsDzVFsOGJ0IrIPeEC7LAQMRAYkymPwZBVOQC2QdURTqI6vTbiUk3mdwiiZQ8gMoMGAWFZj5YSx9SRXls31gQFGbFQnCd+Fs2GErSQOWgmRAWC/040yVtBrOqPL41gwwZc2NfWkltQ60SlT4xxDpalLjIJQbCOqARVVhmHwpJWe6MXeZ1iKqmrsA/bc2WLwUlkQwc9GYwnB3AgmiufbgZzi8m13O46U2nvfH8FiZfoDe+tWB/Dcdn2HqOwXJg6yxn
*/
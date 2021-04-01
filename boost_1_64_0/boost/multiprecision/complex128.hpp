///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_COMPLEX128_HPP
#define BOOST_MP_COMPLEX128_HPP

#include <boost/multiprecision/float128.hpp>
#include <boost/multiprecision/complex_adaptor.hpp>

namespace boost {
namespace multiprecision {

typedef number<complex_adaptor<float128_backend>, et_off> complex128;

template <>
struct component_type<number<complex_adaptor<float128_backend> > >
{
   typedef float128 type;
};

}
} // namespace boost::multiprecision

#endif

/* complex128.hpp
iZ49uHPvwzcrPPfKgJL7aT949z6ibdXdmu58cLtvF690Slx/Doc7lBacnke736A6tfZ71SGMQD8TETTtopkWEg8EHCmhQsS/vfwzgPIRKq/sAJfjq3UjHg5EmlMVHdPndB+Fn6EQwjikeyHIMUVQDRslS0s4RApGlxO//XuTGOXhQgxx68JQgTg/Fe1hh1Zi1VMPbt08WKF6m9wlNB06T4fgfvasLFzxg/Uoz6t/JaQ0ip1qDUp+ez3qFpsSPKz8Vs6MHQL05fS1TXe0AgOD7WiRzWaJSpEYUxk04DWLkp/N42qYGVLOS+YlGyxkvkrJQds6Z2O/vBybtb6dQnmnmk0axTf8bHOH4TCvAyHOFvu2n4EXW2cL+bO1mKyUVGwwkeTLBmHcL+44QGVXG6Kfrkx7/jk+M8scQ6TgDYBcPfFxogCcPboE8PZDg46QCOd+uGlb1USejopSJWIr/LN/k83IRCgY4s+MHcThIUwrmd38sQlNs1vkm/0TYU4duXy6xshoHZmOAjELmlpH7cXiqyjV9/gAsMJ7p1OvY8V+k18uUwd7nRZAC0M58w==
*/
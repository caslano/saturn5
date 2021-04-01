//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_3_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_3_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_3.hpp
9dSCwwb5dLL30+Hp+968WrNQjxFOw1bHsZHGnBXTKQGw1/m1XEWfa1136DhqYZBUEGbhDHdi5uJgOaCkrvTc0+Yw8qdj9vrdJmXstCTknJxwAg4XT71jexvMiXT7hGz+UsEXm1DLCwu2UAUIZXYMRPJNn8PV9SFzaDMEjsTVnok6eBkn85sH3dB7hpShbQud/rGIOV+ivkRxsEyC5tATf7Ww7QZqkK5Me5yioAbo1VSIFtP0OCytYDS7AHRjDeJ+ha3JqS1lcEKZPR8CK/W9jR3lHypbbRQGz1UDD0gaN3XvbRt6aHOVGmVn7QisZujFGJoel7jYbGDz8egzf0w3nC+dJbjI4enFh1F4p68qI/5KRlVej6ePoujI+wLsrdSMbHu6FLgZliBqnzqhK0nSCdlbYUZTc6juqUaZQA2zQqqCXc0GYIIo12eJhn61+dsMH+eMIfZ2TNCbVwkwdpBRMCO/ePhBZXRSuMzfXxqEQHPt9lePH/mCq+9VbobkA4aqLQlEV04tX8LFi4oib5I7d3YSqqX+uOc4RXLKRLwHAmi4AU1wpzLba057uw==
*/
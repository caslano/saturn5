///////////////////////////////////////////////////////////////////////////////
//  Copyright 2016 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_MIN_MAX_HPP
#define BOOST_MP_MIN_MAX_HPP

#include <boost/multiprecision/traits/is_backend.hpp>

namespace boost { namespace multiprecision {

//
// Expression template overloads for (min) and (max):
//
// Introduced in response to https://svn.boost.org/trac/boost/ticket/11149
// note that these can not legally be injected into namespace std, and that doing so
// may break future enhancements to the standard.  None the less adding
// namespace std{ using boost::multiprecision::(min); using boost::multiprecision::(max); }
// to your code may get some generic code working that wouldn't work otherwise.
//
// The use of enable_if on the return type is to avoid poisoning std::min/max,
// otherwise attempting to make an explicit call to min<long>(a, b) when these and std
// versions are in scope, will cause the compiler to try to instantiate the signatures
// for our versions as well as the std ones, which in turn instantiates number<long>
// which fails to compile as "long" is not a valid backend type.
//
template <class Backend>
inline typename boost::enable_if_c<boost::multiprecision::detail::is_backend<Backend>::value, const number<Backend, et_on>&>::type(min)(const number<Backend, et_on>& a, const number<Backend, et_on>& b)
{
   return a < b ? a : b;
}
template <class Backend, class tag, class A1, class A2, class A3, class A4>
inline typename boost::enable_if_c<boost::multiprecision::detail::is_backend<Backend>::value, const number<Backend, et_on> >::type(min)(const number<Backend, et_on>& a, const detail::expression<tag, A1, A2, A3, A4>& b)
{
   number<Backend, et_on> t(b);
   if (a < t)
      return a;
   return BOOST_MP_MOVE(t);
}
template <class tag, class A1, class A2, class A3, class A4, class Backend>
inline typename boost::enable_if_c<boost::multiprecision::detail::is_backend<Backend>::value, const number<Backend, et_on> >::type(min)(const detail::expression<tag, A1, A2, A3, A4>& a, const number<Backend, et_on>& b)
{
   number<Backend, et_on> t(a);
   if (t < b)
      return BOOST_MP_MOVE(t);
   return b;
}
template <class tag, class A1, class A2, class A3, class A4, class tagb, class A1b, class A2b, class A3b, class A4b>
inline typename detail::expression<tag, A1, A2, A3, A4>::result_type(min)(const detail::expression<tag, A1, A2, A3, A4>& a, const detail::expression<tagb, A1b, A2b, A3b, A4b>& b)
{
   typename detail::expression<tag, A1, A2, A3, A4>::result_type t1(a), t2(b);
   if (t1 < t2)
      return BOOST_MP_MOVE(t1);
   return BOOST_MP_MOVE(t2);
}
template <class tag, class A1, class A2, class A3, class A4>
inline typename detail::expression<tag, A1, A2, A3, A4>::result_type(min)(const detail::expression<tag, A1, A2, A3, A4>& a, const detail::expression<tag, A1, A2, A3, A4>& b)
{
   typename detail::expression<tag, A1, A2, A3, A4>::result_type t1(a), t2(b);
   if (t1 < t2)
      return BOOST_MP_MOVE(t1);
   return BOOST_MP_MOVE(t2);
}

template <class Backend>
inline typename boost::enable_if_c<boost::multiprecision::detail::is_backend<Backend>::value, const number<Backend, et_on>&>::type(max)(const number<Backend, et_on>& a, const number<Backend, et_on>& b)
{
   return a > b ? a : b;
}
template <class Backend, class tag, class A1, class A2, class A3, class A4>
inline typename boost::enable_if_c<boost::multiprecision::detail::is_backend<Backend>::value, const number<Backend, et_on> >::type(max)(const number<Backend, et_on>& a, const detail::expression<tag, A1, A2, A3, A4>& b)
{
   number<Backend, et_on> t(b);
   if (a > t)
      return a;
   return BOOST_MP_MOVE(t);
}
template <class tag, class A1, class A2, class A3, class A4, class Backend>
inline typename boost::enable_if_c<boost::multiprecision::detail::is_backend<Backend>::value, const number<Backend, et_on> >::type(max)(const detail::expression<tag, A1, A2, A3, A4>& a, const number<Backend, et_on>& b)
{
   number<Backend, et_on> t(a);
   if (t > b)
      return BOOST_MP_MOVE(t);
   return b;
}
template <class tag, class A1, class A2, class A3, class A4, class tagb, class A1b, class A2b, class A3b, class A4b>
inline typename detail::expression<tag, A1, A2, A3, A4>::result_type(max)(const detail::expression<tag, A1, A2, A3, A4>& a, const detail::expression<tagb, A1b, A2b, A3b, A4b>& b)
{
   typename detail::expression<tag, A1, A2, A3, A4>::result_type t1(a), t2(b);
   if (t1 > t2)
      return BOOST_MP_MOVE(t1);
   return BOOST_MP_MOVE(t2);
}
template <class tag, class A1, class A2, class A3, class A4>
inline typename detail::expression<tag, A1, A2, A3, A4>::result_type(max)(const detail::expression<tag, A1, A2, A3, A4>& a, const detail::expression<tag, A1, A2, A3, A4>& b)
{
   typename detail::expression<tag, A1, A2, A3, A4>::result_type t1(a), t2(b);
   if (t1 > t2)
      return BOOST_MP_MOVE(t1);
   return BOOST_MP_MOVE(t2);
}

}} // namespace boost::multiprecision

#endif

/* min_max.hpp
rnewrvU+KRjLK2aNqvqA1fUU7D8ISxJFrTWxTFDHD2s867NzQENt+E2Mx017IfEK8PrehTc9hJdIiFJGXjTmVo8uco4MPqQYVwXvOTUUcPseBx+ooU25S4oZYaHzTj53fHk1j/P6V6RHiQ48OK0NqSPsU22AfQrNu/X5Z2hXTqOnyqUJD1xXAXLtZ/7C12JMFRXPXFOMCXOOgm1wr7fDaeAlM9UQ4eHcTGeHm73snpDNQkMG8uX7Jxen52dnp9MSCX5VvXwhhkfLmGTk6H714aafuzju8lmDjRXCKNw4lYIlS9/g84tZLo9P9vLvsbm2NPMLv0T0xgHy91H5TrNUjJ7Kr4v9WP4VKr92pKGc8+ZCgt5B3qCmu4lenkuiOM2sVmuxcemzmlz+9nZ9cd7b216tNfCHN+sNXmd7iHB9soFGBz5CwGvPTd/OCNeQFi6lMM2Jzvv36nHq7s7t7bsT8s4CeQf/VZdfE2E7xowrTIE/0IR9C+6xEDYngdOihf/vOO+tce//7ml9WwvnnKKWwAfJyPnG63pcRQrVzOj8f3E2r0PjqFDVvqYbZ/SueAu+V3v5vWhzneBK1C/dT32ucoOHYZD/PuIWZe1Dlim4MEH58I7wuiGGqZCssJjm3ABrB8Ys4lJscJbrtdvTDOvrCEsSWavmhbaL/jORctyHONdrz2tXSa88Vw54TWvINsSNQliCMOOD9kmThrPqHkwN5xL5Sa+/GxxnIWUP3Ca8u2ADiOR9LDQyXkjrpK2bN8G+CORfg+62okvSUkGskBSNwbvwvoz4cGJZM6K2uJvaOF+jEbhbwlx4ocrxhdfAQT/o7kIuq17+Diuu6FLbuh9wcA/1D1Q2481Y2OWJCCwgwOMprx/8wjNvTNKcCHQKgXuo1+M2zjzSkCYesGDcnHi8ppe/40MRJnCx4LG7N/B4Cypb1L6T0bsVj/UCfxO+VXr5TEr2JgURVjS2dm9t1420ooz3dgLh2CK5StavOMBCv87BW14/+Bbo7HUpKxKV9sN5vv1Sx1bviyGUlLrev3GwtcDyn0Z1cjxJnRRvEC2c0cHh2A+nr0frNqcq8WTqPSuyx+higYA8xC3SVDo2NlZ3WQFY38ZY0hpJY2hc0L67B7muEBYjwVmbKG1JmD97d69RuoAFZmyHnyAsX4JJ2qTGq+uaLgfozxGWbO9swbHENu8L5cNqFbcM7ogRXjDcpFTiqp8Um62ffx7wMvPScce6/Q+WAGGG3NQIy0ZmZJC+cUN77R7E2XzDcF/sC00l+GsWnJ0R7zVvQHtDamcEKSs3/N55E2xC3jDapUUhVPKYW2tJYcazk0BYUUdWZOFLbmcbuBWEJUjQnuZQwsY1qDIbvwHv9/q3Hc2Wc7fwR8NvWadvwOeGGH1O0q45wciv/b04GJZ68Nyrh9Z4fFnv4Sa872G8xEQuuTQfsSWem8Y+wqPNYI1KLfUmvJYXdoK6vw4YBv33S9SmPNY+MzSA+yC0qZrsPlCbJiJK4Fxkuelsdq9+zZSDGn9n//hqfKf4xzDughU2yaQa22vu9g8gTsMb8flQZONCZHZeh669VxXp42/t9uVE0lZ2akSBw0a3igJ/80bMX3unWIh23vab+UMcBowtfTBRyPWhClbYDvtrVQedT5WMgfr0hHFWe7LVoovn0J+xEolBKJl0f8gC4jDGfzRg6zbGtY9PwGYj9m/7chJRhRupve4OXEAcsP8yYPvEKXX6Sdh8wgZ/gzf1Yz0blYLgqdGGtQqN9RtvwrhWssBiLk/AFSOuQbipDlVee61RhnUL4d5DuInIutk4wZ7EN18eHtS4Sp0/W1/OrrLK6cz16qwDhNe43xtwrXVCxvQ=
*/
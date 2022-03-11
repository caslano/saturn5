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
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
*/
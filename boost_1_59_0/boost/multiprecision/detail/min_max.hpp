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
inline typename std::enable_if<boost::multiprecision::detail::is_backend<Backend>::value, const number<Backend, et_on>&>::type(min)(const number<Backend, et_on>& a, const number<Backend, et_on>& b)
{
   return a < b ? a : b;
}
template <class Backend, class tag, class A1, class A2, class A3, class A4>
inline typename std::enable_if<boost::multiprecision::detail::is_backend<Backend>::value, const number<Backend, et_on> >::type(min)(const number<Backend, et_on>& a, const detail::expression<tag, A1, A2, A3, A4>& b)
{
   number<Backend, et_on> t(b);
   if (a < t)
      return a;
   return std::move(t);
}
template <class tag, class A1, class A2, class A3, class A4, class Backend>
inline typename std::enable_if<boost::multiprecision::detail::is_backend<Backend>::value, const number<Backend, et_on> >::type(min)(const detail::expression<tag, A1, A2, A3, A4>& a, const number<Backend, et_on>& b)
{
   number<Backend, et_on> t(a);
   if (t < b)
      return std::move(t);
   return b;
}
template <class tag, class A1, class A2, class A3, class A4, class tagb, class A1b, class A2b, class A3b, class A4b>
inline typename detail::expression<tag, A1, A2, A3, A4>::result_type(min)(const detail::expression<tag, A1, A2, A3, A4>& a, const detail::expression<tagb, A1b, A2b, A3b, A4b>& b)
{
   typename detail::expression<tag, A1, A2, A3, A4>::result_type t1(a), t2(b);
   if (t1 < t2)
      return std::move(t1);
   return std::move(t2);
}
template <class tag, class A1, class A2, class A3, class A4>
inline typename detail::expression<tag, A1, A2, A3, A4>::result_type(min)(const detail::expression<tag, A1, A2, A3, A4>& a, const detail::expression<tag, A1, A2, A3, A4>& b)
{
   typename detail::expression<tag, A1, A2, A3, A4>::result_type t1(a), t2(b);
   if (t1 < t2)
      return std::move(t1);
   return std::move(t2);
}

template <class Backend>
inline typename std::enable_if<boost::multiprecision::detail::is_backend<Backend>::value, const number<Backend, et_on>&>::type(max)(const number<Backend, et_on>& a, const number<Backend, et_on>& b)
{
   return a > b ? a : b;
}
template <class Backend, class tag, class A1, class A2, class A3, class A4>
inline typename std::enable_if<boost::multiprecision::detail::is_backend<Backend>::value, const number<Backend, et_on> >::type(max)(const number<Backend, et_on>& a, const detail::expression<tag, A1, A2, A3, A4>& b)
{
   number<Backend, et_on> t(b);
   if (a > t)
      return a;
   return std::move(t);
}
template <class tag, class A1, class A2, class A3, class A4, class Backend>
inline typename std::enable_if<boost::multiprecision::detail::is_backend<Backend>::value, const number<Backend, et_on> >::type(max)(const detail::expression<tag, A1, A2, A3, A4>& a, const number<Backend, et_on>& b)
{
   number<Backend, et_on> t(a);
   if (t > b)
      return std::move(t);
   return b;
}
template <class tag, class A1, class A2, class A3, class A4, class tagb, class A1b, class A2b, class A3b, class A4b>
inline typename detail::expression<tag, A1, A2, A3, A4>::result_type(max)(const detail::expression<tag, A1, A2, A3, A4>& a, const detail::expression<tagb, A1b, A2b, A3b, A4b>& b)
{
   typename detail::expression<tag, A1, A2, A3, A4>::result_type t1(a), t2(b);
   if (t1 > t2)
      return std::move(t1);
   return std::move(t2);
}
template <class tag, class A1, class A2, class A3, class A4>
inline typename detail::expression<tag, A1, A2, A3, A4>::result_type(max)(const detail::expression<tag, A1, A2, A3, A4>& a, const detail::expression<tag, A1, A2, A3, A4>& b)
{
   typename detail::expression<tag, A1, A2, A3, A4>::result_type t1(a), t2(b);
   if (t1 > t2)
      return std::move(t1);
   return std::move(t2);
}

}} // namespace boost::multiprecision

#endif

/* min_max.hpp
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
*/
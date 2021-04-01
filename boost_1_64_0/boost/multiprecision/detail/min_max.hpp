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
xTrfxFOCYGCpj1XtiydE0HEq+c3D7y5vfNYmnMTOaJnsyNjxwEXoVw2z3oH23y16EtHnJF/+iERkwitDC1FN56KCY14yl6ZB8ieqgKs0rR1Qp60gdVUcJNDPM1CDQPrliTfQ7RWusYfdT1DCcVd2Z4aPGvJGLa6eF29WNUPnVv98LVAmNweo8NOlXP2weyc7HGJXkCz+6HwkGp5/EKPygKGZmuB1aXuPqhwldRm+gsBugj0kWBeJUS3M+RV5hOhmoeXXTmeld5uJ1/K4gOQOXBHev28jsvb5TG87AgN6I+nNHnGJl2h8XCsTup6aOiU7ZCSKSP9c2OnymXz486A2TtK/OLBNQDIPn2Hu8pKPM5A9gir2ofmQZTyc99dhb3xBRg9jSstP83pOuocGgqdlJWwINez3/BUqjRYkihqAt2fUoEvjqBXxf4Ff157UN9P3zqxzXjZ2IcqehE6tMCrWhUmtJxD9MFjrpUeu6aBoT8/jwI5Ji1eX7mwqhZiJAco4AkpH/wg8Eu4M0TvHWX46VvF/Pgqe5v1FvgOhqMKvPM9RS9wGZyg5SedfPA==
*/
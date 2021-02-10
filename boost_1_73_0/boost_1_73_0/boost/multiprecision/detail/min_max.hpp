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
sOsLBR+KK3rmW8n8hAXfvpxzUphWT+JULrYwM6fb7RlUmNDawQ2yocUO6xwTmlrqyEsr3TAMFjp2PPDOXdKZu/RlY+Ngd31jYzxY71HEGfJRr9s62Dvubh90gDLdvV+7Pby26V37aFeXHGGtEqpgYQnAMw+sE8r7wTkYqBgeOA3TKeEWP4NJQkiQkivyljqEqS7OUgt18xDYV9NAlCR3cQ0kQpAAj2T2maeJ5hzuMhWSM87XSJoysaP9n6VM1E1dujJB8bTGMSelaS2H5cy13ENR9+4EWDvyzr/nRWU9XijTirqNTe+vfoAt0+ekBvVZlk36vaiQ2hFSF7vpCEHD3sC2HNEDuLEMD7g1A1nMA+9fKpJliUMcXyYGRTHQzEMbfyVAZdYhjYUOaOTs2NLgG2ycYbEDbDMOHT8a4nondsLYUH2zlJBNAamc0e48xUO95VqnykAWpuOEc2QyfSpzFgyusVLE4TkUjvsw2536TPFQdzCKDiSJexx2NvVGcY1m1g9uTbpMUTMaMmMu4ZusubqaXoavsadrz58+f/bdU/nu/6ywl+wpe/1TUugJWzNqpv1c+lBruMxSFEKJ3+H43WbiWGI41K2ZudrKIElSnIe5YMH0hCFq392MQXO5HqQpBeqvzBvq5sw8o1v1
*/
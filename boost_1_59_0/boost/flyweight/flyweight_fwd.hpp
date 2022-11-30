/* Copyright 2006-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_FLYWEIGHT_FWD_HPP
#define BOOST_FLYWEIGHT_FLYWEIGHT_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/templated_streams.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/parameter/parameters.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <iosfwd>

#if !defined(BOOST_FLYWEIGHT_DISABLE_HASH_SUPPORT)
#include <boost/functional/hash_fwd.hpp>
#include <cstddef>
#endif

namespace boost{
  
namespace flyweights{

template<
  typename T,
  typename Arg1=parameter::void_,
  typename Arg2=parameter::void_,
  typename Arg3=parameter::void_,
  typename Arg4=parameter::void_,
  typename Arg5=parameter::void_
>
class flyweight;

#define BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(n)            \
typename Arg##n##1,typename Arg##n##2,typename Arg##n##3, \
typename Arg##n##4,typename Arg##n##5
#define BOOST_FLYWEIGHT_TEMPL_ARGS(n) \
Arg##n##1,Arg##n##2,Arg##n##3,Arg##n##4,Arg##n##5

template<
  typename T1,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1),
  typename T2,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2)
>
bool operator==(
  const flyweight<T1,BOOST_FLYWEIGHT_TEMPL_ARGS(1)>& x,
  const flyweight<T2,BOOST_FLYWEIGHT_TEMPL_ARGS(2)>& y);

template<
  typename T1,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1),
  typename T2,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2)
>
bool operator<(
  const flyweight<T1,BOOST_FLYWEIGHT_TEMPL_ARGS(1)>& x,
  const flyweight<T2,BOOST_FLYWEIGHT_TEMPL_ARGS(2)>& y);

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
template<
  typename T1,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1),
  typename T2
>
bool operator==(
  const flyweight<T1,BOOST_FLYWEIGHT_TEMPL_ARGS(1)>& x,const T2& y);

template<
  typename T1,
  typename T2,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2)
>
bool operator==(
  const T1& x,const flyweight<T2,BOOST_FLYWEIGHT_TEMPL_ARGS(2)>& y);

template<
  typename T1,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1),
  typename T2
>
bool operator<(
  const flyweight<T1,BOOST_FLYWEIGHT_TEMPL_ARGS(1)>& x,const T2& y);

template<
  typename T1,
  typename T2,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2)
>
bool operator<(
  const T1& x,const flyweight<T2,BOOST_FLYWEIGHT_TEMPL_ARGS(2)>& y);
#endif /* !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) */

#define BOOST_FLYWEIGHT_COMPLETE_COMP_OPS_DECL(t,a1,a2)                       \
template<t>                                                                   \
inline bool operator!=(const a1& x,const a2& y);                              \
                                                                              \
template<t>                                                                   \
inline bool operator>(const a1& x,const a2& y);                               \
                                                                              \
template<t>                                                                   \
inline bool operator>=(const a1& x,const a2& y);                              \
                                                                              \
template<t>                                                                   \
inline bool operator<=(const a1& x,const a2& y);                              \

BOOST_FLYWEIGHT_COMPLETE_COMP_OPS_DECL(
  typename T1 BOOST_PP_COMMA()
  BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1) BOOST_PP_COMMA()
  typename T2 BOOST_PP_COMMA()
  BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2),
  flyweight<
    T1 BOOST_PP_COMMA() BOOST_FLYWEIGHT_TEMPL_ARGS(1)
  >,
  flyweight<
    T2 BOOST_PP_COMMA() BOOST_FLYWEIGHT_TEMPL_ARGS(2)
  >)

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
BOOST_FLYWEIGHT_COMPLETE_COMP_OPS_DECL(
  typename T1 BOOST_PP_COMMA()
  BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1) BOOST_PP_COMMA()
  typename T2,
  flyweight<
    T1 BOOST_PP_COMMA() BOOST_FLYWEIGHT_TEMPL_ARGS(1)
  >,
  T2)

BOOST_FLYWEIGHT_COMPLETE_COMP_OPS_DECL(
  typename T1 BOOST_PP_COMMA()
  typename T2 BOOST_PP_COMMA()
  BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2),
  T1,
  flyweight<
    T2 BOOST_PP_COMMA() BOOST_FLYWEIGHT_TEMPL_ARGS(2)
  >)
#endif /* !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) */
  
template<typename T,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(_)>
inline void swap(
  flyweight<T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)>& x,
  flyweight<T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)>& y);

template<
  BOOST_TEMPLATED_STREAM_ARGS(ElemType,Traits)
  BOOST_TEMPLATED_STREAM_COMMA
  typename T,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(_)
>
inline BOOST_TEMPLATED_STREAM(ostream,ElemType,Traits)& operator<<(
  BOOST_TEMPLATED_STREAM(ostream,ElemType,Traits)& out,
  const flyweight<T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)>& x);

template<
  BOOST_TEMPLATED_STREAM_ARGS(ElemType,Traits)
  BOOST_TEMPLATED_STREAM_COMMA
  typename T,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(_)
>
inline BOOST_TEMPLATED_STREAM(istream,ElemType,Traits)& operator>>(
  BOOST_TEMPLATED_STREAM(istream,ElemType,Traits)& in,
  flyweight<T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)>& x);

} /* namespace flyweights */

using flyweights::flyweight;

} /* namespace boost */

#if !defined(BOOST_FLYWEIGHT_DISABLE_HASH_SUPPORT)
#if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)

#if BOOST_WORKAROUND(_CPPLIB_VER,==520)
/* Dinkumware 5.20 defines std::hash as class rather than struct */
#define BOOST_FLYWEIGHT_STD_HASH_STRUCT_KEYWORD class
#else
#define BOOST_FLYWEIGHT_STD_HASH_STRUCT_KEYWORD struct
#endif

#if !defined(_LIBCPP_VERSION)
namespace std{
template <class T> BOOST_FLYWEIGHT_STD_HASH_STRUCT_KEYWORD hash;
}
#else 
/* As discussed in http://lists.boost.org/Archives/boost/2011/02/177218.php */
#include <functional>
#endif

namespace std{

template<typename T,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(_)>
BOOST_FLYWEIGHT_STD_HASH_STRUCT_KEYWORD
hash<boost::flyweight<T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)> >;

} /* namespace std */
#endif /* !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL) */

namespace boost{
#if !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
namespace flyweights{
#endif

template<typename T,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(_)>
inline std::size_t hash_value(
  const flyweight<T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)>& x);

#if !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
} /* namespace flyweights */
#endif
} /* namespace boost */
#endif /* !defined(BOOST_FLYWEIGHT_DISABLE_HASH_SUPPORT) */

#undef BOOST_FLYWEIGHT_COMPLETE_COMP_OPS_DECL
#undef BOOST_FLYWEIGHT_TEMPL_ARGS
#undef BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS

#endif

/* flyweight_fwd.hpp
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
*/
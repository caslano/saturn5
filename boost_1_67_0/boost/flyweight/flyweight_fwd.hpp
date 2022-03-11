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
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
Y135ND4fAwpytJI4ujzbgqPxkTh60wUCyzIYb9TvtqLMDTGTKjurkbu9LNL4fcntRgk2EKi1S9uReWQhb2o57Ihn6sqpsLI2d6WkuXpXwyogcCe0J1RSS7naqhcenMstuYRZfQW29DJWqT3zSS97I8Og9YP3DJZVWQAeqfyuGIQd0gFAxno5VXFG2ownNEhVfl1cnCiSE4s0EpqRFPNxyZlnq+yCpsHUbW9Uuu071G3fOZF127NHQLcdCOIIh7LLqvqBJC8phWVL+r3NNXDkXBLBrgetTOgVdeiogaFDTk1n6g398Bw2vk8S3ikIoQaBx/qGlQ/ifjqG4dQjsNzaCKBPb2S/JAiP0Qn/kQhnWhLOLk/mhLORMKuf1FXX885WqDqPNhaw9lzWws8hr6n3rWfekNxfUguvG27Rws8FOcX6i3ZUv+hZP4b5XtmOBBq2m1crGGQcgZVe6mdHpAj2rjlsQ64LsZNB7BSxD3w6QcRDnP7lTF/EUF5xx3a2ucz7odvwfRn0XNJyQliOLWu90rIyklnLqhrGWtZIqBZtD+wFIpShZR3BlkVZ0vfRTj+RFd6L8z/8LYd8y22V3fCPA1QxKbK++sE1PsIpeDcIE0E7fJtleo/thj2WlXwRwC7C+3M/+QHw+C0s/l4StLSjXLzXY5EcFXD9vYPz2ehEPo2fgqgKk2uZe+rKI/aWY8pfZ9GYYvE1sepuU6rOS1U3dSiruhOhBrW1ICcQFFVdBBng8tl89KFqGSoGofK++eLsRrGs56leBCZNKbhVBPK6LQiFmWk2Sf+lA5TPBZW3klVekjK9Nt8A9zTIdlmstTsHCNCrkcnTZ7H+Mx17zdnJrNfMGWLRa/qXxNRremG2sgVTi5+Eem7jt2oQ5a5Zge/UW85qR/3MCIs1K2upT3elNZI6md+KY6vM4CFjswx8BxLy7+A/qoelM1s2hgdmygmmBJvA8vNQ6I0rzeJjmFsIOdSGO0pu1nJuCHywRWPqauhL9qEG7tcQ9/jH7k/mIYc/OdSRtAOL7GzinW/Rfr8928hyZX9qhLnbu0FyXgD2CWSuL50DtNLtckierQ/JaeewIXkqT+lhEPLoRKkHbXnKJfncFuQvRvLoF5suBRlrZjX/bEg6ZC91CxKdWpAYDCRCVxK+BOvcAsyBYGe1HO0qJI6jBc4rMwGnt0jv0iL9IUj/RXP2y++Xn0GfZd507lapOH2k9RrzeFeahVEQUz7A5mBrvO47MuVxuo5nSUXCqTTl1XJtkU/rdT0TlAYjvhvGGFdpe/KZ12tHd0lg75lIoO1njiPd/1nRwotitnbFOr7rb+k60YmnwWO9X/dguV5Lcn6lJUWmqDooa6ZtOdf/4o0JVs4JA4CAu42ptShjoIrNQDNjBj9+yPa2KkfLXUivtiCd1Vi/3O1TcKxDkkpqwwxZn9Mxj3Aj83yoEhjeXxDIsyCwXCeQ2JwPdXi0X2VPTPq/q62vvaE6E4otNNOmOgY+Mw2qtYOnGzSGWAQytSBMk7lukdE8t8honusV7cPJ2gf/go8LLeKKegReXoWXYVaKyACjgF9KqCzRWpHZMtDlmqgzY0nhgkKmx4VEYBJdwXp0CM11MlCRR/DTd6B2iFIeOoNSmhNFntyzwupGBmPKpEinEt/8lr5Mm46QnoiQW4QFRguwYhXsd/JEvl3sR/szJV52BDxH6EzqiekLxLGlDhAyf3VDlaILztKuSj3cezo/uRvffMkR0bV3zxcEn8QQoisW2di0//vqx6g/5RqoujJhIJ8v9ISiXkpEk39/ms3Gd07zxBK9RJw48ndCywaO62uHn2siAYgx3YtNG80gpDawAMH57YAzFeB0FNU=
*/
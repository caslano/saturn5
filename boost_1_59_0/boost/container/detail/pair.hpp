//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_CONTAINER_DETAIL_PAIR_HPP
#define BOOST_CONTAINER_CONTAINER_DETAIL_PAIR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/static_assert.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/std_fwd.hpp>
#include <boost/container/detail/is_pair.hpp>
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#  include <boost/container/detail/variadic_templates_tools.hpp>
#endif
#include <boost/move/adl_move_swap.hpp> //swap

#include <boost/intrusive/detail/minimal_pair_header.hpp>      //pair
#include <boost/move/utility_core.hpp>
#include <boost/move/detail/fwd_macros.hpp>

namespace boost {
namespace container {
namespace pair_impl {

template <class TupleClass>
struct is_boost_tuple
{
   static const bool value = false;
};

template <
  class T0, class T1, class T2,
  class T3, class T4, class T5,
  class T6, class T7, class T8,
  class T9>
struct is_boost_tuple< boost::tuples::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{
   static const bool value = true;
};

template<class Tuple>
struct disable_if_boost_tuple
   : boost::container::dtl::disable_if< is_boost_tuple<Tuple> >
{};

template<class T>
struct is_tuple_null
{
   static const bool value = false;
};

template<>
struct is_tuple_null<boost::tuples::null_type>
{
   static const bool value = true;
};

}  //namespace detail {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   template <int Dummy = 0>
   struct std_piecewise_construct_holder
   {
      static ::std::piecewise_construct_t *dummy;
   };

   template <int Dummy>
   ::std::piecewise_construct_t *std_piecewise_construct_holder<Dummy>::dummy =
      reinterpret_cast< ::std::piecewise_construct_t *>(0x01234);  //Avoid sanitizer errors on references to null pointers

#else

//! The piecewise_construct_t struct is an empty structure type used as a unique type to
//! disambiguate used to disambiguate between different functions that take two tuple arguments.
typedef unspecified piecewise_construct_t;

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! A instance of type
//! piecewise_construct_t
static piecewise_construct_t piecewise_construct = BOOST_CONTAINER_DOC1ST(unspecified, *std_piecewise_construct_holder<>::dummy);

///@cond

namespace dtl {

struct piecewise_construct_use
{
   //Avoid warnings of unused "piecewise_construct"
   piecewise_construct_use()
   {  (void)&::boost::container::piecewise_construct;   }
};

struct pair_nat;

template<typename T, typename U, typename V>
void get(T); //to enable ADL

///@endcond

#ifdef  _LIBCPP_DEPRECATED_ABI_DISABLE_PAIR_TRIVIAL_COPY_CTOR
//Libc++, in some versions, has an ABI breakage that needs some
//padding in dtl::pair, as "std::pair::first" is not at offset zero.
//See: https://reviews.llvm.org/D56357 for more information.
//
template <class T1, class T2, std::size_t N>
struct pair_padding
{
   char padding[N];
};

template <class T1, class T2>
struct pair_padding<T1, T2, 0>
{
};

template <class T1, class T2>
struct simple_pair
{
   T1 first;
   T2 second;
};

#endif

template <class T1, class T2>
struct pair
#ifdef  _LIBCPP_DEPRECATED_ABI_DISABLE_PAIR_TRIVIAL_COPY_CTOR
   : pair_padding<T1, T2, sizeof(std::pair<T1, T2>) - sizeof(simple_pair<T1, T2>)>
#endif
{
   private:
   BOOST_COPYABLE_AND_MOVABLE(pair)

   public:
   typedef T1 first_type;
   typedef T2 second_type;

   T1 first;
   T2 second;

   //Default constructor
   pair()
      : first(), second()
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }

   //pair copy assignment
   pair(const pair& x)
      : first(x.first), second(x.second)
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }

   //pair move constructor
   pair(BOOST_RV_REF(pair) p)
      : first(::boost::move(BOOST_MOVE_TO_LV(p).first)), second(::boost::move(BOOST_MOVE_TO_LV(p).second))
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }

   template <class D, class S>
   pair(const pair<D, S> &p)
      : first(p.first), second(p.second)
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }

   template <class D, class S>
   pair(BOOST_RV_REF_BEG pair<D, S> BOOST_RV_REF_END p)
      : first(::boost::move(BOOST_MOVE_TO_LV(p).first)), second(::boost::move(BOOST_MOVE_TO_LV(p).second))
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }

   //pair from two values
   pair(const T1 &t1, const T2 &t2)
      : first(t1)
      , second(t2)
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }

   template<class U, class V>
   pair(BOOST_FWD_REF(U) u, BOOST_FWD_REF(V) v)
      : first(::boost::forward<U>(u))
      , second(::boost::forward<V>(v))
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }

   //And now compatibility with std::pair
   pair(const std::pair<T1, T2>& x)
      : first(x.first), second(x.second)
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }

   template <class D, class S>
   pair(const std::pair<D, S>& p)
      : first(p.first), second(p.second)
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }

   pair(BOOST_RV_REF_BEG std::pair<T1, T2> BOOST_RV_REF_END p)
      : first(::boost::move(BOOST_MOVE_TO_LV(p).first)), second(::boost::move(BOOST_MOVE_TO_LV(p).second))
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }

   template <class D, class S>
   pair(BOOST_RV_REF_BEG std::pair<D, S> BOOST_RV_REF_END p)
      : first(::boost::move(BOOST_MOVE_TO_LV(p).first)), second(::boost::move(BOOST_MOVE_TO_LV(p).second))
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
   template< class KeyType, class ...Args>
   pair(try_emplace_t, BOOST_FWD_REF(KeyType) k, Args && ...args)
      : first(boost::forward<KeyType>(k)), second(::boost::forward<Args>(args)...)\
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }
   #else

   //piecewise construction from boost::tuple
   #define BOOST_PAIR_TRY_EMPLACE_CONSTRUCT_CODE(N)\
   template< class KeyType BOOST_MOVE_I##N BOOST_MOVE_CLASS##N > \
   pair( try_emplace_t, BOOST_FWD_REF(KeyType) k BOOST_MOVE_I##N BOOST_MOVE_UREF##N )\
      : first(boost::forward<KeyType>(k)), second(BOOST_MOVE_FWD##N)\
   {\
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));\
   }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_PAIR_TRY_EMPLACE_CONSTRUCT_CODE)
   #undef BOOST_PAIR_TRY_EMPLACE_CONSTRUCT_CODE

   #endif   //BOOST_NO_CXX11_VARIADIC_TEMPLATES

   //piecewise construction from boost::tuple
   #define BOOST_PAIR_PIECEWISE_CONSTRUCT_BOOST_TUPLE_CODE(N,M)\
   template< template<class, class, class, class, class, class, class, class, class, class> class BoostTuple \
            BOOST_MOVE_I_IF(BOOST_MOVE_OR(N,M)) BOOST_MOVE_CLASS##N BOOST_MOVE_I_IF(BOOST_MOVE_AND(N,M)) BOOST_MOVE_CLASSQ##M > \
   pair( piecewise_construct_t\
       , BoostTuple<BOOST_MOVE_TARG##N  BOOST_MOVE_I##N BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(10,N),::boost::tuples::null_type)> p\
       , BoostTuple<BOOST_MOVE_TARGQ##M BOOST_MOVE_I##M BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(10,M),::boost::tuples::null_type)> q\
       , typename dtl::enable_if_c\
         < pair_impl::is_boost_tuple< BoostTuple<BOOST_MOVE_TARG##N  BOOST_MOVE_I##N BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(10,N),::boost::tuples::null_type)> >::value &&\
           !(pair_impl::is_tuple_null<BOOST_MOVE_LAST_TARG##N>::value || pair_impl::is_tuple_null<BOOST_MOVE_LAST_TARGQ##M>::value) \
         >::type* = 0\
       )\
      : first(BOOST_MOVE_TMPL_GET##N), second(BOOST_MOVE_TMPL_GETQ##M)\
   { (void)p; (void)q;\
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));\
   }\
   //
   BOOST_MOVE_ITER2D_0TOMAX(9, BOOST_PAIR_PIECEWISE_CONSTRUCT_BOOST_TUPLE_CODE)
   #undef BOOST_PAIR_PIECEWISE_CONSTRUCT_BOOST_TUPLE_CODE

   //piecewise construction from variadic tuple (with delegating constructors)
   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
   #  if !defined(BOOST_CONTAINER_NO_CXX11_DELEGATING_CONSTRUCTORS)
      private:
      template<template<class ...> class Tuple, class... Args1, class... Args2, size_t... Indexes1, size_t... Indexes2>
      pair(Tuple<Args1...>& t1, Tuple<Args2...>& t2, index_tuple<Indexes1...>, index_tuple<Indexes2...>)
         : first (::boost::forward<Args1>(get<Indexes1>(t1))...)
         , second(::boost::forward<Args2>(get<Indexes2>(t2))...)
      {  (void) t1; (void)t2; }

      public:
      template< template<class ...> class Tuple, class... Args1, class... Args2
              , class = typename pair_impl::disable_if_boost_tuple< Tuple<Args1...> >::type>
      pair(piecewise_construct_t, Tuple<Args1...> t1, Tuple<Args2...> t2)
         : pair(t1, t2, typename build_number_seq<sizeof...(Args1)>::type(), typename build_number_seq<sizeof...(Args2)>::type())
      {
         BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
      }
   #  else
      //piecewise construction from variadic tuple (suboptimal, without delegating constructors)
      private:
      template<typename T, template<class ...> class Tuple, typename... Args>
      static T build_from_args(Tuple<Args...>&& t)
      {  return do_build_from_args<T>(::boost::move(t), typename build_number_seq<sizeof...(Args)>::type());   }

      template<typename T, template<class ...> class Tuple, typename... Args, std::size_t... Indexes>
      static T do_build_from_args(Tuple<Args...> && t, const index_tuple<Indexes...>&)
      {  (void)t; return T(::boost::forward<Args>(get<Indexes>(t))...);  }

      public:
      template< template<class ...> class Tuple, class... Args1, class... Args2
              , class = typename pair_impl::disable_if_boost_tuple< Tuple<Args1...> >::type>
      pair(piecewise_construct_t, Tuple<Args1...> t1, Tuple<Args2...> t2)
         : first  (build_from_args<first_type> (::boost::move(t1)))
         , second (build_from_args<second_type>(::boost::move(t2)))
      {
         BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
      }
   #  endif   //BOOST_NO_CXX11_VARIADIC_TEMPLATES
   #elif defined(BOOST_MSVC) && (_CPPLIB_VER == 520)
      //MSVC 2010 tuple implementation
      #define BOOST_PAIR_PIECEWISE_CONSTRUCT_MSVC2010_TUPLE_CODE(N,M)\
      template< template<class, class, class, class, class, class, class, class, class, class> class StdTuple \
               BOOST_MOVE_I_IF(BOOST_MOVE_OR(N,M)) BOOST_MOVE_CLASS##N BOOST_MOVE_I_IF(BOOST_MOVE_AND(N,M)) BOOST_MOVE_CLASSQ##M > \
      pair( piecewise_construct_t\
          , StdTuple<BOOST_MOVE_TARG##N  BOOST_MOVE_I##N BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(10,N),::std::tr1::_Nil)> p\
          , StdTuple<BOOST_MOVE_TARGQ##M BOOST_MOVE_I##M BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(10,M),::std::tr1::_Nil)> q)\
         : first(BOOST_MOVE_GET_IDX##N), second(BOOST_MOVE_GET_IDXQ##M)\
      { (void)p; (void)q;\
         BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));\
      }\
      //
      BOOST_MOVE_ITER2D_0TOMAX(9, BOOST_PAIR_PIECEWISE_CONSTRUCT_MSVC2010_TUPLE_CODE)
      #undef BOOST_PAIR_PIECEWISE_CONSTRUCT_MSVC2010_TUPLE_CODE
   #elif defined(BOOST_MSVC) && (_CPPLIB_VER == 540)
      #if _VARIADIC_MAX >= 9
      #define BOOST_PAIR_PIECEWISE_CONSTRUCT_MSVC2012_TUPLE_MAX_IT 9
      #else
      #define BOOST_PAIR_PIECEWISE_CONSTRUCT_MSVC2012_TUPLE_MAX_IT BOOST_MOVE_ADD(_VARIADIC_MAX, 1)
      #endif

      //MSVC 2012 tuple implementation
      #define BOOST_PAIR_PIECEWISE_CONSTRUCT_MSVC2012_TUPLE_CODE(N,M)\
      template< template<BOOST_MOVE_REPEAT(_VARIADIC_MAX, class), class, class, class> class StdTuple \
               BOOST_MOVE_I_IF(BOOST_MOVE_OR(N,M)) BOOST_MOVE_CLASS##N BOOST_MOVE_I_IF(BOOST_MOVE_AND(N,M)) BOOST_MOVE_CLASSQ##M > \
      pair( piecewise_construct_t\
          , StdTuple<BOOST_MOVE_TARG##N  BOOST_MOVE_I##N BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(BOOST_MOVE_ADD(_VARIADIC_MAX, 3),N),::std::_Nil) > p\
          , StdTuple<BOOST_MOVE_TARGQ##M BOOST_MOVE_I##M BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(BOOST_MOVE_ADD(_VARIADIC_MAX, 3),M),::std::_Nil) > q)\
         : first(BOOST_MOVE_GET_IDX##N), second(BOOST_MOVE_GET_IDXQ##M)\
      { (void)p; (void)q;\
         BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));\
      }\
      //
      BOOST_MOVE_ITER2D_0TOMAX(BOOST_PAIR_PIECEWISE_CONSTRUCT_MSVC2012_TUPLE_MAX_IT, BOOST_PAIR_PIECEWISE_CONSTRUCT_MSVC2012_TUPLE_CODE)
      #undef BOOST_PAIR_PIECEWISE_CONSTRUCT_MSVC2010_TUPLE_CODE
      #undef BOOST_PAIR_PIECEWISE_CONSTRUCT_MSVC2012_TUPLE_MAX_IT
   #endif

   //pair copy assignment
   pair& operator=(BOOST_COPY_ASSIGN_REF(pair) p)
   {
      first  = p.first;
      second = p.second;
      return *this;
   }

   //pair move assignment
   pair& operator=(BOOST_RV_REF(pair) p)
   {
      first  = ::boost::move(BOOST_MOVE_TO_LV(p).first);
      second = ::boost::move(BOOST_MOVE_TO_LV(p).second);
      return *this;
   }

   template <class D, class S>
   typename ::boost::container::dtl::disable_if_or
      < pair &
      , ::boost::container::dtl::is_same<T1, D>
      , ::boost::container::dtl::is_same<T2, S>
      >::type
      operator=(const pair<D, S>&p)
   {
      first  = p.first;
      second = p.second;
      return *this;
   }

   template <class D, class S>
   typename ::boost::container::dtl::disable_if_or
      < pair &
      , ::boost::container::dtl::is_same<T1, D>
      , ::boost::container::dtl::is_same<T2, S>
      >::type
      operator=(BOOST_RV_REF_BEG pair<D, S> BOOST_RV_REF_END p)
   {
      first  = ::boost::move(BOOST_MOVE_TO_LV(p).first);
      second = ::boost::move(BOOST_MOVE_TO_LV(p).second);
      return *this;
   }
//std::pair copy assignment
   pair& operator=(const std::pair<T1, T2> &p)
   {
      first  = p.first;
      second = p.second;
      return *this;
   }

   template <class D, class S>
   pair& operator=(const std::pair<D, S> &p)
   {
      first  = ::boost::move(p.first);
      second = ::boost::move(p.second);
      return *this;
   }

   //std::pair move assignment
   pair& operator=(BOOST_RV_REF_BEG std::pair<T1, T2> BOOST_RV_REF_END p)
   {
      first  = ::boost::move(BOOST_MOVE_TO_LV(p).first);
      second = ::boost::move(BOOST_MOVE_TO_LV(p).second);
      return *this;
   }

   template <class D, class S>
   pair& operator=(BOOST_RV_REF_BEG std::pair<D, S> BOOST_RV_REF_END p)
   {
      first  = ::boost::move(BOOST_MOVE_TO_LV(p).first);
      second = ::boost::move(BOOST_MOVE_TO_LV(p).second);
      return *this;
   }

   //swap
   void swap(pair& p)
   {
      ::boost::adl_move_swap(this->first, p.first);
      ::boost::adl_move_swap(this->second, p.second);
   }
};

template <class T1, class T2>
inline bool operator==(const pair<T1,T2>& x, const pair<T1,T2>& y)
{  return static_cast<bool>(x.first == y.first && x.second == y.second);  }

template <class T1, class T2>
inline bool operator< (const pair<T1,T2>& x, const pair<T1,T2>& y)
{  return static_cast<bool>(x.first < y.first ||
                         (!(y.first < x.first) && x.second < y.second)); }

template <class T1, class T2>
inline bool operator!=(const pair<T1,T2>& x, const pair<T1,T2>& y)
{  return static_cast<bool>(!(x == y));  }

template <class T1, class T2>
inline bool operator> (const pair<T1,T2>& x, const pair<T1,T2>& y)
{  return y < x;  }

template <class T1, class T2>
inline bool operator>=(const pair<T1,T2>& x, const pair<T1,T2>& y)
{  return static_cast<bool>(!(x < y)); }

template <class T1, class T2>
inline bool operator<=(const pair<T1,T2>& x, const pair<T1,T2>& y)
{  return static_cast<bool>(!(y < x)); }

template <class T1, class T2>
inline pair<T1, T2> make_pair(T1 x, T2 y)
{  return pair<T1, T2>(x, y); }

template <class T1, class T2>
inline void swap(pair<T1, T2>& x, pair<T1, T2>& y)
{  x.swap(y);  }

}  //namespace dtl {
}  //namespace container {

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES

template<class T1, class T2>
struct has_move_emulation_enabled< ::boost::container::dtl::pair<T1, T2> >
{
   static const bool value = true;
};

#endif

namespace move_detail{

template<class T>
struct is_class_or_union;

template <class T1, class T2>
struct is_class_or_union< ::boost::container::dtl::pair<T1, T2> >
//This specialization is needed to avoid instantiation of pair in
//is_class, and allow recursive maps.
{
   static const bool value = true;
};

template <class T1, class T2>
struct is_class_or_union< std::pair<T1, T2> >
//This specialization is needed to avoid instantiation of pair in
//is_class, and allow recursive maps.
{
   static const bool value = true;
};

template<class T>
struct is_union;

template <class T1, class T2>
struct is_union< ::boost::container::dtl::pair<T1, T2> >
//This specialization is needed to avoid instantiation of pair in
//is_class, and allow recursive maps.
{
   static const bool value = false;
};

template <class T1, class T2>
struct is_union< std::pair<T1, T2> >
//This specialization is needed to avoid instantiation of pair in
//is_class, and allow recursive maps.
{
   static const bool value = false;
};

template<class T>
struct is_class;

template <class T1, class T2>
struct is_class< ::boost::container::dtl::pair<T1, T2> >
//This specialization is needed to avoid instantiation of pair in
//is_class, and allow recursive maps.
{
   static const bool value = true;
};

template <class T1, class T2>
struct is_class< std::pair<T1, T2> >
//This specialization is needed to avoid instantiation of pair in
//is_class, and allow recursive maps.
{
   static const bool value = true;
};


//Triviality of pair
template<class T>
struct is_trivially_copy_constructible;

template<class A, class B>
struct is_trivially_copy_assignable
   <boost::container::dtl::pair<A,B> >
{
   static const bool value = boost::move_detail::is_trivially_copy_assignable<A>::value &&
                             boost::move_detail::is_trivially_copy_assignable<B>::value ;
};

template<class T>
struct is_trivially_move_constructible;

template<class A, class B>
struct is_trivially_move_assignable
   <boost::container::dtl::pair<A,B> >
{
   static const bool value = boost::move_detail::is_trivially_move_assignable<A>::value &&
                             boost::move_detail::is_trivially_move_assignable<B>::value ;
};

template<class T>
struct is_trivially_copy_assignable;

template<class A, class B>
struct is_trivially_copy_constructible<boost::container::dtl::pair<A,B> >
{
   static const bool value = boost::move_detail::is_trivially_copy_constructible<A>::value &&
                             boost::move_detail::is_trivially_copy_constructible<B>::value ;
};

template<class T>
struct is_trivially_move_assignable;

template<class A, class B>
struct is_trivially_move_constructible<boost::container::dtl::pair<A,B> >
{
   static const bool value = boost::move_detail::is_trivially_move_constructible<A>::value &&
                             boost::move_detail::is_trivially_move_constructible<B>::value ;
};

template<class T>
struct is_trivially_destructible;

template<class A, class B>
struct is_trivially_destructible<boost::container::dtl::pair<A,B> >
{
   static const bool value = boost::move_detail::is_trivially_destructible<A>::value &&
                             boost::move_detail::is_trivially_destructible<B>::value ;
};


}  //namespace move_detail{

}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_PAIR_HPP

/* pair.hpp
rcJs8np5RFPwpr7ZQIvmQUZI0O3L1N0ro+i14QSCAGrrwJuu2eMy9o6mT/VYctFJZ4N6pRUnK3D+p/Wc6wkLBRwC0vExkBOorV57dfeW+VnAhjcIb08N+XDWIgUWa1FGtPFJhDsOHNHPhCqQenxsUSZe3ybs20854DatywcpVpiXbaaVG7ZrXWXQpVT6D3X1bMeUJeowSm08vqqaUQPOOQ38mJvASPENSyxULSmcf2rG3xcun/9qC/fSZ2DG8x4rQsGEaGHqWBNVITO7rFPDQe0bSlOurgeJOsbUv0bfuzM25LnFR6Z34wVziwCyz6UTgXHUhAnB4OihWJsuDTI5UBxlSxutZxoFrCJHgi10dhHEa7KCd7XwyRcTZn4XwQvI7X7UNixd9DxpxAzzmEZ68RxFKa4wnd7INjVqyj7bqh4kD5bWJAIoSmWzRCxKwZfuuaGArNLJTE8j0QiVKP+jErcuCE77VPFS90Yws5Ad/UnqGDxLLN1ko0RAGGm31Mtj+TucPneMzYy+PKicwxgrZNA3iaAWRfuX0dznP1S7YCGsAADajUAIqBBVUN0D7VwHkoiPRBfunN1lEcZtsejyxMbQD7dPAfrwyXE08JP0FLudyl9kJn5OFeJBw5BhL/YNWcsSMwMU9HWPyt9+u7M03tG5ThlVGlPessZ6sLxxAAQh62/+golhaijKYD5eqZxDRhLXcPaOmUAW0FE61aEgkBOifyvIeu+NOxU+7ZsNK+iJFXKMQo0JFHOFkz8BiXwI5ym/sIRbfuAFFLzM5op9cXRvgUYKhyf+6954m7p2YSCNLjA0jglX3t0Sklig0OhiB//tNzX0uA907KGbtiFzc/agaVsMOSfo1f4S3d3l+YSPGVslylNBxxn851NV+Oj+0GyZFoDfABDymUZT99oprXJCD1sH98Uy5kwBUUC0GAgAtsu+An1wC4tI9mBhWk6E4U2xtTRVZb/4ljNkD/ZJzrZIDM6wZaNV446L+wSThvgZNsgTPMzZR+46KXwvrB3oPYAihmzseOgwsMno7wtTzKG7cDLXI2K0xUBrG4V16IN8Nhna/v4VKwnrtf8SpOIWqFP5fkTRKtp5PL7yFEhK1EVDy51M6oVrRmwWR0Cm8Tmg2t2ARRnnjXC+0vpgdntSZQje6jLfoy5VVmdGvaC6sXWrbbKRSMNat5aoQH8EZxaF6/r6obR2ZdoeiJcq84O+q3BENap63vjXftLGPu2+IvIEKpJGKi73JvrwuUDWccwjgvEpBXWGJ9iwW2pnSHKMecqtuyYfEsLLKP6wDmkQiH4TMHRLhsRH7cHM7Jk3NBo5mEMqoEsuVp/hsuSXiQnfcZptdis+TqHtNpdXVLmBxYjA4ILRiVA9ajWpMi3QufhYoVIdXLiIR1Q6KjLAKUtUgY/I4CcvwlKCWwiNtHUFc1NDJM+lVzolQaYTqqyAG/U1hWqZO/6qQHXJpaIaEKLe5yZT9YxKSS3Sd2pU03cCeawVRCexNWCpEdR98/NJL7pnnMeApYEUYylB4c7CrLhCy5Jb8blJI1soucGI4Eq1OQ10SLfAWCDDnaNP9KM/AdoNt+MV1kWiKQxszAgpH9v+ZyffdgyUjx0jjEtobUVGru8dJkGXG247HtXWbkpVwbis77nWQpoBtexhYsoHeA1aThigki+3Qp4x4iLZWC9ubP6fYuHtNA969Ih17cdkFlxp/UNjteORjxfk96vPrV0lm/2SBYajN+Cl5PX2eu2cAC6+/VMNSiapa+SEJGfGemE3c+p1Ni45NnXlHgHA8JMPVhbe3XxDQP6i4z+ze8T7KnT0z+AhNWJvQEEYfoAQRaRuQPykVQG2EAN62PiqC0W7dhbmvL5Oix6sujp0uuIwfx86WsavF3T1c21ar5e3eY7pCYpp6sjcHUvP+n8Cq459KwcYlJcio9Ctyp4EUylpZFPI7NZQhk7Vkkxi7xywvZg1KAd8q+0Nh7Rm0jLvkfHkHmbF/yz/Dli0PjOrMhEAANZ3+9Dk+IPTyQAYgAfB/Zr0JYlLUoUd3H0TzJRmkwN1hqk/DPf+6eQB1uC0dZa29R/WP6ARWPTAGbWXvfTpNnwwXnlKJkjeU45SHGNJxKlJIIG1XTWhBummpNTfARMuhmOHkLNOf82dL6bF2pceGyOB6KuzPFjRgfntQWTsPjJBkdwjl/H6eIQ6Ih2AsotgmmTazcbckZedrLfUEnM7i/eck+0tQJR9Qc3WDVl+wwoOQqgE48vOmAwKUlN02lB4qOKoWYjc6qNz9cy5/FtfWvZu+ft2ELxopWR/gYIkZWJUOH+RE3rfZhZkWEGi+JpkYQZKtiRzlCnoxNCCVjHHWBIltdCC+RNAj0xwWGGkmCFiyJN6lpUCwiMXbW6dSPXy5WsAwOpfoU+x/8AlvLNeqdFUKqK9rWXfsYWTADCQlVqEJBHZKbTCWFhlyYJci+f16+O/rYjeJTunP6zboHAvRUsHDw28LIS+1evgUTGjBpyWV8zpgYKSdhf0GKUcQLW2152md4wZg7aP35ym+51b+KlDCCdgW1FLZpUls0p33KeCRDx8/MoI0fNL0GPqVqYBEAImb/ujzQwTBPXwKZjtGHPSyxsqCIuLvW6okkALDwNHZ58nvBrr+FAHy+Xejl+cW1QPGw51Sn9PIKlbOamj+W+/29I52s8R3cH71a5AgRt2VshLBhGCkC3XoFK9kH/8R/xVs9mk+1OuaQbRw9T5vuuDhkSwE7+/NEdIzio4QjGybhxUWjQj1VRzyCFbL8EXK+qhgwUQ98GiA0Hi1yUFg/MLYxNI64fjvscku84KHBvXwvIRVGGCi22hmjL0zT//pRkkt2Ffx6XQkh3W400LFe1AgCGNTEbPdEurHfWlYIO8DodifmR0uA45INPwzMBmodSyU2seAwAF3Tq7k+EtZ42TUsnohfTgD/I2swvkAPcrU9CuX+JVxBN41VbkDeU0PUmxXY6kHY6a45mGmHc0YYct9yHDbfDm0gPlLncCMldzueln5jTmt62BJad00dcItil6lHuQAIRGzq2aB9fd5liMq36qJcZm83pNlmz/q+mo4S7dIgeBvr+orplUQVmJHeUvlKw56AAEEJpUhMsuIfT8hY+X3PR9QQeZ5mWlW1sDBp+gR2ioaKlmZ+PzVOtYGKPD+B2taMQraiujHng7VJ5QSKxhmXGAus1Fy9bdMgv6cCbzSOs9t921IkOmJM5HpGc2iew3E6U0DwHsBYrjcNT53liFAtmt/4Q0X3kpk9J8nw+mMl/7AHK/e/0azeZZupPOAv53X5MVW9V8vuBJzaKe6Gtnp+3Wq9Har+iQsV0/yiYmplQrbGVjaVmYSUKO6oAmF6SLnhU5p1obV7MtDZx7j2c29LRYc8oz5v5Li13modNqfmnmktU8gpuN1h8eB4uy0SkcJZYGOq4lyHStrBbsvGnGgzNyjsSLd/lpzDc9AzIHaHdSodizS8eBpY5E4GQQO+3wlc5I11KKrJ5VSW7FXR6hJXZoDmmzQBHbguUVzst76xrOHZvagQ5agheOq0QCIpBfw39kLXJ/8PktxVN9pQUVDzDTU3bZPLTGBodAW01XBACjpfdfOA+6MazB3ZXGh5v9UNEEv2O015G+qBz25rNGMnEMH3NXO1g8bTGw/cR/A9d38vOLkwHa7KMP3ef5EL1qIhRvpwOyCi//Ba9PpjwaArOsvcxl6TIwYSfst0mZAd/5SEGyQn/9qpJWLmCcamSoBjvG9ZsqPTMxWjOJtdliIvY0S3pDF9TtFFd2Bu7BQCKtNDoeSDegzQowHf28+UAhz49KfPYLrEUZmrhkWT+qU1McxGCmgTsIL7fSH9SJnCp3vWFJ+chw6tywkUdW6w9dQPsmyFJjSlK0SXmT81djsyx/NoZLqEm+8DjnjD8D5HLSWC8cta8FRQ3LbTiQ5BIl4AqTqXAz/SivhP4SGNkp5WJwy2+ggtNY8ackclXRo/030Ie+vrzansNFCcUnqgnklU2mbz1S30MAPkSRVVklshKLwPMoRBKTK8ek4qLCvEGQI5nO6cOqbaeAYQ2Je3TOTzCC3Y2AfCjNf+BDy8tef3eVBNRDmsBdgNXtz3Em/RKXKulJr5ygsB7HaPL4fmX0pCgZ7RQS75QCRO4qGk5MrZ92/GEIBi/aLpjYfjGLsDy2FKZYX+LUXPKs975zhQImdnwZZNKgIyl7bGqIpil1aTm97kdl8DHlMjOTZtmaVRGTSf1005T8PRzmVM1A25zfzPIBmVX5L1by2Z5VNfSW4YInkdZPSVWarDwFJYRWBdPRzXyG3Qhs0ybbIH7CnPZOnxVlXOP7vbk+BwxNL/XTxeJdTMvLZ1NjnSJqZWBayOq4u70Y6GGDVbyThN6n3MP6bILXQuh0Ta+rOPm1NjtuaqUGU3V04r+g7fXHiffZlBaeMaxVAvfq/O/EwOZCq9MKuO4006qbx+Jmvo3SiddNmuxaKdad/5Yui/L3Sdz8LLkNArzB9nhouoN6ZyJ2OZ/yOeo/E7phca7ZW/D36j/zwuyCMNhgvSDU8F0LbIXGTWLmFFWr549/QaxkMQk9m+AYOFYZXPYt8k714+xpN0Um2a2DpI3iGvR3xIL38b7GIq5luTqiZC+ZS46spagJyiKpBvmIRWyxVs1b4oaHVkv+68tYGnW2/zRpF8sa5DHo8MndafL49zJosgB3TvBo7phRLOA0oflD8Gn7AOJ73LyAuMgArbmavDpQPCNVzYBFdVk7NLpZluyki9v8rzz6w2uejTgJYz61vGj2QzAnotA7rKqoivdGMUJz8ZVlt90b/MaQ5kQpJGODUX/QpVzmp3wDsh6wrKWvcSvrWhnrZZERrMqnWGm6nZcmKrNM2KeZd729Xvp1QVrU+Wf9op3DZHKCU8BQoHq+nWLicoLXwAgp6qO82Gpyo90sqD3srthJ9GakHsAOnDS8+fF6YmNUzOsT8rH5kvJyBB7XDrbsZCPo0OcFDdoPjzO0Mq7rcy0R8RfA4ZjFxb8Pf8vMKY191EV5T8mWJfvU3/PU5QtullX2+zE848HmqW8IqBjoN9g2ZFMlbZfgWeg0HfasxH/lWt4+0K/l9JkzS/RNHUbWXvZQhEAo41hdQNge0X1Y5T/na3Wie5eSyfYF3cJX7YxGlRekSyMf/c/2kn2pRKMii2vqjfbBU/7jCcwPo0PI8+KopqclyEsn6FSHrrOAvZnTY6NfIq36rYFD1tj7R/rqZYv0h0/erRInA+kdG9HQOwebwNf0xhEb3jC/nLbPa+GkMZ9jocpCo4tHRdF+I4eA1xbL48uB6hJr/KC7Zoz1T0rqE92I3k8T69PLH7phRPquQ5e80UsG8V/HzNQzI8fjTZV/85eiPKc+dMW2SNyTl/2hZ5e0HZMOEG/P2HuPPczPz66ph98KgxxupwuP3avAW8ufX2CV37y57bs5gB6dgO8dFlWqAP2NoA6K5gL/GXvEAQpVggoBIgcEfLe+QgAAAZSDkoB974oOz+lAw4IF/swqMBgm3A2paQXVt/0yULLmUCzLc6fc+7nH/awGPP8+4drEsKlULaF/tb6e8YkN/2x7NS3vf9j3sMwrNi4eQsPJkW9qfvbCVzlhpVKVCOaoSbfwPJ2ZRAkjTDSz/Yz2eXYmNaBm35cOVsMyf0lWDvpFRz6D9f1+lqXPoB+UINxeps9K/4ue5tr9PBy2HNSjW1mD68fSv7XDLxJ0G30c/EVX/61VqPd7xQUUyCtz9fnd9hJW6LiMu4t7DX++8AVzTsU40Nsp7Nb/8hMdDl8c3juHtzJzESyPlHr9WzrELC1CySNHkn84ZIn8wOW5b5m8lPObdUGvivyYq8AQ6dclhm0WBhn56x6nvDwV+3OPi0NyyZ77fchTwCvLIsvKJctEQ8sl22rNyzVTh1PCO+6szco17shDyzX+4s3LNX5/rZspohHKzDcNXUzONx13xM5HE45SykElPeSyQCvJQvFrpnz1VUXMln7S1US//tV1RXQ7aq1QzvMuimyMYN/zpcazpZ/Lv8g8myi0yXFTe5F6+gidIkusGb2hqt2l53L4JZDSrHTQpBYTtav4DURFiqg2ffkZFATE1X+3Wv05EaJmk7WCVZyuX+I2hrP6jbeCk2mEGq3zyn0KHIhnH8UGxF9YmrUj1xzVJok+AbPpSz4zuQnoD7K9jd/RcbyN8LI70WngnTbZiXiA0PGp0IA8+clQkTjx6dCROvkJWYLYESbRgjIZRlGTNBFm0ZM2GYYhYP4xqqFAXTnKITFRMeqhMeMHtkJylouqslydk8r8o1qfNuvoLpBeRS/T32j48OuNmid+5anZat3uuVOHk++37qxd77nuyFPuuf6CjMBKoGM9You8vr/jYb8FK1r5cxvw3Do49BdC121VMUCzryztWDV6oIDEwgvteDiQpohp4P8Ofltlr/xsn9sZaZ7jJcULgE0jCOYCf/mcDX+HLqQ5EvmQQXXrt1hq3vziUijP8VnHnwuPf6NTPGMFA77SnvyGKdelC6cueg1BK1/nFwyV9l9p8aI/LrwpMsbhZUA+y/u4+aHgZLDES83puHFDTJawLTbtuTOFsBinww7NWdUIi2fnQy6N65OLOQ6+kG41zEuivcjaqQbXTYEnaswy8BeHbc2G4KF16A6Xf/RJZQV1eF+mT4wpbu0k3VY694bVs+HlBTafLUfDznq+do1MeBnucusNkQEGy35+ZtUFSjwEf8yqhNtSok+B5pZ/5iOGjRLI976oVPuVzQvKFEvKf3GpMt1pkxE6DCqCxFkjF7/oXw4Xgsx7fMhS6EnhoLrT/YYllcNhwWKoll93jVAoA/zXwSseatUz+KcUxktGL4q/kCrbXue6/qoBSKuf4XNLmiG6zLdc1QrMAk3m5A+NqvytsIbj5dLvUCQ4lRhQfi870b/+lDc53NUHSgZmtBsNB26CMgld0rXzKiwQQnBXxtdzG5jPLaPvYP5Tsjs2bliUfux/5vryHNWqxLPvEs2Vc3uYkfNmfQkAr8fVQITyyiYt/1lfsYIBRtwgBHtRZMDmuzLpVTG7TH7Dx8x1wmG6MtCrYXQBmkPaEShnUmmDxgqnOCyDKle3lQcN9XfftHt4ll58D08DB8Gkutb2sUfQQ8yuhTuvbbaHbrDPPZWIokl1GJP7cgGd+PSzS85Q16hzw7CZb8+BMqErwJUbM3AxmxUpgV4Ou0VFs1jPBLGTkvO7aBEd9aNmAiwhZOKcHQ10Ivjm1OqHnobAC9MfbUnlWqE4zU/jLGMh+vy3h0H+7z9jhhTdG5DI/7jt4vEJFX+1qhrI1bLlKtgbr+381ei4WD/DazsDgKxovfKTH0I69/+t1uwTAHneP+s7VE2HldMQ1fyiVloGDV4hgL3OX5ncvDYuoJi/Pk6kXqUcXiCCwVdHYlzGUX33nMVdyq7o4bJ1z7FGrH6rs3o38Aiz5L4ykzPlwjfSRuTERV3wxzRqV2fWmpm3Z9Smiege3a4iwofctuaHp9++rkRn3MadQBnvmWmEAd1VGhOCvWW3MACDjNAhBPBb2QMq2PoAz4X310lz9GvYfmOrhBOQ16/npdh9jwMJGpgIfcR/lIqz7x/kkzBjRsyMEfOIP+zpBzkxbBgF8SqQ
*/
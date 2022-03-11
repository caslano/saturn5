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
#include <boost/container/detail/workaround.hpp>

#include <boost/static_assert.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/std_fwd.hpp>
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#  include <boost/container/detail/variadic_templates_tools.hpp>
#endif
#include <boost/move/adl_move_swap.hpp> //swap

#include <boost/intrusive/detail/minimal_pair_header.hpp>      //pair
#include <boost/move/utility_core.hpp>
#include <boost/move/detail/fwd_macros.hpp>

namespace boost {
namespace tuples {

struct null_type;

template <
  class T0, class T1, class T2,
  class T3, class T4, class T5,
  class T6, class T7, class T8,
  class T9>
class tuple;

}  //namespace tuples {
}  //namespace boost {

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

}}}

#if defined(BOOST_MSVC) && (_CPPLIB_VER == 520)
//MSVC 2010 tuple marker
namespace std { namespace tr1 { struct _Nil; }}
#elif defined(BOOST_MSVC) && (_CPPLIB_VER == 540)
//MSVC 2012 tuple marker
namespace std { struct _Nil; }
#endif


namespace boost {
namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   template <int Dummy = 0>
   struct std_piecewise_construct_holder
   {
      static ::std::piecewise_construct_t *dummy;
   };

   template <int Dummy>
   ::std::piecewise_construct_t *std_piecewise_construct_holder<Dummy>::dummy =
      reinterpret_cast< ::std::piecewise_construct_t *>(0x01234);  //Avoid sanitizer errors on references to null pointers

typedef const std::piecewise_construct_t & piecewise_construct_t;

struct try_emplace_t{};

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

template <class T1, class T2>
struct pair;

template <class T>
struct is_pair
{
   static const bool value = false;
};

template <class T1, class T2>
struct is_pair< pair<T1, T2> >
{
   static const bool value = true;
};

template <class T1, class T2>
struct is_pair< std::pair<T1, T2> >
{
   static const bool value = true;
};

template <class T>
struct is_not_pair
{
   static const bool value = !is_pair<T>::value;
};

template <class T>
struct is_std_pair
{
   static const bool value = false;
};

template <class T1, class T2>
struct is_std_pair< std::pair<T1, T2> >
{
   static const bool value = true;
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
      : first(::boost::move(p.first)), second(::boost::move(p.second))
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
      : first(::boost::move(p.first)), second(::boost::move(p.second))
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
      : first(::boost::move(p.first)), second(::boost::move(p.second))
   {
      BOOST_STATIC_ASSERT((sizeof(std::pair<T1, T2>) == sizeof(pair<T1, T2>)));
   }

   template <class D, class S>
   pair(BOOST_RV_REF_BEG std::pair<D, S> BOOST_RV_REF_END p)
      : first(::boost::move(p.first)), second(::boost::move(p.second))
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
      first  = ::boost::move(p.first);
      second = ::boost::move(p.second);
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
      first  = ::boost::move(p.first);
      second = ::boost::move(p.second);
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
      first  = ::boost::move(p.first);
      second = ::boost::move(p.second);
      return *this;
   }

   template <class D, class S>
   pair& operator=(BOOST_RV_REF_BEG std::pair<D, S> BOOST_RV_REF_END p)
   {
      first  = ::boost::move(p.first);
      second = ::boost::move(p.second);
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
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
*/
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DISPATCH_USES_ALLOCATOR_HPP
#define BOOST_CONTAINER_DISPATCH_USES_ALLOCATOR_HPP

#if defined (_MSC_VER)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/container/allocator_traits.hpp>
#include <boost/container/uses_allocator.hpp>

#include <boost/container/detail/addressof.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/pair.hpp>
#include <boost/container/detail/type_traits.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif
#include <boost/move/utility_core.hpp>

#include <boost/core/no_exceptions_support.hpp>

namespace boost { namespace container {

namespace dtl {


// Check if we can detect is_convertible using advanced SFINAE expressions
#if !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   //! Code inspired by Mathias Gaunard's is_convertible.cpp found in the Boost mailing list
   //! http://boost.2283326.n4.nabble.com/type-traits-is-constructible-when-decltype-is-supported-td3575452.html
   //! Thanks Mathias!

   //With variadic templates, we need a single class to implement the trait
   template<class T, class ...Args>
   struct is_constructible
   {
      typedef char yes_type;
      struct no_type
      { char padding[2]; };

      template<std::size_t N>
      struct dummy;

      template<class X>
      static decltype(X(boost::move_detail::declval<Args>()...), true_type()) test(int);

      template<class X>
      static no_type test(...);

      static const bool value = sizeof(test<T>(0)) == sizeof(yes_type);
   };

   template <class T, class InnerAlloc, class ...Args>
   struct is_constructible_with_allocator_prefix
      : is_constructible<T, allocator_arg_t, InnerAlloc, Args...>
   {};

#else    // #if !defined(BOOST_NO_SFINAE_EXPR) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   //Without advanced SFINAE expressions, we can't use is_constructible
   //so backup to constructible_with_allocator_xxx

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template <class T, class InnerAlloc, class ...Args>
   struct is_constructible_with_allocator_prefix
      : constructible_with_allocator_prefix<T>
   {};

   template <class T, class InnerAlloc, class ...Args>
   struct is_constructible_with_allocator_suffix
      : constructible_with_allocator_suffix<T>
   {};

   #else    // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template <class T, class InnerAlloc, BOOST_MOVE_CLASSDFLT9>
   struct is_constructible_with_allocator_prefix
      : constructible_with_allocator_prefix<T>
   {};

   template <class T, class InnerAlloc, BOOST_MOVE_CLASSDFLT9>
   struct is_constructible_with_allocator_suffix
      : constructible_with_allocator_suffix<T>
   {};

   #endif   // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#endif   // #if !defined(BOOST_NO_SFINAE_EXPR)

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template < typename ConstructAlloc
         , typename ArgAlloc
         , typename T
         , class ...Args
         >
inline typename dtl::enable_if_and
   < void
   , dtl::is_not_pair<T>
   , dtl::not_< uses_allocator<T, ArgAlloc> >
   >::type dispatch_uses_allocator
   ( ConstructAlloc & construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, T* p, BOOST_FWD_REF(Args)...args)
{
   (void)arg_alloc;
   allocator_traits<ConstructAlloc>::construct(construct_alloc, p, ::boost::forward<Args>(args)...);
}

// allocator_arg_t
template < typename ConstructAlloc
         , typename ArgAlloc
         , typename T
         , class ...Args
         >
inline typename dtl::enable_if_and
   < void
   , dtl::is_not_pair<T>
   , uses_allocator<T, ArgAlloc>
   , is_constructible_with_allocator_prefix<T, ArgAlloc, Args...>
   >::type dispatch_uses_allocator
   ( ConstructAlloc& construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, T* p, BOOST_FWD_REF(Args) ...args)
{
   allocator_traits<ConstructAlloc>::construct
      ( construct_alloc, p, allocator_arg
      , ::boost::forward<ArgAlloc>(arg_alloc), ::boost::forward<Args>(args)...);
}

// allocator suffix
template < typename ConstructAlloc
         , typename ArgAlloc
         , typename T
         , class ...Args
         >
inline typename dtl::enable_if_and
   < void
   , dtl::is_not_pair<T>
   , uses_allocator<T, ArgAlloc>
   , dtl::not_<is_constructible_with_allocator_prefix<T, ArgAlloc, Args...> >
   >::type dispatch_uses_allocator
   ( ConstructAlloc& construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, T* p, BOOST_FWD_REF(Args)...args)
{
   allocator_traits<ConstructAlloc>::construct
      (construct_alloc, p, ::boost::forward<Args>(args)..., ::boost::forward<ArgAlloc>(arg_alloc));
}

#else    //#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#define BOOST_CONTAINER_SCOPED_ALLOCATOR_DISPATCH_USES_ALLOCATOR_CODE(N) \
   template <typename ConstructAlloc, typename ArgAlloc, typename T BOOST_MOVE_I##N BOOST_MOVE_CLASS##N >\
   inline typename dtl::enable_if_and\
      < void\
      , dtl::is_not_pair<T>\
      , dtl::not_<uses_allocator<T, ArgAlloc> >\
      >::type\
      dispatch_uses_allocator\
      (ConstructAlloc &construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, T* p BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      (void)arg_alloc;\
      allocator_traits<ConstructAlloc>::construct(construct_alloc, p BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
   }\
//
BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_SCOPED_ALLOCATOR_DISPATCH_USES_ALLOCATOR_CODE)
#undef BOOST_CONTAINER_SCOPED_ALLOCATOR_DISPATCH_USES_ALLOCATOR_CODE

#define BOOST_CONTAINER_SCOPED_ALLOCATOR_DISPATCH_USES_ALLOCATOR_CODE(N) \
   template < typename ConstructAlloc, typename ArgAlloc, typename T BOOST_MOVE_I##N BOOST_MOVE_CLASS##N >\
   inline typename dtl::enable_if_and\
      < void\
      , dtl::is_not_pair<T>\
      , uses_allocator<T, ArgAlloc>\
      , is_constructible_with_allocator_prefix<T, ArgAlloc BOOST_MOVE_I##N BOOST_MOVE_TARG##N>\
      >::type\
      dispatch_uses_allocator\
      (ConstructAlloc& construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, T* p BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      allocator_traits<ConstructAlloc>::construct\
         (construct_alloc, p, allocator_arg, ::boost::forward<ArgAlloc>(arg_alloc) BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
   }\
//
BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_SCOPED_ALLOCATOR_DISPATCH_USES_ALLOCATOR_CODE)
#undef BOOST_CONTAINER_SCOPED_ALLOCATOR_DISPATCH_USES_ALLOCATOR_CODE

#define BOOST_CONTAINER_SCOPED_ALLOCATOR_DISPATCH_USES_ALLOCATOR_CODE(N) \
   template < typename ConstructAlloc, typename ArgAlloc, typename T BOOST_MOVE_I##N BOOST_MOVE_CLASS##N >\
   inline typename dtl::enable_if_and\
      < void\
      , dtl::is_not_pair<T>\
      , uses_allocator<T, ArgAlloc>\
      , dtl::not_<is_constructible_with_allocator_prefix<T, ArgAlloc BOOST_MOVE_I##N BOOST_MOVE_TARG##N> >\
      >::type\
      dispatch_uses_allocator\
      (ConstructAlloc& construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, T* p BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      allocator_traits<ConstructAlloc>::construct\
         (construct_alloc, p BOOST_MOVE_I##N BOOST_MOVE_FWD##N, ::boost::forward<ArgAlloc>(arg_alloc));\
   }\
//
BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_SCOPED_ALLOCATOR_DISPATCH_USES_ALLOCATOR_CODE)
#undef BOOST_CONTAINER_SCOPED_ALLOCATOR_DISPATCH_USES_ALLOCATOR_CODE

#endif   //#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template < typename ConstructAlloc
         , typename ArgAlloc
         , typename Pair
         > inline 
BOOST_CONTAINER_DOC1ST(void, typename dtl::enable_if<dtl::is_pair<Pair> BOOST_MOVE_I void >::type)
   dispatch_uses_allocator
   ( ConstructAlloc & construct_alloc
   , BOOST_FWD_REF(ArgAlloc) arg_alloc
   , Pair* p)
{
   (dispatch_uses_allocator)(construct_alloc, arg_alloc, dtl::addressof(p->first));
   BOOST_TRY{
      (dispatch_uses_allocator)(construct_alloc, arg_alloc, dtl::addressof(p->second));
   }
   BOOST_CATCH(...) {
      allocator_traits<ConstructAlloc>::destroy(construct_alloc, dtl::addressof(p->first));
      BOOST_RETHROW
   }
   BOOST_CATCH_END
}


template < typename ConstructAlloc
         , typename ArgAlloc
         , class Pair, class U, class V>
BOOST_CONTAINER_DOC1ST(void, typename dtl::enable_if<dtl::is_pair<Pair> BOOST_MOVE_I void>::type)
   dispatch_uses_allocator
   ( ConstructAlloc & construct_alloc
   , BOOST_FWD_REF(ArgAlloc) arg_alloc
   , Pair* p, BOOST_FWD_REF(U) x, BOOST_FWD_REF(V) y)
{
   (dispatch_uses_allocator)(construct_alloc, arg_alloc, dtl::addressof(p->first), ::boost::forward<U>(x));
   BOOST_TRY{
      (dispatch_uses_allocator)(construct_alloc, arg_alloc, dtl::addressof(p->second), ::boost::forward<V>(y));
   }
   BOOST_CATCH(...){
      allocator_traits<ConstructAlloc>::destroy(construct_alloc, dtl::addressof(p->first));
      BOOST_RETHROW
   }
   BOOST_CATCH_END
}

template < typename ConstructAlloc
         , typename ArgAlloc
         , class Pair, class Pair2>
BOOST_CONTAINER_DOC1ST(void, typename dtl::enable_if< dtl::is_pair<Pair> BOOST_MOVE_I void >::type)
   dispatch_uses_allocator
   (ConstructAlloc & construct_alloc
   , BOOST_FWD_REF(ArgAlloc) arg_alloc
   , Pair* p, Pair2& x)
{  (dispatch_uses_allocator)(construct_alloc, arg_alloc, p, x.first, x.second);  }

template < typename ConstructAlloc
         , typename ArgAlloc
         , class Pair, class Pair2>
typename dtl::enable_if_and
   < void
   , dtl::is_pair<Pair>
   , dtl::not_<boost::move_detail::is_reference<Pair2> > >::type //This is needed for MSVC10 and ambiguous overloads
   dispatch_uses_allocator
   (ConstructAlloc & construct_alloc
      , BOOST_FWD_REF(ArgAlloc) arg_alloc
      , Pair* p, BOOST_RV_REF_BEG Pair2 BOOST_RV_REF_END x)
{  (dispatch_uses_allocator)(construct_alloc, arg_alloc, p, ::boost::move(x.first), ::boost::move(x.second));  }


//piecewise construction from boost::tuple
#define BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_BOOST_TUPLE_CODE(N,M)\
template< typename ConstructAlloc, typename ArgAlloc, class Pair \
        , template<class, class, class, class, class, class, class, class, class, class> class BoostTuple \
         BOOST_MOVE_I_IF(BOOST_MOVE_OR(N,M)) BOOST_MOVE_CLASS##N BOOST_MOVE_I_IF(BOOST_MOVE_AND(N,M)) BOOST_MOVE_CLASSQ##M > \
typename dtl::enable_if< dtl::is_pair<Pair> BOOST_MOVE_I void>::type\
   dispatch_uses_allocator( ConstructAlloc & construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, Pair* pair, piecewise_construct_t\
      , BoostTuple<BOOST_MOVE_TARG##N  BOOST_MOVE_I##N BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(10,N),::boost::tuples::null_type)> p\
      , BoostTuple<BOOST_MOVE_TARGQ##M BOOST_MOVE_I##M BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(10,M),::boost::tuples::null_type)> q)\
{\
   (void)p; (void)q;\
   (dispatch_uses_allocator)\
      (construct_alloc, arg_alloc, dtl::addressof(pair->first) BOOST_MOVE_I_IF(N) BOOST_MOVE_TMPL_GET##N);\
   BOOST_TRY{\
      (dispatch_uses_allocator)\
         (construct_alloc, arg_alloc, dtl::addressof(pair->second) BOOST_MOVE_I_IF(M) BOOST_MOVE_TMPL_GETQ##M);\
   }\
   BOOST_CATCH(...) {\
      allocator_traits<ConstructAlloc>::destroy(construct_alloc, dtl::addressof(pair->first));\
      BOOST_RETHROW\
   }\
   BOOST_CATCH_END\
}\
//
BOOST_MOVE_ITER2D_0TOMAX(9, BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_BOOST_TUPLE_CODE)
#undef BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_BOOST_TUPLE_CODE

//piecewise construction from Std Tuple
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template< typename ConstructAlloc, typename ArgAlloc, class Pair
           , template<class ...> class Tuple, class... Args1, class... Args2, size_t... Indexes1, size_t... Indexes2>
   void dispatch_uses_allocator_index( ConstructAlloc & construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, Pair* pair
                                    , Tuple<Args1...>& t1, Tuple<Args2...>& t2, index_tuple<Indexes1...>, index_tuple<Indexes2...>)
   {
      (void)t1; (void)t2;
      (dispatch_uses_allocator)(construct_alloc, arg_alloc, dtl::addressof(pair->first), ::boost::forward<Args1>(get<Indexes1>(t1))...);
      BOOST_TRY{
         (dispatch_uses_allocator)(construct_alloc, arg_alloc, dtl::addressof(pair->second), ::boost::forward<Args2>(get<Indexes2>(t2))...);
      }
      BOOST_CATCH(...){
         allocator_traits<ConstructAlloc>::destroy(construct_alloc, dtl::addressof(pair->first));
         BOOST_RETHROW
      }
      BOOST_CATCH_END
   }

   template< typename ConstructAlloc, typename ArgAlloc, class Pair
           , template<class ...> class Tuple, class... Args1, class... Args2>
   typename dtl::enable_if< dtl::is_pair<Pair>, void >::type
      dispatch_uses_allocator( ConstructAlloc & construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, Pair* pair, piecewise_construct_t
                             , Tuple<Args1...> t1, Tuple<Args2...> t2)
   {
      (dispatch_uses_allocator_index)( construct_alloc, arg_alloc, pair, t1, t2
                                     , typename build_number_seq<sizeof...(Args1)>::type()
                                     , typename build_number_seq<sizeof...(Args2)>::type());
   }

#elif defined(BOOST_MSVC) && (_CPPLIB_VER == 520)

   //MSVC 2010 tuple implementation
   #define BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_MSVC2010_TUPLE_CODE(N,M)\
   template< typename ConstructAlloc, typename ArgAlloc, class Pair\
           , template<class, class, class, class, class, class, class, class, class, class> class StdTuple\
            BOOST_MOVE_I_IF(BOOST_MOVE_OR(N,M)) BOOST_MOVE_CLASS##N BOOST_MOVE_I_IF(BOOST_MOVE_AND(N,M)) BOOST_MOVE_CLASSQ##M > \
   typename dtl::enable_if< dtl::is_pair<Pair> BOOST_MOVE_I void>::type\
      dispatch_uses_allocator(ConstructAlloc & construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, Pair* pair, piecewise_construct_t\
                           , StdTuple<BOOST_MOVE_TARG##N  BOOST_MOVE_I##N BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(10,N),::std::tr1::_Nil)> p\
                           , StdTuple<BOOST_MOVE_TARGQ##M BOOST_MOVE_I##M BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(10,M),::std::tr1::_Nil)> q)\
   {\
      (void)p; (void)q;\
      (dispatch_uses_allocator)\
         (construct_alloc, arg_alloc, dtl::addressof(pair->first) BOOST_MOVE_I_IF(N) BOOST_MOVE_GET_IDX##N);\
      BOOST_TRY{\
         (dispatch_uses_allocator)\
            (construct_alloc, arg_alloc, dtl::addressof(pair->second) BOOST_MOVE_I_IF(M) BOOST_MOVE_GET_IDXQ##M);\
      }\
      BOOST_CATCH(...) {\
         allocator_traits<ConstructAlloc>::destroy(construct_alloc, dtl::addressof(pair->first));\
         BOOST_RETHROW\
      }\
      BOOST_CATCH_END\
   }\
   //
   BOOST_MOVE_ITER2D_0TOMAX(9, BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_MSVC2010_TUPLE_CODE)
   #undef BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_MSVC2010_TUPLE_CODE

#elif defined(BOOST_MSVC) && (_CPPLIB_VER == 540)
   #if _VARIADIC_MAX >= 9
   #define BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_MSVC2012_TUPLE_MAX_IT 9
   #else
   #define BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_MSVC2012_TUPLE_MAX_IT BOOST_MOVE_ADD(_VARIADIC_MAX, 1)
   #endif

   //MSVC 2012 tuple implementation
   #define BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_MSVC2012_TUPLE_CODE(N,M)\
   template< typename ConstructAlloc, typename ArgAlloc, class Pair\
            , template<BOOST_MOVE_REPEAT(_VARIADIC_MAX, class), class, class, class> class StdTuple \
            BOOST_MOVE_I_IF(BOOST_MOVE_OR(N,M)) BOOST_MOVE_CLASS##N BOOST_MOVE_I_IF(BOOST_MOVE_AND(N,M)) BOOST_MOVE_CLASSQ##M > \
   typename dtl::enable_if< dtl::is_pair<Pair> BOOST_MOVE_I void>::type\
      dispatch_uses_allocator\
         ( ConstructAlloc & construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, Pair* pair, piecewise_construct_t\
         , StdTuple<BOOST_MOVE_TARG##N  BOOST_MOVE_I##N BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(BOOST_MOVE_ADD(_VARIADIC_MAX, 3),N),::std::_Nil) > p\
         , StdTuple<BOOST_MOVE_TARGQ##M BOOST_MOVE_I##M BOOST_MOVE_REPEAT(BOOST_MOVE_SUB(BOOST_MOVE_ADD(_VARIADIC_MAX, 3),M),::std::_Nil) > q)\
   {\
      (void)p; (void)q;\
      (dispatch_uses_allocator)\
         (construct_alloc, arg_alloc, dtl::addressof(pair->first) BOOST_MOVE_I_IF(N) BOOST_MOVE_GET_IDX##N);\
      BOOST_TRY{\
         (dispatch_uses_allocator)\
            (construct_alloc, arg_alloc, dtl::addressof(pair->second) BOOST_MOVE_I_IF(M) BOOST_MOVE_GET_IDXQ##M);\
      }\
      BOOST_CATCH(...) {\
         allocator_traits<ConstructAlloc>::destroy(construct_alloc, dtl::addressof(pair->first));\
         BOOST_RETHROW\
      }\
      BOOST_CATCH_END\
   }\
   //
   BOOST_MOVE_ITER2D_0TOMAX(BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_MSVC2012_TUPLE_MAX_IT, BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_MSVC2012_TUPLE_CODE)
   #undef BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_MSVC2010_TUPLE_CODE
   #undef BOOST_DISPATCH_USES_ALLOCATOR_PIECEWISE_CONSTRUCT_MSVC2012_TUPLE_MAX_IT

#endif   //!defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template < typename ConstructAlloc
         , typename ArgAlloc
         , class Pair, class KeyType, class ... Args>
typename dtl::enable_if< dtl::is_pair<Pair>, void >::type
   dispatch_uses_allocator
   (ConstructAlloc & construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, Pair* p, try_emplace_t, BOOST_FWD_REF(KeyType) k, BOOST_FWD_REF(Args) ...args)
{
   (dispatch_uses_allocator)(construct_alloc, arg_alloc, dtl::addressof(p->first), ::boost::forward<KeyType>(k));
   BOOST_TRY{
      (dispatch_uses_allocator)(construct_alloc, arg_alloc, dtl::addressof(p->second), ::boost::forward<Args>(args)...);
   }
   BOOST_CATCH(...) {
      allocator_traits<ConstructAlloc>::destroy(construct_alloc, dtl::addressof(p->first));
      BOOST_RETHROW
   }
   BOOST_CATCH_END
}

#else

#define BOOST_CONTAINER_DISPATCH_USES_ALLOCATOR_PAIR_TRY_EMPLACE_CODE(N) \
   template <typename ConstructAlloc, typename ArgAlloc, class Pair, class KeyType BOOST_MOVE_I##N BOOST_MOVE_CLASS##N >\
   inline typename dtl::enable_if\
      < dtl::is_pair<Pair> BOOST_MOVE_I void >::type\
      dispatch_uses_allocator\
      (ConstructAlloc &construct_alloc, BOOST_FWD_REF(ArgAlloc) arg_alloc, Pair* p, try_emplace_t, \
       BOOST_FWD_REF(KeyType) k BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      (dispatch_uses_allocator)(construct_alloc, arg_alloc, dtl::addressof(p->first), ::boost::forward<KeyType>(k));\
      BOOST_TRY{\
         (dispatch_uses_allocator)(construct_alloc, arg_alloc, dtl::addressof(p->second) BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
      }\
      BOOST_CATCH(...) {\
         allocator_traits<ConstructAlloc>::destroy(construct_alloc, dtl::addressof(p->first));\
         BOOST_RETHROW\
      }\
      BOOST_CATCH_END\
   }\
//
BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_DISPATCH_USES_ALLOCATOR_PAIR_TRY_EMPLACE_CODE)
#undef BOOST_CONTAINER_DISPATCH_USES_ALLOCATOR_PAIR_TRY_EMPLACE_CODE

#endif   //!defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

}  //namespace dtl

}} // namespace boost { namespace container {

#include <boost/container/detail/config_end.hpp>

#endif //  BOOST_CONTAINER_DISPATCH_USES_ALLOCATOR_HPP

/* dispatch_uses_allocator.hpp
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
*/
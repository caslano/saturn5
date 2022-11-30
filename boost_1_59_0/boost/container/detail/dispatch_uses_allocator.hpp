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
#include <boost/container/detail/is_pair.hpp>
#include <boost/container/detail/type_traits.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#else
#include <boost/container/detail/variadic_templates_tools.hpp>
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
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_and
   < void
   , dtl::is_not_pair<T>
   , dtl::not_< uses_allocator<T, typename remove_cvref<ArgAlloc>::type > >
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
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_and
   < void
   , dtl::is_not_pair<T>
   , uses_allocator<T, typename remove_cvref<ArgAlloc>::type>
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
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_and
   < void
   , dtl::is_not_pair<T>
   , uses_allocator<T, typename remove_cvref<ArgAlloc>::type>
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
   BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_and\
      < void\
      , dtl::is_not_pair<T>\
      , dtl::not_<uses_allocator<T, typename remove_cvref<ArgAlloc>::type> >\
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
   BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_and\
      < void\
      , dtl::is_not_pair<T>\
      , uses_allocator<T, typename remove_cvref<ArgAlloc>::type>\
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
   BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_and\
      < void\
      , dtl::is_not_pair<T>\
      , uses_allocator<T, typename remove_cvref<ArgAlloc>::type>\
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
   dispatch_uses_allocator(construct_alloc, arg_alloc, dtl::addressof(p->first));
   BOOST_TRY{
      dispatch_uses_allocator(construct_alloc, arg_alloc, dtl::addressof(p->second));
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
   dispatch_uses_allocator(construct_alloc, arg_alloc, dtl::addressof(p->first), ::boost::forward<U>(x));
   BOOST_TRY{
      dispatch_uses_allocator(construct_alloc, arg_alloc, dtl::addressof(p->second), ::boost::forward<V>(y));
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
{  dispatch_uses_allocator(construct_alloc, arg_alloc, p, x.first, x.second);  }

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
{  dispatch_uses_allocator(construct_alloc, arg_alloc, p, ::boost::move(x.first), ::boost::move(x.second));  }


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
   dispatch_uses_allocator\
      (construct_alloc, arg_alloc, dtl::addressof(pair->first) BOOST_MOVE_I_IF(N) BOOST_MOVE_TMPL_GET##N);\
   BOOST_TRY{\
      dispatch_uses_allocator\
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
      dispatch_uses_allocator(construct_alloc, arg_alloc, dtl::addressof(pair->first), ::boost::forward<Args1>(get<Indexes1>(t1))...);
      BOOST_TRY{
         dispatch_uses_allocator(construct_alloc, arg_alloc, dtl::addressof(pair->second), ::boost::forward<Args2>(get<Indexes2>(t2))...);
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
      dispatch_uses_allocator\
         (construct_alloc, arg_alloc, dtl::addressof(pair->first) BOOST_MOVE_I_IF(N) BOOST_MOVE_GET_IDX##N);\
      BOOST_TRY{\
         dispatch_uses_allocator\
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
      dispatch_uses_allocator\
         (construct_alloc, arg_alloc, dtl::addressof(pair->first) BOOST_MOVE_I_IF(N) BOOST_MOVE_GET_IDX##N);\
      BOOST_TRY{\
         dispatch_uses_allocator\
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
   dispatch_uses_allocator(construct_alloc, arg_alloc, dtl::addressof(p->first), ::boost::forward<KeyType>(k));
   BOOST_TRY{
      dispatch_uses_allocator(construct_alloc, arg_alloc, dtl::addressof(p->second), ::boost::forward<Args>(args)...);
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
      dispatch_uses_allocator(construct_alloc, arg_alloc, dtl::addressof(p->first), ::boost::forward<KeyType>(k));\
      BOOST_TRY{\
         dispatch_uses_allocator(construct_alloc, arg_alloc, dtl::addressof(p->second) BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
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
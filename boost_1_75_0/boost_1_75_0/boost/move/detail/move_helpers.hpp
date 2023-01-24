//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2010-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_MOVE_HELPERS_HPP
#define BOOST_MOVE_MOVE_HELPERS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/move/detail/type_traits.hpp>

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#define BOOST_MOVE_CATCH_CONST(U)  \
   typename ::boost::move_detail::if_< ::boost::move_detail::is_class<U>, BOOST_CATCH_CONST_RLVALUE(U), const U &>::type
#define BOOST_MOVE_CATCH_RVALUE(U)\
   typename ::boost::move_detail::if_< ::boost::move_detail::is_class<U>, BOOST_RV_REF(U), ::boost::move_detail::nat>::type
#define BOOST_MOVE_CATCH_FWD(U) BOOST_FWD_REF(U)
#else
#define BOOST_MOVE_CATCH_CONST(U)  const U &
#define BOOST_MOVE_CATCH_RVALUE(U) U &&
#define BOOST_MOVE_CATCH_FWD(U)    U &&
#endif

////////////////////////////////////////
//
// BOOST_MOVE_CONVERSION_AWARE_CATCH
//
////////////////////////////////////////

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES

   template<class RETURN_VALUE, class BOOST_MOVE_TEMPL_PARAM, class TYPE>
   struct boost_move_conversion_aware_catch_1
      : public ::boost::move_detail::enable_if_and
                        < RETURN_VALUE
                        , ::boost::move_detail::is_same<TYPE, BOOST_MOVE_TEMPL_PARAM>
                        , ::boost::move_detail::is_class<TYPE>
                        , ::boost::has_move_emulation_disabled<BOOST_MOVE_TEMPL_PARAM>
                        >
   {};

   template<class RETURN_VALUE, class BOOST_MOVE_TEMPL_PARAM, class TYPE>
   struct boost_move_conversion_aware_catch_2
      : public ::boost::move_detail::disable_if_or
                        < RETURN_VALUE
                        , ::boost::move_detail::is_same<TYPE, BOOST_MOVE_TEMPL_PARAM> 
                        , ::boost::move_detail::is_rv_impl<BOOST_MOVE_TEMPL_PARAM>
                        , ::boost::move_detail::and_
                                    < ::boost::move_detail::is_rv_impl<BOOST_MOVE_TEMPL_PARAM>
                                    , ::boost::move_detail::is_class<BOOST_MOVE_TEMPL_PARAM>
                                    >
                        >
   {};

   #define BOOST_MOVE_CONVERSION_AWARE_CATCH_COMMON(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION)\
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(BOOST_MOVE_CATCH_CONST(TYPE) x)\
      {  return FWD_FUNCTION(static_cast<const TYPE&>(x)); }\
      \
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(BOOST_MOVE_CATCH_RVALUE(TYPE) x) \
      {  return FWD_FUNCTION(::boost::move(x));  }\
      \
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(TYPE &x)\
      {  return FWD_FUNCTION(const_cast<const TYPE &>(x)); }\
   //
   #if defined(BOOST_MOVE_HELPERS_RETURN_SFINAE_BROKEN)
      #define BOOST_MOVE_CONVERSION_AWARE_CATCH(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION)\
         BOOST_MOVE_CONVERSION_AWARE_CATCH_COMMON(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION)\
         \
         template<class BOOST_MOVE_TEMPL_PARAM>\
         BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(const BOOST_MOVE_TEMPL_PARAM &u,\
            typename boost_move_conversion_aware_catch_1< ::boost::move_detail::nat, BOOST_MOVE_TEMPL_PARAM, TYPE>::type* = 0)\
         { return FWD_FUNCTION(u); }\
         \
         template<class BOOST_MOVE_TEMPL_PARAM>\
         BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(const BOOST_MOVE_TEMPL_PARAM &u,\
            typename boost_move_conversion_aware_catch_2< ::boost::move_detail::nat, BOOST_MOVE_TEMPL_PARAM, TYPE>::type* = 0)\
         {\
            TYPE t((u));\
            return FWD_FUNCTION(::boost::move(t));\
         }\
      //
   #else
      #define BOOST_MOVE_CONVERSION_AWARE_CATCH(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION)\
         BOOST_MOVE_CONVERSION_AWARE_CATCH_COMMON(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION)\
         \
         template<class BOOST_MOVE_TEMPL_PARAM>\
         BOOST_MOVE_FORCEINLINE typename boost_move_conversion_aware_catch_1<RETURN_VALUE, BOOST_MOVE_TEMPL_PARAM, TYPE>::type\
            PUB_FUNCTION(const BOOST_MOVE_TEMPL_PARAM &u)\
         { return FWD_FUNCTION(u); }\
         \
         template<class BOOST_MOVE_TEMPL_PARAM>\
         BOOST_MOVE_FORCEINLINE typename boost_move_conversion_aware_catch_2<RETURN_VALUE, BOOST_MOVE_TEMPL_PARAM, TYPE>::type\
            PUB_FUNCTION(const BOOST_MOVE_TEMPL_PARAM &u)\
         {\
            TYPE t((u));\
            return FWD_FUNCTION(::boost::move(t));\
         }\
      //
   #endif
#elif (defined(_MSC_VER) && (_MSC_VER == 1600))

   #define BOOST_MOVE_CONVERSION_AWARE_CATCH(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION)\
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(BOOST_MOVE_CATCH_CONST(TYPE) x)\
      {  return FWD_FUNCTION(static_cast<const TYPE&>(x)); }\
      \
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(BOOST_MOVE_CATCH_RVALUE(TYPE) x) \
      {  return FWD_FUNCTION(::boost::move(x));  }\
      \
      template<class BOOST_MOVE_TEMPL_PARAM>\
      BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c\
                        < !::boost::move_detail::is_same<TYPE, BOOST_MOVE_TEMPL_PARAM>::value\
                        , RETURN_VALUE >::type\
      PUB_FUNCTION(const BOOST_MOVE_TEMPL_PARAM &u)\
      {\
         TYPE t((u));\
         return FWD_FUNCTION(::boost::move(t));\
      }\
   //

#else    //BOOST_NO_CXX11_RVALUE_REFERENCES

   #define BOOST_MOVE_CONVERSION_AWARE_CATCH(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION)\
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(BOOST_MOVE_CATCH_CONST(TYPE) x)\
      {  return FWD_FUNCTION(x); }\
      \
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(BOOST_MOVE_CATCH_RVALUE(TYPE) x) \
      {  return FWD_FUNCTION(::boost::move(x));  }\
   //

#endif   //BOOST_NO_CXX11_RVALUE_REFERENCES

////////////////////////////////////////
//
// BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG
//
////////////////////////////////////////

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES

   template<class RETURN_VALUE, class BOOST_MOVE_TEMPL_PARAM, class UNLESS_CONVERTIBLE_TO, class TYPE>
   struct boost_move_conversion_aware_catch_1arg_1
      : public ::boost::move_detail::enable_if_and
                        < RETURN_VALUE
                        , ::boost::move_detail::not_< ::boost::move_detail::is_same_or_convertible<BOOST_MOVE_TEMPL_PARAM, UNLESS_CONVERTIBLE_TO> >
                        , ::boost::move_detail::is_same<TYPE, BOOST_MOVE_TEMPL_PARAM>
                        , ::boost::has_move_emulation_disabled<BOOST_MOVE_TEMPL_PARAM>
                        >
   {};

   template<class RETURN_VALUE, class BOOST_MOVE_TEMPL_PARAM, class UNLESS_CONVERTIBLE_TO, class TYPE>
   struct boost_move_conversion_aware_catch_1arg_2
      : public ::boost::move_detail::disable_if_or
                        < RETURN_VALUE
                        , ::boost::move_detail::is_same_or_convertible< BOOST_MOVE_TEMPL_PARAM, UNLESS_CONVERTIBLE_TO>
                        , ::boost::move_detail::is_rv_impl<BOOST_MOVE_TEMPL_PARAM>
                        , ::boost::move_detail::is_same<TYPE, BOOST_MOVE_TEMPL_PARAM>
                        >
   {};

   #define BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG_COMMON(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION, ARG1, UNLESS_CONVERTIBLE_TO)\
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(ARG1 arg1, BOOST_MOVE_CATCH_CONST(TYPE) x)\
      {  return FWD_FUNCTION(arg1, static_cast<const TYPE&>(x)); }\
      \
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(ARG1 arg1, BOOST_MOVE_CATCH_RVALUE(TYPE) x) \
      {  return FWD_FUNCTION(arg1, ::boost::move(x));  }\
      \
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(ARG1 arg1, TYPE &x)\
      {  return FWD_FUNCTION(arg1, const_cast<const TYPE &>(x)); }\
   //
   #if defined(BOOST_MOVE_HELPERS_RETURN_SFINAE_BROKEN)
      #define BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION, ARG1, UNLESS_CONVERTIBLE_TO)\
         BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG_COMMON(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION, ARG1, UNLESS_CONVERTIBLE_TO)\
         \
         template<class BOOST_MOVE_TEMPL_PARAM>\
         BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(ARG1 arg1, const BOOST_MOVE_TEMPL_PARAM &u,\
            typename boost_move_conversion_aware_catch_1arg_1<void, BOOST_MOVE_TEMPL_PARAM, UNLESS_CONVERTIBLE_TO, TYPE>::type* = 0)\
         { return FWD_FUNCTION(arg1, u); }\
         \
         template<class BOOST_MOVE_TEMPL_PARAM>\
         BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(ARG1 arg1, const BOOST_MOVE_TEMPL_PARAM &u,\
            typename boost_move_conversion_aware_catch_1arg_2<void, BOOST_MOVE_TEMPL_PARAM, UNLESS_CONVERTIBLE_TO, TYPE>::type* = 0)\
         {\
            TYPE t((u));\
            return FWD_FUNCTION(arg1, ::boost::move(t));\
         }\
      //
   #else
      #define BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION, ARG1, UNLESS_CONVERTIBLE_TO)\
         BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG_COMMON(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION, ARG1, UNLESS_CONVERTIBLE_TO)\
         \
         template<class BOOST_MOVE_TEMPL_PARAM>\
         BOOST_MOVE_FORCEINLINE typename boost_move_conversion_aware_catch_1arg_1<RETURN_VALUE, BOOST_MOVE_TEMPL_PARAM, UNLESS_CONVERTIBLE_TO, TYPE>::type\
            PUB_FUNCTION(ARG1 arg1, const BOOST_MOVE_TEMPL_PARAM &u)\
         { return FWD_FUNCTION(arg1, u); }\
         \
         template<class BOOST_MOVE_TEMPL_PARAM>\
         BOOST_MOVE_FORCEINLINE typename boost_move_conversion_aware_catch_1arg_2<RETURN_VALUE, BOOST_MOVE_TEMPL_PARAM, UNLESS_CONVERTIBLE_TO, TYPE>::type\
            PUB_FUNCTION(ARG1 arg1, const BOOST_MOVE_TEMPL_PARAM &u)\
         {\
            TYPE t((u));\
            return FWD_FUNCTION(arg1, ::boost::move(t));\
         }\
      //
   #endif

#elif (defined(_MSC_VER) && (_MSC_VER == 1600))

   #define BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION, ARG1, UNLESS_CONVERTIBLE_TO)\
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(ARG1 arg1, BOOST_MOVE_CATCH_CONST(TYPE) x)\
      {  return FWD_FUNCTION(arg1, static_cast<const TYPE&>(x)); }\
      \
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(ARG1 arg1, BOOST_MOVE_CATCH_RVALUE(TYPE) x) \
      {  return FWD_FUNCTION(arg1, ::boost::move(x));  }\
      \
      template<class BOOST_MOVE_TEMPL_PARAM>\
      BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::disable_if_or\
                        < RETURN_VALUE \
                        , ::boost::move_detail::is_same<TYPE, BOOST_MOVE_TEMPL_PARAM> \
                        , ::boost::move_detail::is_same_or_convertible<BOOST_MOVE_TEMPL_PARAM, UNLESS_CONVERTIBLE_TO> \
                        >::type\
      PUB_FUNCTION(ARG1 arg1, const BOOST_MOVE_TEMPL_PARAM &u)\
      {\
         TYPE t((u));\
         return FWD_FUNCTION(arg1, ::boost::move(t));\
      }\
   //

#else

   #define BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(PUB_FUNCTION, TYPE, RETURN_VALUE, FWD_FUNCTION, ARG1, UNLESS_CONVERTIBLE_TO)\
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(ARG1 arg1, BOOST_MOVE_CATCH_CONST(TYPE) x)\
      {  return FWD_FUNCTION(arg1, static_cast<const TYPE&>(x)); }\
      \
      BOOST_MOVE_FORCEINLINE RETURN_VALUE PUB_FUNCTION(ARG1 arg1, BOOST_MOVE_CATCH_RVALUE(TYPE) x) \
      {  return FWD_FUNCTION(arg1, ::boost::move(x));  }\
   //

#endif

#endif //#ifndef BOOST_MOVE_MOVE_HELPERS_HPP

/* move_helpers.hpp
lERNlzU95C3QMt0BuvSPNh5iJWT8W6gefE6aSahOMwmZyh+0lz/qLJ+g5Wut8sTOo93ScVz6I5d1XOegX84RHphGQOBjTpeYskdoF+tAGDC4Xwft7zHQ397M8d/Pcbp6KwCPnDP72x4Pwxn/nU0BaolXQS3xKm7F7FCFrtiKoucQCQB/n7RCrlfWyoVik3eNHhDL1FlagLorNVM+n95b79VUEozkavr8j85xff7n5zLo8wlPUdGW6cwkdN52ZnIDZL57nq3hieedZx5jsDiTR51mOj7Nqf8+b+ORFkLmAY7nnkF4bhak5/AxjOaSWw4B1w3DgV8bA/wayEUg51vaSO7/cZ7bXZwA4DIk75/oPR5E/zko9qltvdGYCSkaLSH1Cr3IQ/iTpTp7BWjIMTk83i09IbcpJVKnukorkRrEuLAIeKMWzO5LUlQaN4HW73qo33ioX3hI/ZoB73Aie8wD4HVI5/9EbVdtG+JW07iSsgBpu0u+SzL2YDeTPt636YLsHjw945jbAlPumJqhBdR49V2rZZNwxbclNNGonY7xJmWx915lqhrTXFhNKjv1Ot9X/nsD07HfUF6U10t3B+827gtVGK/gYINULpYJWW6QpNcAO+3zGlpcoXargWKlOKgZhrm/hTPuby1/5nZ6CwDYCek//5zmZ02HX7tNJZe5uphQtsmy1O1k/GzPn9Mtmok3QYuOjSj4HgY2JSW9
*/
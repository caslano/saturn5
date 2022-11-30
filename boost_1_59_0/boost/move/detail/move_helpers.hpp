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
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
*/
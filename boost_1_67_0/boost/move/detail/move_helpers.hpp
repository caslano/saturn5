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
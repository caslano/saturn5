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
tTh+mRMPrdkRYo/AWsf7vaq2Hu4Ftr7X8LdAB2dHbaSQeLgDziE75ABzB3mo0P5o1T/NrP8Sqd9Ace8G2PmNuaQDB+a/WIko346iLVQaYnkevZTG+UoqgkWkXViFoB92uaOjk0FJSo1dkDzdzpY8eYP/9cNVctVEqNjCIUdq/VZ/TaE4veZ1NN1P8Yyq00GRg2M2Ap2Gh4zjtSKvkWVwzBqKqI+URTz6qmAG/K9Rdj4YHczAU3v4Idgz9tl+TyOl8F9OPJt67co/jVeZy3aZTnHR2ztpwcrT6k5PdGRSpahFBClfvLSYHkhyqm3yY1rup8umqHGTsKxtOXYh/brcdHtTYF1TF7VhBYEKSEgJEA+tF0CScyR3rJZCMUORNLKe26rjMCH5Rj01u61eauv6seJpCWf7k+O1WjONdrOD5L9sJPoL8+IKHGBHo3mNxJdd+Y2Dumnh4XzTD+j0FfE3UN3g3/q6J960BxG6j8XgPfHwxkTTHqzj6bd5oytwS5wZSCcBrwfW8SH+VOCxulLrFD/uT6AQeA49mT3VBdmZzZhEuJOggkOsCviwbuqMlyWXs5qnQU++yfRvQa1d6s2h1zWHOfs76e9tInHcGGH3gm7rdZeH6fadu/zqf+Bj+fPbVOmY763zT9Y4wfTJd6ldELshMltGZR0RpOOWqSIedHLaRTTt1ewjmCnMLRQmI2SE6dH2vRTH17KdFi3p/QmoOehcgjXqL6wdK95x+tmHTuQ0Ya9TzZr7KAQyvA2LsXSLFvWe5TYcNhxPmQoBVK/fbFWRPIWdKIzlBW2K/edcakYOJMegFMND9tlWHq4gSFAQtBYUmDqZx7Cnntks9pwHrzzRcfTrjlkenjE0NvtKW1PvjY3ke48YK5O00SZThEN9yEt6hcIeOOFggK1zTwO+v2e6pPgUy0/nwMsgqujPqCLtqEI1qjheC1pVgP0BERtKjCpUVKGiCk/yYyKvfFartPj0QozIxTIKTzzUFDs/rI23UtzsSOG3UhyhHWtPO2b0K4ccuI/df+eH9dM++H86wqmf1s/5ky1R3ELNNJaYgUU30MOOtp10xQAQv2RU8arD1cXtHfSuuXy8Nlm+m14a9Yd+zGLGPZwg1FXzZDz8bDz8XDz8QjzcGw+/Eg+/Gg//fU48/Nri8Bs72nYZJTJxBRLL8d76VGmcHxIcXR+pbA93NWhun4tqQZVyW05zd9q+5ylcwUySBtUDmHgY0tZNDG/0dO03LltQuUV6rLZMBJXlOxnsi/9sySr79rGqwXD3aRJgYPM5o7rIedAJcsP2IVxdYN1OGrRbqMbAuo5GrYdqIGBDXfX62X9BIeLk+Eit16y/nVHWoP/kaMPhjQqnmuW4bTJppUH+r0kCeOBzJ6/iYiZofzGT8FIZjd2GyVSfK4mZ5Lm0qSyaTvfUC3AAU4Ar5uMBP+TGqtrfrCpxLuQ4R5WykJHhEx3NZcZIcoTDtLkcd7T2upmZPcPQZVk+yR5SxaMfZUKyN+1k5UjWYCYrl2Sa222NJrNvvhngvrFca4nCc8KR/70KT2s9egRJ8DjZat9fdaQ2xeI4Ov3oe5l0/MYtItppZiwhZsVRRhdVgLdVgLdhpEKQZpmDXbz6jEdapik0rNwxPwLg2RGaFF5W+llm2THVXwaY3v8+233h+wLr7LuieGjxBDZNRgsz2BVMJz6IO2Xx6UGj8Ao0houFA3W+lgTd/dLf0RiAJN39Fu62Gs7HWg9uIvk54sKffq4gS3+BqOk+iFKtZ+BX7iBwm3cQDMP5mXlfNElm92ElIilz/ccxJ9S2bB+v8hMYBQUOHuIi33bnwOcoogr603d6qta2nOFV9Rm8fkKO/PU=
*/
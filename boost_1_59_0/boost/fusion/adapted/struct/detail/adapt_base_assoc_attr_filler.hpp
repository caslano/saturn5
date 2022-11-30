/*=============================================================================
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_ADAPT_BASE_ASSOC_ATTR_FILLER_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_ADAPT_BASE_ASSOC_ATTR_FILLER_HPP

#include <boost/config.hpp>

#include <boost/fusion/adapted/struct/detail/adapt_auto.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base_attr_filler.hpp>

#include <boost/mpl/aux_/preprocessor/token_equal.hpp>

#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/elem.hpp>

#if BOOST_PP_VARIADICS

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0(...)                           \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAP_ATTR(__VA_ARGS__)                      \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_1

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_1(...)                           \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAP_ATTR(__VA_ARGS__)                      \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAP_ATTR(...)                          \
  BOOST_PP_IIF(                                                                 \
      BOOST_MPL_PP_TOKEN_EQUAL(auto, BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__)),   \
      ((2,                                                                      \
          (BOOST_PP_VARIADIC_ELEM(1, __VA_ARGS__),                              \
           BOOST_PP_VARIADIC_ELEM(2, __VA_ARGS__)))),                           \
      ((BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),                                    \
          (__VA_ARGS__)))                                                       \
    )

#else // BOOST_PP_VARIADICS


#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0(X, Y, Z)                       \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAP_ATTR(X, Y, Z)                          \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_1

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_1(X, Y, Z)                       \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAP_ATTR(X, Y, Z)                          \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAP_ATTR(X, Y, Z)                      \
    BOOST_PP_IIF(BOOST_MPL_PP_TOKEN_EQUAL(auto, X),                             \
      ((2, (Y,Z))),                                                             \
      ((3, (X,Y,Z)))                                                            \
    )

#endif // BOOST_PP_VARIADICS

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0_END
#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_1_END


#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAPPEDATTR_GET_KEY(ATTRIBUTE)          \
    BOOST_PP_TUPLE_ELEM(                                                        \
        BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE),                  \
        BOOST_PP_DEC(BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE)),    \
        BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR(ATTRIBUTE))

#endif

/* adapt_base_assoc_attr_filler.hpp
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
*/
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
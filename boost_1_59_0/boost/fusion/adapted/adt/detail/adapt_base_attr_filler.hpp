/*=============================================================================
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_DETAIL_ADAPT_BASE_ATTR_FILLER_HPP
#define BOOST_FUSION_ADAPTED_ADT_DETAIL_ADAPT_BASE_ATTR_FILLER_HPP

#include <boost/config.hpp>

#include <boost/fusion/adapted/struct/detail/adapt_auto.hpp>
#include <boost/fusion/adapted/struct/detail/preprocessor/is_seq.hpp>

#include <boost/mpl/aux_/preprocessor/token_equal.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/or.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/rest_n.hpp>


#define BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE)                      \
  BOOST_PP_TUPLE_ELEM(2, 0, ATTRIBUTE)

#define BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR(ATTRIBUTE)                           \
  BOOST_PP_TUPLE_ELEM(2, 1, ATTRIBUTE)

#if BOOST_PP_VARIADICS

#  define BOOST_FUSION_ADAPT_ADT_FILLER_0(...)                                  \
      BOOST_FUSION_ADAPT_ADT_FILLER(__VA_ARGS__)                                \
      BOOST_FUSION_ADAPT_ADT_FILLER_1

#  define BOOST_FUSION_ADAPT_ADT_FILLER_1(...)                                  \
      BOOST_FUSION_ADAPT_ADT_FILLER(__VA_ARGS__)                                \
      BOOST_FUSION_ADAPT_ADT_FILLER_0

#  define BOOST_FUSION_ADAPT_ADT_FILLER_0_END
#  define BOOST_FUSION_ADAPT_ADT_FILLER_1_END

// MSVC don't compile when using BOOST_PP_BITOR instead of BOOST_PP_OR.
#  define BOOST_FUSION_ADAPT_ADT_FILLER(...)                                    \
      BOOST_PP_IIF(                                                             \
          BOOST_PP_OR(                                                          \
              BOOST_MPL_PP_TOKEN_EQUAL(auto,                                    \
                  BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__)),                      \
              BOOST_MPL_PP_TOKEN_EQUAL(auto,                                    \
                  BOOST_PP_VARIADIC_ELEM(1, __VA_ARGS__))),                     \
                                                                                \
          BOOST_FUSION_ADAPT_ADT_WRAP_ATTR(                                     \
              BOOST_PP_VARIADIC_ELEM(2, __VA_ARGS__),                           \
              BOOST_FUSION_WORKAROUND_VARIADIC_EMPTINESS_LAST_ELEM(__VA_ARGS__) \
          ),                                                                    \
          BOOST_FUSION_ADAPT_ADT_WRAP_ATTR(__VA_ARGS__))

#  define BOOST_FUSION_ADAPT_ADT_WRAP_ATTR(...)                                 \
      ((BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), (__VA_ARGS__)))

#  define BOOST_FUSION_WORKAROUND_VARIADIC_EMPTINESS_LAST_ELEM(...)             \
  BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REST_N(                                        \
            BOOST_PP_DEC(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)),                  \
        BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))

#else // BOOST_PP_VARIADICS

#  define BOOST_FUSION_ADAPT_ADT_FILLER_0(A, B, C, D)                           \
      BOOST_FUSION_ADAPT_ADT_WRAP_ATTR(A,B,C,D)                                 \
      BOOST_FUSION_ADAPT_ADT_FILLER_1

#  define BOOST_FUSION_ADAPT_ADT_FILLER_1(A, B, C, D)                           \
      BOOST_FUSION_ADAPT_ADT_WRAP_ATTR(A,B,C,D)                                 \
      BOOST_FUSION_ADAPT_ADT_FILLER_0

#  define BOOST_FUSION_ADAPT_ADT_FILLER_0_END
#  define BOOST_FUSION_ADAPT_ADT_FILLER_1_END

#  define BOOST_FUSION_ADAPT_ADT_WRAP_ATTR(A, B, C, D)                          \
      BOOST_PP_IIF(BOOST_MPL_PP_TOKEN_EQUAL(auto, A),                           \
        ((2, (C,D))),                                                           \
        ((4, (A,B,C,D)))                                                        \
      )

#endif // BOOST_PP_VARIADICS

#endif

/* adapt_base_attr_filler.hpp
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
*/
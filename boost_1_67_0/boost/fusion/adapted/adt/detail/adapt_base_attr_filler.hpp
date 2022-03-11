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
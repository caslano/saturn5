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
B5tNgjaylQbB81uD3gSCxwcoBl29MHB0B9uROupYe31IoUkE9RMsiI/mAgGXhO7oBOHr2sXQZD0wBacK83WAJE09KOQY4QlE53Hzx54mHsWWyfR4rSxJtSFqMiBJegJ9DL7fCXr9kVDI1cauEMZNoI6zty7chkdrTtAryVYWHsm0B7I2PyXT+F/dx5DI9F6i0W09Gv3Vo9FRPRo91KPXR124TABdMyBjHWBan8KlNLQBt6Cn+jaAJUkRVq1Rs1d41YDEH2zrAiyZPhpodGCbckDNSNOYksL88bQVFr3N+G1/UgXC63/K80eKOnDZhmgo81NyrKfHEzXslLsHrgi1J2c0FFgOJgjICb8YRYpfU8qJemfUKt3AyTbWpKXgRfct+vWhvbWDcweLccISG4PeSY/QG9oWgpbcsMkHatZdZmZ6ZdXdpC0A2qYlCGMaEdiq9bg+0YtS213aGdqmnZlbXp3fOz8D5S0tHpifmZ/TG8wpRlV8VGhi5uD0jH32gI18B8BwbKkib6Lgr7eZFR1Wp6csg7Lc2+7CBovgPFZQOnSomHzrMPYIR3Bd2ACozaCJMa+fx7prXE4MIn0IoaAQM10I8hScOa3BVnMW67WyAWIONF3Bgdrh6aB3zYKX7PT6mmWWTQVjudVotfvDZb3RaTjbUizULZVEaxMWDCLFRu1jtFQAYLRDGyqwsp/VOq1PMaGPVEfRpbabTgyjx1JXMQe6quDo3PpQVqH/mH+8PmiXGVewdR71zsaWfGS/Jb83aG+gWlvFge0dVxURyvSkvDiKKuuaitA6jhhGt1X8LfLHbmbReNV80pPaMgIeXGIam5RC1wAVqGDBsSsFp51IumXlscWnDXzlWH3QapYm02saFBKZ/tOGTyBsMI5pqx3gVN0kYxOqhEmErFLKSqYCXR9iJAy4gfJCLqo/abiFwBEfwQAzD4STKOTTDqzgYnDbVptBrjhn3oAX0YfUleVB3Sd6YGDyMM5Cs4nbQEqHGnSIGJTtVLR6DPstDt5k4G8IRylEUSkgKDsvUqmvktbTT6z7NjF3xcNei8fAEJOb+sDnQGObfYweWi1NWJMNFIOOpcy4A8L32OSGKGx9fQSSZmKOjd/eINfvItTynutcL+UsjM3vRIpwMhYCS3shoGWGwFXT+VwDdtINHXaycYHrxlVEonULCssgVH1Yx0kbrQcFblSy2zmUkxXgIDWi2ACsppClBOAitNXUh8NBEjQnCyt5OApdyRue8grCtnALC/2gKDqLmcgOvFR8X7KYtUVOaNORblFYPGxocwJBbF66hg4ypRvAW2gH3C30A+4WGgI3rSMwKrQUcdNpqqUEs1rIWFtl96Ig2dLiQdqJIwp5mMdRHmY6BxCaxIKwnkafe9EY1s9wSi6CDIqHXURRdufj1TCEFvbqJ8/Y8HeodfgzEKWMCCHxpD0Di56+jrkIHs0Q1zxfIhrrt/FwYAB7/k/TbX3AjjaSYlgHYxwVilEstwZFg0ccPX31YZUuVUX5dHr1JoXGSiLKKsmkhqlqulKqspgKhoJCsWw/5mFahAgpdU8wzNFGNU/w8HQZ9gbaOcBcWpnFzaHCmeUDtdl5rOiWFu2RoAjEqBVCsEhgR5dWF2t4/c68PhcjkKjpomGsMM7q/uW56dly6YcqY98g4KELoJo4uBYkcs94JZnJ3KD5NAPYcaONGEftAxhOslnwQnzUrWFfN8xFVYiDxozyMMdcHAa8Tm+z3YDp2WpiyQ99lrMBH8VI76ONzTFah9oJCVLH6JjctcPhVeYMtDoFFB5GhzLaJwIMD4UNUr5Oat8fDfDdSTxCacvfR9BwHajWgsNBkDhGx+T2KeKpQHcxWjo=
*/
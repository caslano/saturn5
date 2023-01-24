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
Yd2/MFKjzTz44et/yu/Y/wcKAh+pIpguuDps+UM3Y23SvL+m9RzeTvf9CnPY4atc3gGxLm/cN+Qi1aYdfs4dtAeQZbxxXQz9zqFRs81GbIu2xRRJnOd3fClstfckPd21yQ47CSX/2IjJuYFfY0IGArw1R4LNs9HuBt0P3/RLe7m34Bfzqol+tGqQFnItHiIZUy6xa7W9cUw5bYBBA8jgRDggwzXCmg3UntehQVuDBm0nTj6NC8UyMAPRkLFk5SHqrWTj8kPkh5SM5zsZXSr1BbE36QuiNWeXrVa65N9KtuklxzWyfrm0PRS5wU4uYS4QjDZt7TLrxmZsJnB9wp/V62U51Gnj9zZmyfc28p/Jxhv4pxLvFON3/FirWy2J40T+Rjsvzh7kv7KNHP4ryxhENCxftreBgNcS/1dqUUKE0VhcywOvzOytS5GVU3SU5TCgWDuOWDyxoS6LPeuwuHWDZHHtBsni0g2SxS82qCwK23b6NyCQn5Dk9K+qyTnj9/c4DquAJHBJKwyacMTI5AGk2O6UAi0/xu3NFPbjC0HGXVag8WKhki1exvz692twnTCuGRm082kqEMfThdhoMmzCrgXk946/38rRluk94BaWDE/gIEJFWJ9Th3A5gP6fP7e3/D/Hkv2a+izar/Mnkf/nINP/8yCn+/Y75h3STf9PITNB6d8O1OgqRnYWArCjK54wWpvp2PST6WC0Nhll
*/
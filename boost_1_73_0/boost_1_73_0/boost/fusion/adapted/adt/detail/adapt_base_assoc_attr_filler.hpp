/*=============================================================================
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTER_ADT_DETAIL_ADAPT_BASE_ASSOC_ATTR_FILLER_HPP
#define BOOST_FUSION_ADAPTER_ADT_DETAIL_ADAPT_BASE_ASSOC_ATTR_FILLER_HPP

#include <boost/config.hpp>

#include <boost/fusion/adapted/struct/detail/adapt_auto.hpp>
#include <boost/fusion/adapted/adt/detail/adapt_base_attr_filler.hpp>

#include <boost/mpl/aux_/preprocessor/token_equal.hpp>

#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#if BOOST_PP_VARIADICS

#define BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0(...)                              \
    BOOST_FUSION_ADAPT_ASSOC_ADT_WRAP_ATTR(__VA_ARGS__)                         \
    BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_1

#define BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_1(...)                              \
    BOOST_FUSION_ADAPT_ASSOC_ADT_WRAP_ATTR(__VA_ARGS__)                         \
    BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0

#define BOOST_FUSION_ADAPT_ASSOC_ADT_WRAP_ATTR(...)                             \
    ((BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), (__VA_ARGS__)))

#else // BOOST_PP_VARIADICS

#define BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0(A, B, C, D, E)                    \
    BOOST_FUSION_ADAPT_ASSOC_ADT_WRAP_ATTR(A, B, C, D, E)                       \
    BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_1

#define BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_1(A, B, C, D, E)                    \
    BOOST_FUSION_ADAPT_ASSOC_ADT_WRAP_ATTR(A, B, C, D, E)                       \
    BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0

#define BOOST_FUSION_ADAPT_ASSOC_ADT_WRAP_ATTR(A, B, C, D, E)                   \
    BOOST_PP_IIF(BOOST_MPL_PP_TOKEN_EQUAL(auto, A),                             \
        ((3, (C,D,E))),                                                         \
        ((5, (A,B,C,D,E)))                                                      \
    )

#endif // BOOST_PP_VARIADICS

#define BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0_END
#define BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_1_END


#define BOOST_FUSION_ADAPT_ASSOC_ADT_WRAPPEDATTR_GET_KEY(ATTRIBUTE)             \
    BOOST_PP_TUPLE_ELEM(                                                        \
        BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE),                     \
        BOOST_PP_DEC(BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE)),       \
        BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR(ATTRIBUTE))

#endif

/* adapt_base_assoc_attr_filler.hpp
nzqHlw+/YxBEHiSq7MAR/j04QV3skDQM5tKSOqWT/tc9PxKFgfN2tAAJwJ6yifOl968XZMKlGb4Px5Pw7XgyXq6Q+47tdTMa7fTSDuOYoDebpqmnlFV4FQ0sDZxyPm/KuRgtrxdTeh9Orkfeghu8lLQLbRTPLt2JTjQaUTiJZtDTt4v7sKPZ8BLru+vp0OoVdbpnPVToUVqXo9E8nIzfjw5Pvf8AUEsDBAoAAAAIAC1nSlIRTSSaBQQAAOsIAAA1AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9URUxORVRPUFRJT05TLjNVVAUAAbZIJGCtVG1P40YQ/u5fMUo/JEE+B0olej1A9QXf4eKz09iBi4Rkbew13srxWrvrACr9751dOwQoFXw4R8k6s/PMyzMvzvUA9n7YYznaHLz5pOab4oPnFjQT/C+aqdcBafoA3QeB13i+w9UEdqiHdAzvQj3AyKDS3texfk/Td7i71kHqn4kGX6f6FSUdssdPeXMv2E2pYDQdw8HHj7/CB/h5/+DIhjNSM1pBrGi9ouLGhuPcSH4vyd2dI+mpDVQBqZxnBpOSSZC8ULdEUMD3imW0ljQHIiGnMhNshX9YDaqkULCKwjSaLf3wqw23JcvK
*/
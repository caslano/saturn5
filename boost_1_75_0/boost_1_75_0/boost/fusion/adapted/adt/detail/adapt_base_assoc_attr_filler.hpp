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
V/0tfesy/Tnr6q8J9CcW1vb3hWskwiRn+H4C3TAIpz1FzS3IEuIJwGqbEIAccbQ7r7sK7LLWBZDhfSVJmfhHyZqwSyPPIuy0GnkWQKega5W4WdrRFcTjbazCGSfxcCdyVqtk2NS702nIOWLAroErATyKihyW7wGUIU7wf3W5r5xH6//NPAY3+b+dx0ueWvP4/k19Hj1m1J7HoPP/i3nMbfx/O4+5XWvN4++R+jzGfFZ7Hh+c+1/Mozr+/3Yef3SpNY/Whnks+1TNg/BxxCuxIKk8/I0D8c53pqCnx/dwJFCpdFHe+FuBlvcxWoZCfFWseB+gZSsfoGU3E1rC6BVavgFjKRoSSbhJmMnxEeUaPnRWrWEKLCBFHfDzcfvKCLLMFocYvmi7x+PvEak9EgKsYeHd6lhOHyFNaxNqncMribRC/r80WppsWhqQf3xSix7yepSX1L0eQ74JWo94fT0aj7vMejybdtn16PrvpdbjyeF1rkd3S9B6dBh+JevxfWrwenwyndeD+LdYwb81kbzbnDNqZB7Q14Nytu0eUUsTrJsGva5/w4FMtgvV8ls93t4YMLmgfimezyAbXhYj/kI9HsSLXAQLo0UJCoJCEVesx5ud4PFHh+DiR4q/SsGFwesRq2tbxKKMpKrYtnt80IQPMwJDdB6xInG+sxh1XvQJY7nzDckMJ+jaerYbW0OMgFiBRffRCuRCM3lguCA2
*/
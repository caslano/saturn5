// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


/// \file relation/detail/static_access_builder.hpp
/// \brief Define macros to help building metafunctions

#ifndef BOOST_BIMAP_RELATION_DETAIL_STATIC_ACCESS_BUILDER_HPP
#define BOOST_BIMAP_RELATION_DETAIL_STATIC_ACCESS_BUILDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/is_tag_of_member_at.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/cat.hpp>



/******************************************************************************
              BIMAP SYMMETRIC STATIC ACCESS INTERFACE
*******************************************************************************

template< class Tag, class SYMETRIC_TYPE >
struct NAME
{
    -UNDEFINED BODY-;
};

******************************************************************************/


/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER(                          \
                                                                              \
        NAME,                                                                 \
        SYMMETRIC_TYPE,                                                       \
        LEFT_BODY,                                                            \
        RIGHT_BODY                                                            \
    )                                                                         \
                                                                              \
    template                                                                  \
    <                                                                         \
        class Tag,                                                            \
        class SYMMETRIC_TYPE,                                                 \
        class Enable = void                                                   \
    >                                                                         \
    struct NAME                                                               \
    {                                                                         \
        BOOST_BIMAP_STATIC_ERROR(                                             \
            BOOST_PP_CAT(NAME,_FAILURE),                                      \
            (SYMMETRIC_TYPE,Tag)                                              \
        );                                                                    \
    };                                                                        \
                                                                              \
    template< class Tag, class SYMMETRIC_TYPE >                               \
    struct NAME                                                               \
    <                                                                         \
        Tag, SYMMETRIC_TYPE,                                                  \
        BOOST_DEDUCED_TYPENAME enable_if                                      \
        <                                                                     \
            ::boost::bimaps::relation::support::is_tag_of_member_at_left      \
            <                                                                 \
                Tag,                                                          \
                SYMMETRIC_TYPE                                                \
            >                                                                 \
                                                                              \
        >::type                                                               \
    >                                                                         \
    {                                                                         \
        LEFT_BODY;                                                            \
    };                                                                        \
                                                                              \
    template< class Tag, class SYMMETRIC_TYPE >                               \
    struct NAME                                                               \
    <                                                                         \
        Tag, SYMMETRIC_TYPE,                                                  \
        BOOST_DEDUCED_TYPENAME enable_if                                      \
        <                                                                     \
            ::boost::bimaps::relation::support::is_tag_of_member_at_right     \
            <                                                                 \
                Tag,                                                          \
                SYMMETRIC_TYPE                                                \
            >                                                                 \
                                                                              \
        >::type                                                               \
    >                                                                         \
    {                                                                         \
        RIGHT_BODY;                                                           \
    };
/*===========================================================================*/


#endif // BOOST_BIMAP_RELATION_DETAIL_STATIC_ACCES_BUILDER_HPP



/* static_access_builder.hpp
vuY2plQyt7E5pX2X/XH8dvxdy9JIbvh9CBK3aAXaPYjXtd/tPSTvZa8wf1B+j12m6wOwy4xN5rcz5e2C2lefO2iol6dUZ7kb5wkav+l/IH/dlBiEdT+HWym+i2qsPkfQUI/PUHxm303rDc+jFu+xcSuFTbdXUbsqg1H2AdZeyhCUva9vqBVXmUc4r+I8wo8qzCOs4D79oae7nNy8vwT97TkXsAHLjHMBa+myNDlnkGXGuYAhLDPOBVSlLFPOUfvur1Im56id1mVyjlrZ+1Im09iky2Qaz7DMOD/wMV0m0/itLpNpzGSZcX7gRF0m58GN1GWyrI4c8Z4zWK7LZBo7dZlMY5suy5T3pstkGqt1mXweT+oy+TyW6DJZVqN1mSyrQSwzzhnsrsvkfbTVZfrcR12m70eiy+R9xOoyeR+huozvA/MDffQHjvroDxwzmUd40qSfcNZHP+GSj36CULz7CQ7Fu58Qpnj3CaaAa8Mon9Jfio+5hvPe85xreO8H1zfX0PfcO7M5c2Zz8n75cdSQWU75gb2X6yvh3+U8FX/2+y5Hw943G0c1m8t44+ZK+p6DaD7H8RztY8L6BNZVlYE3wR7mRrg6HlVDsDbYHYwDJ4F1wKlgPDgDrAd+DCaDzsgag03AFDAbTAXbgOngrWAm2BdsBk4Cm4NTwSxwBtgK/BhsCwqei9gE7AhmgreAOWAnsA2P494CdgH7gj3AIeCtvE/DCoW/7bm/Wgamwi6FAIbmJjYGh4AjweHgBHAU7/8wGvwrWAgeB+eBX4Dzedx6LJgMjgM3ghPArWAx+CdwIhiL/NwFJoFTwPrg3WBTcCqYAd4DNgOngdngdLA1OBPMBWfzfc4B/wzOBw9orv0wAi2u/MWCi8E4cAnYAPwjmAyuB4eDj4CzwUfBICu+5cEo8CkwGlwOxoFPg4ngCrA+uBJsBP4eTAGfAbPBteBecD24D+/kJjAIH56bwVBwCzgV3Ao+Af4JfAXcDn4Nvgbi26nSuZU0/9I/x/Ka5ljuwzyFs/65Cn7jN37jN37jN37zX2Z+jfH/4QU3bv3/UcP6/zK7ILMLN1GT2c45/r/fLniMDGlfff2/yz/GT3h8bBe5B1iaqXavcf4I3gNgP/npZ8lQVX3sn2SNzPe9ln5y5B7JH5J7tBqn4kw7kmGX3INOmaPSPa7blDv97CJ3Lxlvtojh8ab3yb0VWv99mDXfDVpMnMVG1zA+TPFXFVfb63oHxdFTTRZVDXtbc1r4rxaNC7Mb+3S/5+wRqcMwajND7NPWCNN9rg1x8P7SMo5lotwwXs1nlhnGq7e97fRXU8ossH8lWaQcp86lsjmu7VAmeIytu/fB/pLSSsaJD7vkc2j3Z6esUElAr5X3LObnEMDPxV1uIXLMbASFKZN7ZLekdE9pe5Sqqtke2a0ojCrzYiX3cPTJVU4H/WCS6flIPuB0n6u4h7aMswVdT5dr4dtTPgqxp/ZK3KVNzimYTvG+IPfTLna5lRDI3hJHTPfT/gv8GffTfpjSmy73ADhB5XkApz9Y2I+sY3DDj6zToaZ7a9dGno17ax+mNFvyfBjoUSiNWpbG8LMWcxo2Kxd4X22Zlve+2vxeHqCwK9WJ2JG7FskUWUcs4g3oZ3oqndRnsPv8n4Wv/bEnKCDlx266P3Zniq8t9seeJi7hzRqtHFDc99KWyquV3Bt7LsW1Gs8Bbvkc1ivVIHtH/LnSPbHrX8Oe2O2pPHR3ArlZl37QW5+rHfTW535/wFufe+aAtz731AFvfe7HB7z1uYcOeOtz9x3w1ucuftv7vLP7dJnM82RdJvM8hmXGPbGH6TKZ5766TOb5Fl0m85zztv0/bk/sWcY9sf8=
*/
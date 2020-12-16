// Boost.Geometry

// Copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_PARAMETERS_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_PARAMETERS_HPP

#include <boost/geometry/formulas/andoyer_inverse.hpp>
#include <boost/geometry/formulas/thomas_direct.hpp>
#include <boost/geometry/formulas/thomas_inverse.hpp>
#include <boost/geometry/formulas/vincenty_direct.hpp>
#include <boost/geometry/formulas/vincenty_inverse.hpp>
//#include <boost/geometry/formulas/karney_direct.hpp>
//#include <boost/geometry/formulas/karney_inverse.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/integral_c.hpp>


namespace boost { namespace geometry { namespace strategy
{

struct andoyer
{
    template
    <
        typename CT,
        bool EnableCoordinates = true,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false
    >
    struct direct
            : formula::thomas_direct
              <
                  CT, false,
                  EnableCoordinates, EnableReverseAzimuth,
                  EnableReducedLength, EnableGeodesicScale
              >
    {};

    template
    <
        typename CT,
        bool EnableDistance,
        bool EnableAzimuth,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false
    >
    struct inverse
        : formula::andoyer_inverse
            <
                CT, EnableDistance,
                EnableAzimuth, EnableReverseAzimuth,
                EnableReducedLength, EnableGeodesicScale
            >
    {};
};

struct thomas
{
    template
    <
        typename CT,
        bool EnableCoordinates = true,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false
    >
    struct direct
            : formula::thomas_direct
              <
                  CT, true,
                  EnableCoordinates, EnableReverseAzimuth,
                  EnableReducedLength, EnableGeodesicScale
              >
    {};

    template
    <
        typename CT,
        bool EnableDistance,
        bool EnableAzimuth,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false
    >
    struct inverse
        : formula::thomas_inverse
            <
                CT, EnableDistance,
                EnableAzimuth, EnableReverseAzimuth,
                EnableReducedLength, EnableGeodesicScale
            >
    {};
};

struct vincenty
{
    template
    <
        typename CT,
        bool EnableCoordinates = true,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false
    >
    struct direct
            : formula::vincenty_direct
              <
                  CT, EnableCoordinates, EnableReverseAzimuth,
                  EnableReducedLength, EnableGeodesicScale
              >
    {};

    template
    <
        typename CT,
        bool EnableDistance,
        bool EnableAzimuth,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false
    >
    struct inverse
        : formula::vincenty_inverse
            <
                CT, EnableDistance,
                EnableAzimuth, EnableReverseAzimuth,
                EnableReducedLength, EnableGeodesicScale
            >
    {};
};
/*
struct karney
{
    template
    <
        typename CT,
        bool EnableCoordinates = true,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false,
        size_t SeriesOrder = 8
    >
    struct direct
            : formula::karney_direct
              <
                  CT, EnableCoordinates, EnableReverseAzimuth,
                  EnableReducedLength, EnableGeodesicScale,
                  SeriesOrder
              >
    {};

    template
    <
        typename CT,
        bool EnableDistance,
        bool EnableAzimuth,
        bool EnableReverseAzimuth = false,
        bool EnableReducedLength = false,
        bool EnableGeodesicScale = false,
        size_t SeriesOrder = 8
    >
    struct inverse
        : formula::karney_inverse
            <
                CT, EnableDistance,
                EnableAzimuth, EnableReverseAzimuth,
                EnableReducedLength, EnableGeodesicScale,
                SeriesOrder
            >
    {};
};
*/
template <typename FormulaPolicy>
struct default_order
{
    BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THIS_TYPE
        , (types<FormulaPolicy>)
    );
};

template<>
struct default_order<andoyer>
    : boost::mpl::integral_c<unsigned int, 1>
{};

template<>
struct default_order<thomas>
    : boost::mpl::integral_c<unsigned int, 2>
{};

template<>
struct default_order<vincenty>
    : boost::mpl::integral_c<unsigned int, 4>
{};
/*
template<>
struct default_order<karney>
    : boost::mpl::integral_c<unsigned int, 8>
{};
*/

}}} // namespace boost::geometry::strategy


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_PARAMETERS_HPP

/* parameters.hpp
o54Z6I57sAPuRU/MxM64H73wAA7FLByLB9EXj6LpOozId/2v0bkOi5Lpj5bpj8FWGIvd0Yjq++2YiPG4DOfh45iojcf8/f/UQWc8J2Q8z8t4TuJ4fAGn4mmMx5dwC76CGXgGM/F1lPtdbBCm8TDfytzvGiHXZSPRFX2wLY7GrjgGB+BY9MFxaMTxOBsnyXKcjOnohztxKh5HfzyBAZiHgfgqBuNZNOB5DMXLOA2vYhhq+wP5jviHSJnnf/T3AH6OdfEymq9HfWS4F3SuR7+S6b6K/fFbDMJCjMNruBi/l+VWhGvxB3wSf8Rn8Sd8DovR9LxYvnce83SeF0fKdj0Lle4x2BTjsC3Oxi4Yj5MwAdXPQseVmIjpOB+V8S/A/+Bj+DlSZ/U5zzLshytwAK7EYHwcV+ETuA5X4XZcjQdxDZ7AtXga16HcN5DvlGcadO4bbJDp2ohtcBN2xc04BrdgAD6F4ab9srac7DvIZxLrLKdMKXcftsT96IlZOAQP4ng8jCGYjbPwCC7Ao/g4HsONmCPjLVAi4/1dltPDyvm3xf63iexvO+AlGc/HOAULMBYvy3i+wH34JR7Br/B9vIqf4jdYiIVYl/FdQ2f8Dr3wexyKP6AvFuMCvI4peAO34c+Yjr/I8rqJL+PvWIxMEJ/LCLI/v1pB+354PgPSNJ2T1Ot2eX+b/lzQHluhA3riQ9gP6+E0dMRZWB+XYwM8gM54FBvjaXTBy9gEv0FX/BmbI8OUa4FNsRW2w9Y4GN3RB9ugEdviPGyPm7EDnsKOmIed8B3sjD9hF/wVu2Mj5Xkj9sUe6I29cTJ64Qzsg/OwL27Dfrgf+2MODsCLOBA/x8Go7HiGYG30VsaDw9EdR6AnjsSeOAoDcAxm4jg8iuPxAk7Aj3EiFuIkvIGTsb4d+1Fsgv7YFwPQGwNxFEbgHozENzAKz2M0foKz8CrG4jWcjZ2U54PYGxMwGOfidFyEc3AxLseluBZTlfHgZjyDW/BzTMMbuBVLcBvWrMzxGWtjOjbDHdgcd2J33IU9MEMZH+7GRNyDC3AvLsZ9uBP3YxYewHzMwg/wENZgfc5GezyC5s+/5Xv1tfaRTrd9/i3Pc7X+oqU/97v0l32P5RXcY3kuvc398XNbfxzbtf4CpD/1c1HKW/fXrbQ/FqjU7y79Zd9jfwVa/e7UH/GSzzO/S38BXqXj9bmtvx8t+ku5Q3/st7T+cu+xvyLpz/Eu/dn3ubfyvKQ/97v0lyT9tbrbdFiUF3Zbf2NK5ws7KamfTn/DLPrzkP4c79Kfzz2Wl9RX6neX/nKlv4537o+drMyXu/Tn1c/2dARarlfSX5O79Jci/bnfpb/8e+zPvr9Mx13685H+OqnnE9b9dbToL136c7xLf7nSX5O79Fck/bnfpT+PATIdNvuTz+mT/nroPDe2U96HxUrYCStjF6xi8T5qrgyfoHPe+Fx103nwCfTEkzgIT+EMPI1R+BIa8WWUcuV7Ozm265Q7vYrpfuwMdMYIbIYzsRNGYg+Mwl4Yjdp+UivX9uenM375DkzWXZ3xG2X8cdgUZ2MrnIN9MB4HYwIOxblofu4TIOU+p/PcZ4e0I9yJTXAXqu81YV/cg6NwLwZhJsbgAVyMWfgkHsQMPIQ5mK21R5Tvt8RHde4jpNeW8WNDZfzYGjOwM+5G8/2YdClnns79mBNy/fMC9sDTOBBfxIn4Ekbhy7gK83AbvooH8TV8F8/gRXwTr+FZrMH43sLmmI8z8F2MwvdwFp7D2XgeZbpZELan+6Q8F81FZ3wRW+HL2BnzUGvvIOU8pnPfvrx8vlxFbIR26IKVUd1u0B+r4kyshnOxOkr58n2Q+u+JZcl7XAc=
*/
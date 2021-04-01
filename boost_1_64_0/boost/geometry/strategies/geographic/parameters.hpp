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
6hE85/OtKBeSk0GS/2a3OA2+0m6mDvxWvyMaZRKculBY91xjGJSzl2+E9+0kNFW/akolWS+emdkH1L4FB0fcfZ302qYGZIgP24V53AF5n4Up37U8mNTKZE6e0ds3VeSJ54kol8Ie5bulZS9VEjowMu4MM2gUQI9JA1nP3uB8/EwYhWNfidXbpyyOT8IkkjVyELmIE+2rUHOiT7cbXCp5LIIzR1GtgUvY2GOXm+Ezt5bUvtrZMnM1/iwVCb6PtmDWQDHop/YOxp6m3aTgRNyiONtZQUJ1IQ02hcHOnxQbeojZIFdjrX0R8+OXenYZ99PCsME5SNthPbQKbMlFV9A07gdqQXD2aSjA8Pidx4ndYmhZsYxg9KFZjVKboIW4PaDOTdlIxN4G1IOXh92O6LE2RZJZD5Fv863EOe4Iwl5MBdz4ENy3GoK2SjOkOxymeW4Wo9zsrcEiWx62EyL02yZ6nv9CC+GRezzOexV/DfO1fIYbGb6Rs1BJlu1QoYhFa9yBa2rFnaeNlUfYECwFA3GCfDBtRuz6Dy81xkkfjB1/OURJMtkluJ9HW49n4Q==
*/
// Boost.Geometry

// Copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_PARAMETERS_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_PARAMETERS_HPP

#include <type_traits>

#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/formulas/andoyer_inverse.hpp>
#include <boost/geometry/formulas/thomas_direct.hpp>
#include <boost/geometry/formulas/thomas_inverse.hpp>
#include <boost/geometry/formulas/vincenty_direct.hpp>
#include <boost/geometry/formulas/vincenty_inverse.hpp>
#include <boost/geometry/formulas/karney_direct.hpp>
#include <boost/geometry/formulas/karney_inverse.hpp>


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

struct karney
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
            : formula::karney_direct
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
        : formula::karney_inverse
            <
                CT, EnableDistance,
                EnableAzimuth, EnableReverseAzimuth,
                EnableReducedLength, EnableGeodesicScale
            >
    {};
};

template <typename FormulaPolicy>
struct default_order
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this type.",
        FormulaPolicy);
};

template<>
struct default_order<andoyer>
    : std::integral_constant<unsigned int, 1>
{};

template<>
struct default_order<thomas>
    : std::integral_constant<unsigned int, 2>
{};

template<>
struct default_order<vincenty>
    : std::integral_constant<unsigned int, 4>
{};

template<>
struct default_order<karney>
    : std::integral_constant<unsigned int, 8>
{};


}}} // namespace boost::geometry::strategy


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_PARAMETERS_HPP

/* parameters.hpp
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
*/
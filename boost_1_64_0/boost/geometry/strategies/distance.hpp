// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DISTANCE_HPP
#define BOOST_GEOMETRY_STRATEGIES_DISTANCE_HPP


#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace distance { namespace services
{


template <typename Strategy> struct tag {};

template <typename Strategy, typename P1, typename P2>
struct return_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_STRATEGY, (types<Strategy, P1, P2>)
        );
};


template <typename Strategy> struct comparable_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_STRATEGY, (types<Strategy>)
        );
};

template <typename Strategy> struct get_comparable
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_STRATEGY, (types<Strategy>)
        );
};

template <typename Strategy, typename P1, typename P2>
struct result_from_distance {};




// Default strategy


/*!
    \brief Traits class binding a default strategy for distance
        to one (or possibly two) coordinate system(s)
    \ingroup distance
    \tparam GeometryTag1 tag (point/segment/box) for which this strategy is the default
    \tparam GeometryTag2 tag (point/segment/box) for which this strategy is the default
    \tparam Point1 first point-type
    \tparam Point2 second point-type
    \tparam CsTag1 tag of coordinate system of first point type
    \tparam CsTag2 tag of coordinate system of second point type
*/
template
<
    typename GeometryTag1,
    typename GeometryTag2,
    typename Point1,
    typename Point2 = Point1,
    typename CsTag1 = typename cs_tag<Point1>::type,
    typename CsTag2 = typename cs_tag<Point2>::type,
    typename UnderlyingStrategy = void
>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_POINT_TYPE_COMBINATION
            , (types<Point1, Point2, CsTag1, CsTag2>)
        );
};


}}} // namespace strategy::distance::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DISTANCE_HPP

/* distance.hpp
Yk0WHNmSBzGCoZuUR0lg82HwM9HcFlwghVLLlFVuYQOqtvo66jniG6mo5dcVQsWoyOPtvpj3TnjbZMPxZu+kfAhk8K4zJPRgp+iIEsKwYhmEk1OStmxraSn24eIbM0f46vR28odet+kTqos6jPoaO9NVX0MovYOUQpya+BgGzScsVCJ0gs6QSnzgy6YSh5pK7D4YjCmrw6R9eP/hT125Pc5qN8WwjMWpCK9PJnxVAuGfRTpaFK6lI/sqP5FJeT5uYjlePdQRicL/7+83FxgWqXV3sfjE4FM7ht/1SHnXLbP5XUf4XQ+z9b8eq0bybZ4T5HKdX+vpiLuuWP6iBuTGCbkFIHeWm9yuQYZcoZBrTE0OdZy6JeB+7jMx4ozi9CZJem0XpUivMjE94QlGjM6dJ9SNTp+z9G3KrZvrzjUja0VybVQkflP6DgtPzbgUUejlHku3Jsqeyh8utOgnJ5OqKPoz0kaWfClHakLrDaErhdAdQqg/E1pMhJI5wUa9dWX0uH12G1siL2nGhaaNDTcvaXNQrdxMG3uZ/IRGdZthYUnrWiaEuqQidHUSoeWW8Er4mhCJf7PEf24WWos7/jgd37TO08kvReWqbykkebwX+gmk8lK/uNTNOBQ9p4zrVzL2TcnYyFQZu29gYsZ+Qj8pXpY7Y5mpM7Y+OWNXJWTsiTPs7+seydidF6TIWGBgQo0rnnvS9/X5iid95sYhv7x9umbI5J4gDBnmXmwowrfAW5+tA7guwQG+SfMoyki6gGrGEWrYYM1EaFqa4BUfYMcK+YyA24pi+7mRo0TXDVESnEYELsi7luSlFfUa7WEYBXgBdTfNyj+9ZKtjFtpylpmAFMl+8oNYqfeSHmTcTCPGIRfUn9DPYxwq2WFEge1QxQ79HQ517JDtcKhnh38caztga/JthwP2Cn/jcMCu43aHwyp2eNw4bCNlF25xklCCPZJgL0+wVybYqxLsdQn2+gR7Y4J9RYJ9ZYJ9VYK9IsG+xmnfVg/WfIaxPgbfw1jdfPYG7YmbUECakE/1wwHXyxB7OMEeSbCXJ9grE+xVCfa6BHt9gr0xwb4iwb4ywb4qwV7htHPtu73XuLzNu2qxjiSLI3Hp6JuGjxasWV61TzML7GnT3WfIUsffPFXi41rrqSZyzWkq8qHSb5jqTv8sQ+LFs1KRSIheKtH5xivkIGKi36qjH6L8CemfaZf/rA6Vv8xR/jPs8oc7Wn5n/DITf3T78U3UcFnq/naM9LfPzrD72yIfc/d72R1fMTs8OcB2CLHDjxwOYXa4y+EQYYdmh0M5O1ytHfRQtMDhUMkO5Q6HKpzx0A7U5vN97v4qL8EeTLAXJtiLE+yhBHs4wR5JsJcn2CsS7JUJ9qoEe1GCvc5ppx7E5+pvl/n+M/tb2T7fdxraEyRxoNqvn0OSZa2W2HQ0t/cyjKCIufIrhI2mxjxfsldYvPJTeEXEK5jCq1y8Ch1e5r27nELJTuFkp0iyU3myU0WyU2WyU1Wyk7SH5FKskVLUJRaQruTmXa9Gbiha1BTDVM0Y19To3n4ODZS2GHMTPmTZrctd9jvLJlIlRFzTqZmKSEgT0WKSmFsq1WbfchCpEyKuKVhPRSTsJBImIlzZmvl0loNIvRBxTdt2HK12a5xEIiwVp4hEiEi2g0ijEHFN9ZoVkXInkXLHvLeciGzz2ERWCBHX9HCKIlLhJFLBEn4+e5vkBk3E3NY/0jWDtI5OlMaVsxno75TC8RJNYCUIXOCak27sKwSMpK+WEqxUBKqUGpjrZUn23jReknFb2zDWLMlqj6K9mm87slqBlOaVtDTIiNAyLWEG/m43t+SvqFekZItUsnWe2iGOtfeVSLY=
*/
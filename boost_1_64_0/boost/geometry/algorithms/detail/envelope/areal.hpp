// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_AREAL_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/algorithms/detail/envelope/range.hpp>
#include <boost/geometry/algorithms/detail/envelope/linear.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

struct envelope_polygon
{
    template <typename Polygon, typename Box, typename Strategy>
    static inline void apply(Polygon const& polygon, Box& mbr, Strategy const& strategy)
    {
        typename ring_return_type<Polygon const>::type ext_ring
            = exterior_ring(polygon);

        if (geometry::is_empty(ext_ring))
        {
            // if the exterior ring is empty, consider the interior rings
            envelope_multi_range
                <
                    envelope_range
                >::apply(interior_rings(polygon), mbr, strategy);
        }
        else
        {
            // otherwise, consider only the exterior ring
            envelope_range::apply(ext_ring, mbr, strategy);
        }
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Ring>
struct envelope<Ring, ring_tag>
    : detail::envelope::envelope_range
{};

template <typename Polygon>
struct envelope<Polygon, polygon_tag>
    : detail::envelope::envelope_polygon
{};

template <typename MultiPolygon>
struct envelope<MultiPolygon, multi_polygon_tag>
    : detail::envelope::envelope_multi_range
        <
            detail::envelope::envelope_polygon
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_AREAL_HPP

/* areal.hpp
g9vx369m8cNpdIXxvz6Y+tNY9vk6zurQq2r8yZ78fzfO5g7FyH3dSsyLXN9ew/jYvSz52Vh0991fU/f7J7DLsO/4tbfH4+uxTT1t+O8/UH9m368ZS+1+c/RvLucQ2JE/7IUdIu4Zie2b8xHnBuzfFcSdy4ir9yLXXEwceuij7EnikK3ewrfix7dDP77Gdw1ZTL6/BH8xgjMQalhlA1lLgjiBNf7xAXLkN8mXL8dev4zPOJk62+nEqaOo4wwmJycnOZ2Y88K/kOviN46eSq58K3agmZwEu13+Bn72cOa7PfVg9s9uF2PLV2Pgz0LHz4dHLdipMLWip4ldzidf/1kRtTZqFA3sefbRdti9DL7r9TOxG18hO+Y/bjl6wBwWECtsczW+7JYB6CF7eBzxGzHlG78lJnyPNTHfY/FfiCM0kd9hw4gdf4A9I87seAX8PtTqJnNmeQo2dDk2sQRffSRxZhu58d3UDF4hhiCOuCBbBD01DPbGInh4WA269Efy2AeF/6VOeyNxy7XwDD+7gHzl/l+RI2+Bzv+dOAMbdD4yfhb5dL5KLLwY+4Lt6Ka/iS9gr/n/Evz0ueyRR37Duc4S5IQOTcXfTbiaeGkKvoWa0c3U3vYMEZPi6+4lZvo3tvsaYoz/QPcxe+BU2t30MLkbvrRtNrbpYuLLm1kj8798I34buxg6ATt2GHWXI4gLJrPPkPHz8H3E7dhm7Hg7/N7jz+T05IMV2KhxbyPfh8mz9sdGEjPstiu2APuWTeKjGeNq7NWjxKevsAe+aSe/PJ561ljO3a8kPsLnDL+cPVRBvPASdgi/UvIwPMUGzSKWPuFabOnB+LD5+L151K3Im9LUWYqJHbLIaN5CalzEtccShw2jvx/dRpxxNPsNe5CkBno6sBuxf0ufpFbP3v9qFDb7eernxLHVhyK/D5FFAzr6SPEAwmsKwix/AXvz80Ghk4o2bhwEaCN8ET+z7pO/qFAoS4w/Cdi2oYGjuvn/9/klfPlwV74ZbRtqufTDT7olsjreG9rw0YcChrigSSe7u1oyAlYS2gwryFcAQssPP8goFI1nRKNIJhua/qPSperPBQtCH33I+92HMi4SFv8uGjqQtlvzF3C8s4Jv5sCHhwZQjcQn8/ekzcl3hoo5D4FW/JBj8regH+LQMydOKwga9J9+zGnLoWrsrbQ5ZZ05TWQem6t5wC9onH9v45vT5qFt+Xsy9IPz0GeNNoNDQ/lbjNftjCfkMhwY7egklPt7oPM3BD78zsiNtnhC9G5zvV/OQR3+jFFrgg7OBejGOXTjHbqb0QNX5sy4M5KJxzQ9YErAOhNdOmyIgLUnu9MhBds6R9cS7dVgQ3OwpK/tSAHrjUe1ttRqga31t52Qo/PB0GNgiUwL0v1wMvLfAp2coOnkFPA5uWc7PXmnNF2bKNY8CN7w7+85698WPhWJvofy68iKsfjB3zq8muzxlD4C/J3itEEe/JCzOG2mam0208bdOTDuLkP5DYy7q9PHbg6tu1dHSBn16DIanpMHsC6ArHO6s1enaXxBDonOeCYFgeCO+wc8gt66jzLZaGy1u4vkH2oPsW5tfzrrnuHMudi/Puj4DaxvpkM7y6GttM4hEomls5GOZCzaEY+kkomubDydyU3IimF2os85Tp/jHZ4xP34i9R3RWLw92dEST2P7GG8AE5mreAQPI4lkc3drbgD5T3rE9ln5GXF5OGeWbKD+ptX8Ta+nJZqNmmsRUGcde/eDN53dHdlEc2/W152JkHKjz30C+jQvtybGTnRxVCD1af5QwYvOZhdW6az/R/r6v4VsgvZ964B9L3V0Yrhmk9doe7ci4CfCQ+UvdtTXT6XTz0Jt/20=
*/
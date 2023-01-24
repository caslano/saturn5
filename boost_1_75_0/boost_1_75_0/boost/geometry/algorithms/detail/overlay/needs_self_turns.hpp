// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2017 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_NEEDS_SELF_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_NEEDS_SELF_TURNS_HPP

#include <boost/range.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/algorithms/num_interior_rings.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct needs_self_turns
{
};

template <typename Geometry>
struct needs_self_turns<Geometry, box_tag>
{
    static inline bool apply(Geometry const&)
    {
        return false;
    }
};

template <typename Geometry>
struct needs_self_turns<Geometry, ring_tag>
{
    static inline bool apply(Geometry const&)
    {
        return false;
    }
};

template <typename Geometry>
struct needs_self_turns<Geometry, polygon_tag>
{
    static inline bool apply(Geometry const& polygon)
    {
        return geometry::num_interior_rings(polygon) > 0;
    }
};

template <typename Geometry>
struct needs_self_turns<Geometry, multi_polygon_tag>
{
    static inline bool apply(Geometry const& multi)
    {
        typedef typename boost::range_value<Geometry>::type polygon_type;
        std::size_t const n = boost::size(multi);
        return n > 1 || (n == 1
             && needs_self_turns<polygon_type>
                         ::apply(*boost::begin(multi)));
    }
};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_NEEDS_SELF_TURNS_HPP

/* needs_self_turns.hpp
oQ06Z7wvTDLGct+VRGhGdndAE5bP0Qh7t+QQEMeTkOefuyStRo5FNjOt7LAtC7HlsoaT6TEBRbHDRq4ILLvAK4WZuFvYmsLEcLZTyyzB4set6BTTjNsx2Jr2S1YjheIqGmo37Y42aPAR9t8cgbpSzhNq1nbK4udVzpfJ8sJknenpwcrQ+EgsX15FaWLKkmnGebjesq6KM9bIQjw0GhtsbaxPNxY/MgYR+LcqzV6Lrr8kewuZZiTlLEXcxwojfLHsxtUoG4EF1yqyOKPNSxEVxSqvIpa8yIrHlcJItgWKWQYDVkDf3wj7uYDNw3PyO7yJUZd5+j1XvFpPjFAkiXvkU7TOF9B4Y6qg+PI1WsX50Q6WPa3IhyorDMXMuTPJ4fklVZFTcSNeEAS34xJGEAwfkJdIFdTRvGUTvNwDl4CDIvfO0wvSdkE+hklbj3cTE2BZ4Up9zZFyzmJTqWGPhlh9pGv2zpB2/bHRPFUoB4PByHfMRvjT67olJh3fbtrFsl4QaOdA6GP8FBcIMXz3EnaTRcHvwbM8/YGpgm0k+3ccRujT7BkhbC7uoA9u+0jf/d2GmRtoYETNrNbnPqxVMnXLuCQ0eG5QN0HHcfcm9nzeOY+fzpvf5J4/1lchk8ebh1g8opl3SrPwjNYB6LHZt+QM9mYN8X/+Y8inrpsPsDXmOCH/eD1n7FWLj9KfI+QHtlxu2fQGMcwGjGzUew52
*/
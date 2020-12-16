// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_REVERSE_DISPATCH_HPP
#define BOOST_GEOMETRY_CORE_REVERSE_DISPATCH_HPP


#include <cstddef>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/integral_constant.hpp>

#include <boost/geometry/core/geometry_id.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Different geometries: reverse_dispatch if second ID < first ID
template <std::size_t GeometryId1, std::size_t GeometryId2>
struct reverse_dispatch : boost::mpl::if_c
    <
        (GeometryId1 > GeometryId2),
        boost::true_type,
        boost::false_type
    >
{};


// Same geometry: never reverse_dispatch
template <std::size_t GeometryId>
struct reverse_dispatch<GeometryId, GeometryId> : boost::false_type {};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template <typename Geometry1, typename Geometry2>
struct reverse_dispatch : detail::reverse_dispatch
    <
        geometry_id<Geometry1>::type::value,
        geometry_id<Geometry2>::type::value
    >
{};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_REVERSE_DISPATCH_HPP

/* reverse_dispatch.hpp
ap6ar65XN6hadaO6Sd2sFqhb1EK1iHfpblW3qdvVEnWHulPdxW95d6t71L1qqbpP3a8eUMvUg+oh9bBarlaoleoRfud/VD2mHler1BPqSfWUWq2eVs+oNWqtWqeeVc+pqHpevaBeVOvVS2qDelltVK+oP6o/qU1qs3pVvaZi6s/qdfWGelP9Rb2l3lZb1F/VO+pv6l31nvq7el81qA/Uh+ofaqv6SH2sPlHb1Kfqn+oz9bn6Qv1Lfaka1b/VV+o/arv6Wn2jvlVN6jv1vfpB7VA/qp/Uzxx+i8eZHXhM2NFKs/ay0nlo3NnqYmXw4L6btbfl46FyD6unlWn1snpbfawsq6/Vz9rH6m/ta+1n7W/5rQOsA61fWQOsX1sHWQdbA63fWIdYh1qDrMOsw60jrIA12BpiHWkNtY6yjraOsbKtY63jrGHWcOt46wTrRCvHOsk62RphjbROsU61TrNyrVHW6dYZ1mjrTGuMNdYKWmdZ46zx1gTrbGuidY41yfqtda51nnW+dYF1oZVn5VsF1mSr0Cqyiq0Sa4pVapVZF1lTrXJrmlVhVVoh62KrygpbEavamm7NsGZal1iXWr+zZlmzrcusy60a6wrrSusqa451tXWNda0117rO+r31B2ueNd+63rrBqrWa/+uNReXl6uRRY/NK8tB2VFE8I29ydUlJcZUuyiusrKgoLoyYqvhmretFhy7JCxeHw2WVFXllRc3l4dLqSFHljAo1csLo8eY//zytOFJaWWQXxcfyX2+OL5o+OG+I9Gpd3Fp79vbuW14WjhRXiGpZ18rllHHj8sorC4ryxo8fnReOVJVVTAmrscFTxmhdVlEWsQcmeMqZeVXF0mr8KePHjxo7xi2cXFaZUDGjqixS7F2a0H78uGDeiILywryT8kIFVQXTlK4cMSqYe8q4vKLicGFVWSjCqMcX89+/LorXU4ojeQXVkdK8irLW5WwuEm5dVlgWKi2u8mpdVDalOBzxqkksmTrTq11FwbTi1mWMeLjVLpSF8wqKC6T32DODeQVFRcyyaaEqmWT2EYqrxycg5nFFHl3CLRuUtfRoZRHGtQ2PMafmjZgwiVlWXFCVV1JeMKVlhfyHyFuVVRUXtyzhpGpZwFYH57HJkrKZCRUem6HYnoiehXmFkTiTwmlFLUReQdWU6S1LpheUVxfnRS4JSZZY2VNQUm9daJ8GptA+SnLOjTjJq7SwOhypnJZXPLNFHzntdl5rD35zWWFBefnkgsKp7FtVuVtaWkxRqKpsegGn0dTiS+wa9/hU2udJ2C2trCgpm+LKiJ50xRUFk8uLi9zS+C0UFVQUJx5sqZCuLcum6XHUhyK+2C5o6SCd2Zwpob46XCq7LlknHAN70hfq/0p+SVlhQaR1RaS8ckoeI1rVqkLWkfgiGTZGrUU52y+sZlm6hGNC6pGC+Fp7y4n+snyE48vcSWGvvolVYlY4uUVVUXFJQXV5hITD4RlFu6zNq2Yetc7SK3MmbUll8zSKr3FnSVzZxdVl/L+5lsVXuePjmnnVlhdPLy53q+TUlDUsvjhSNq24stodIFkey0q8tyB1DEUoUupVMa2yyD04pQXhnZ+H9oVOuhEXFsSPgyxSElcVT6ucXtz6tLS1vW3A0Ugsx8OrXPwSqsI7sQrvxCrsZZV4BoV3dm6E25rwsijHnzn2BgvKQxWcPZWRynBCOUF5cWGrHUic6WHvU0mKd378w83nWsuTKrzz8y3sdb55VxVXTCmraJVNZeXUsmKOSUVxFYsFvT2qJd2Eyoi+spQV2dPKe1/sY2Lny4WzvMWm5Vz/ZW0SV4vwL1st4pvZ925yR1xeXOHRxj35yqraqLbzbKOehCI=
*/
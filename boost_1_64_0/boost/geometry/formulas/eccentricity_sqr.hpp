// Boost.Geometry

// Copyright (c) 2016, 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_ECCENCRICITY_SQR_HPP
#define BOOST_GEOMETRY_FORMULAS_ECCENCRICITY_SQR_HPP

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct eccentricity_sqr
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct eccentricity_sqr<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& /*geometry*/)
    {
        return ResultType(0);
    }
};

template <typename ResultType, typename Geometry>
struct eccentricity_sqr<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        // 1 - (b / a)^2
        return ResultType(1) - math::sqr(ResultType(get_radius<2>(geometry))
                                       / ResultType(get_radius<0>(geometry)));
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
ResultType eccentricity_sqr(Geometry const& geometry)
{
    return formula_dispatch::eccentricity_sqr<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_ECCENCRICITY_SQR_HPP

/* eccentricity_sqr.hpp
yyR8O8qXWu36I7mCzKnPPgsRtLvop2z71+/DA4JMGKy/6uaPQ1T8bIdN42e1z8kkFRMXuyYjj9MD6r26yx6XtK2X2E2F+jBwuISIkTtNTWHDEENlrEv8/lSCkMTZqjYlYI5IINpTp/uD7sg/kMmFzUMQH9eUCgHpo2oQ6RA6P0RmzhdD7NdQaC6diLu/ac4LtsX3wNITC/KuRUJnwAIrDmvXVEHitVjQFgtu3PfuSf1HOqFbtk13eZLn31wvEpAtSkIZqSNQC4ZJ4DQUkDZAxdMNkDPwnKOpksrNVgh+5GqR3NdRdN8ymjaUXWzIwVqh6+tWohsppRIQzniQgi2E9nMVMUb5QgZmvX+ISQv1iYpNq0vywTJw4RDGgpfO7ZRDE5PcJF9Etcib2hqK9NEEBCBnyaq5E1O/PZp0GogKdUj8mPjyuVtphzl3kaAXYhuptvdjMZnbRwTFp26kGDCwsZSRBsS7lMrdAQo/mGukh+FKlDk/4F9GUDpR3ASHZu3O5uL/ei0X1gqAcjNsvXCek0UbCdzHcRl6G/5BsA+xahhCXS6nqEd0knkUXw==
*/
// Boost.Geometry

// Copyright (c) 2020-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_DETAIL_HPP
#define BOOST_GEOMETRY_STRATEGIES_DETAIL_HPP


#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/spherical/get_radius.hpp>
#include <boost/geometry/srs/sphere.hpp>
#include <boost/geometry/srs/spheroid.hpp>
#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{


namespace strategies
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


struct umbrella_strategy {};


struct not_implemented {};


template <typename Strategy>
struct is_umbrella_strategy
{
    static const bool value = std::is_base_of<umbrella_strategy, Strategy>::value;
};


struct cartesian_base : umbrella_strategy
{
    typedef cartesian_tag cs_tag;
};

template <typename RadiusTypeOrSphere>
class spherical_base : umbrella_strategy
{
protected:
    typedef typename strategy_detail::get_radius
        <
            RadiusTypeOrSphere
        >::type radius_type;

public:
    typedef spherical_tag cs_tag;

    spherical_base()
        : m_radius(1.0)
    {}

    template <typename RadiusOrSphere>
    explicit spherical_base(RadiusOrSphere const& radius_or_sphere)
        : m_radius(strategy_detail::get_radius
            <
                RadiusOrSphere
            >::apply(radius_or_sphere))
    {}

    srs::sphere<radius_type> model() const
    {
        return srs::sphere<radius_type>(m_radius);
    }

protected:
    radius_type const& radius() const
    {
        return m_radius;
    }

    radius_type m_radius;
};

template <>
class spherical_base<void> : umbrella_strategy
{
protected:
    typedef double radius_type;

public:
    typedef spherical_tag cs_tag;

    srs::sphere<radius_type> model() const
    {
        return srs::sphere<radius_type>(1.0);
    }

protected:
    radius_type radius() const
    {
        return 1.0;
    }
};

template <typename Spheroid>
class geographic_base : umbrella_strategy
{
public:
    typedef geographic_tag cs_tag;

    geographic_base()
        : m_spheroid()
    {}

    explicit geographic_base(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    Spheroid model() const
    {
        return m_spheroid;
    }

protected:
    Spheroid m_spheroid;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


} // namespace strategies


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DETAIL_HPP

/* detail.hpp
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
*/
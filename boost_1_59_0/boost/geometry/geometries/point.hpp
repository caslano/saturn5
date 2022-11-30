// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_POINT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_POINT_HPP

#include <cstddef>
#include <type_traits>

#include <boost/static_assert.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/make.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
#include <algorithm>
#include <boost/geometry/core/assert.hpp>
#endif

namespace boost { namespace geometry
{

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif

namespace detail
{

template <typename Dummy, std::size_t N, std::size_t DimensionCount>
struct is_coordinates_number_leq
{
    static const bool value = (N <= DimensionCount);
};

template <typename Dummy, std::size_t N, std::size_t DimensionCount>
struct is_coordinates_number_eq
{
    static const bool value = (N == DimensionCount);
};

} // namespace detail


namespace model
{

/*!
\brief Basic point class, having coordinates defined in a neutral way
\details Defines a neutral point class, fulfilling the Point Concept.
    Library users can use this point class, or use their own point classes.
    This point class is used in most of the samples and tests of Boost.Geometry
    This point class is used occasionally within the library, where a temporary
    point class is necessary.
\ingroup geometries
\tparam CoordinateType \tparam_numeric
\tparam DimensionCount number of coordinates, usually 2 or 3
\tparam CoordinateSystem coordinate system, for example cs::cartesian

\qbk{[include reference/geometries/point.qbk]}
\qbk{before.synopsis, [heading Model of]}
\qbk{before.synopsis, [link geometry.reference.concepts.concept_point Point Concept]}


*/
template
<
    typename CoordinateType,
    std::size_t DimensionCount,
    typename CoordinateSystem
>
class point
{
    BOOST_STATIC_ASSERT(DimensionCount > 0);

    // The following enum is used to fully instantiate the
    // CoordinateSystem class and check the correctness of the units
    // passed for non-Cartesian coordinate systems.
    enum { cs_check = sizeof(CoordinateSystem) };

public:

    // TODO: constexpr requires LiteralType and until C++20
    // it has to have trivial destructor which makes access
    // debugging impossible with constexpr.

#if !defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    /// \constructor_default_no_init
    constexpr point()
// Workaround for VS2015
#if defined(_MSC_VER) && (_MSC_VER < 1910)
        : m_values{} {}
#else
        = default;
#endif
#else // defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    point()
    {
        m_created = 1;
        std::fill_n(m_values_initialized, DimensionCount, 0);
    }
    ~point()
    {
        m_created = 0;
        std::fill_n(m_values_initialized, DimensionCount, 0);
    }
#endif

    /// @brief Constructor to set one value
    template
    <
        typename C = CoordinateType,
        std::enable_if_t<geometry::detail::is_coordinates_number_leq<C, 1, DimensionCount>::value, int> = 0
    >
#if ! defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    constexpr
#endif
    explicit point(CoordinateType const& v0)
        : m_values{v0}
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        m_created = 1;
        std::fill_n(m_values_initialized, DimensionCount, 1);
#endif
    }

    /// @brief Constructor to set two values
    template
    <
        typename C = CoordinateType,
        std::enable_if_t<geometry::detail::is_coordinates_number_leq<C, 2, DimensionCount>::value, int> = 0
    >
#if ! defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    constexpr
#endif
    point(CoordinateType const& v0, CoordinateType const& v1)
        : m_values{ v0, v1 }
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        m_created = 1;
        std::fill_n(m_values_initialized, DimensionCount, 1);
#endif
    }

    /// @brief Constructor to set three values
    template
    <
        typename C = CoordinateType,
        std::enable_if_t<geometry::detail::is_coordinates_number_leq<C, 3, DimensionCount>::value, int> = 0
    >
#if ! defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    constexpr
#endif
    point(CoordinateType const& v0, CoordinateType const& v1, CoordinateType const& v2)
        : m_values{ v0, v1, v2 }
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        m_created = 1;
        std::fill_n(m_values_initialized, DimensionCount, 1);
#endif
    }

    /// @brief Get a coordinate
    /// @tparam K coordinate to get
    /// @return the coordinate
    template <std::size_t K>
#if ! defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    constexpr
#endif
    CoordinateType const& get() const
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        BOOST_GEOMETRY_ASSERT(m_created == 1);
        BOOST_GEOMETRY_ASSERT(m_values_initialized[K] == 1);
#endif
        BOOST_STATIC_ASSERT(K < DimensionCount);
        return m_values[K];
    }

    /// @brief Set a coordinate
    /// @tparam K coordinate to set
    /// @param value value to set
    template <std::size_t K>
    void set(CoordinateType const& value)
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        BOOST_GEOMETRY_ASSERT(m_created == 1);
        m_values_initialized[K] = 1;
#endif
        BOOST_STATIC_ASSERT(K < DimensionCount);
        m_values[K] = value;
    }

private:

    CoordinateType m_values[DimensionCount];

#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    int m_created;
    int m_values_initialized[DimensionCount];
#endif
};


} // namespace model

// Adapt the point to the concept
#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{
template
<
    typename CoordinateType,
    std::size_t DimensionCount,
    typename CoordinateSystem
>
struct tag<model::point<CoordinateType, DimensionCount, CoordinateSystem> >
{
    typedef point_tag type;
};

template
<
    typename CoordinateType,
    std::size_t DimensionCount,
    typename CoordinateSystem
>
struct coordinate_type<model::point<CoordinateType, DimensionCount, CoordinateSystem> >
{
    typedef CoordinateType type;
};

template
<
    typename CoordinateType,
    std::size_t DimensionCount,
    typename CoordinateSystem
>
struct coordinate_system<model::point<CoordinateType, DimensionCount, CoordinateSystem> >
{
    typedef CoordinateSystem type;
};

template
<
    typename CoordinateType,
    std::size_t DimensionCount,
    typename CoordinateSystem
>
struct dimension<model::point<CoordinateType, DimensionCount, CoordinateSystem> >
    : std::integral_constant<std::size_t, DimensionCount>
{};

template
<
    typename CoordinateType,
    std::size_t DimensionCount,
    typename CoordinateSystem,
    std::size_t Dimension
>
struct access<model::point<CoordinateType, DimensionCount, CoordinateSystem>, Dimension>
{
    static constexpr CoordinateType get(
        model::point<CoordinateType, DimensionCount, CoordinateSystem> const& p)
    {
        return p.template get<Dimension>();
    }

    static void set(
        model::point<CoordinateType, DimensionCount, CoordinateSystem>& p,
        CoordinateType const& value)
    {
        p.template set<Dimension>(value);
    }
};

template
<
    typename CoordinateType,
    std::size_t DimensionCount,
    typename CoordinateSystem
>
struct make<model::point<CoordinateType, DimensionCount, CoordinateSystem> >
{
    typedef model::point<CoordinateType, DimensionCount, CoordinateSystem> point_type;

    static const bool is_specialized = true;

    template
    <
        typename C = CoordinateType,
        std::enable_if_t<geometry::detail::is_coordinates_number_eq<C, 1, DimensionCount>::value, int> = 0
    >
    static constexpr point_type apply(CoordinateType const& v0)
    {
        return point_type(v0);
    }

    template
    <
        typename C = CoordinateType,
        std::enable_if_t<geometry::detail::is_coordinates_number_eq<C, 2, DimensionCount>::value, int> = 0
    >
    static constexpr point_type apply(CoordinateType const& v0,
                                      CoordinateType const& v1)
    {
        return point_type(v0, v1);
    }

    template
    <
        typename C = CoordinateType,
        std::enable_if_t<geometry::detail::is_coordinates_number_eq<C, 3, DimensionCount>::value, int> = 0
    >
    static constexpr point_type apply(CoordinateType const& v0,
                                      CoordinateType const& v1,
                                      CoordinateType const& v2)
    {
        return point_type(v0, v1, v2);
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_POINT_HPP

/* point.hpp
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
*/
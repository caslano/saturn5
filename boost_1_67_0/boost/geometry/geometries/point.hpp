// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_POINT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_POINT_HPP

#include <cstddef>

#include <boost/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>

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


namespace model
{

namespace detail
{

template <std::size_t DimensionCount, std::size_t Index>
struct array_assign
{
    template <typename T>
    static inline void apply(T values[], T const& value)
    {
        values[Index] = value;
    }
};

// Specialization avoiding assigning element [2] for only 2 dimensions
template <> struct array_assign<2, 2>
{
    template <typename T> static inline void apply(T [], T const& ) {}
};

// Specialization avoiding assigning elements for (rarely used) points in 1 dim
template <> struct array_assign<1, 1>
{
    template <typename T> static inline void apply(T [], T const& ) {}
};

template <> struct array_assign<1, 2>
{
    template <typename T> static inline void apply(T [], T const& ) {}
};

}
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
    BOOST_MPL_ASSERT_MSG((DimensionCount >= 1),
                         DIMENSION_GREATER_THAN_ZERO_EXPECTED,
                         (boost::mpl::int_<DimensionCount>));

    // The following enum is used to fully instantiate the
    // CoordinateSystem class and check the correctness of the units
    // passed for non-Cartesian coordinate systems.
    enum { cs_check = sizeof(CoordinateSystem) };

public:

#if !defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
    /// \constructor_default_no_init
    point() = default;
#else
    /// \constructor_default_no_init
    inline point()
    {}
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
    explicit inline point(CoordinateType const& v0)
    {
        detail::array_assign<DimensionCount, 0>::apply(m_values, v0);
        detail::array_assign<DimensionCount, 1>::apply(m_values, CoordinateType());
        detail::array_assign<DimensionCount, 2>::apply(m_values, CoordinateType());

#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        m_created = 1;
        std::fill_n(m_values_initialized, (std::min)(std::size_t(3), DimensionCount), 1);
#endif
    }

    /// @brief Constructor to set two values
    inline point(CoordinateType const& v0, CoordinateType const& v1)
    {
        detail::array_assign<DimensionCount, 0>::apply(m_values, v0);
        detail::array_assign<DimensionCount, 1>::apply(m_values, v1);
        detail::array_assign<DimensionCount, 2>::apply(m_values, CoordinateType());

#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        m_created = 1;
        std::fill_n(m_values_initialized, (std::min)(std::size_t(3), DimensionCount), 1);
#endif
    }

    /// @brief Constructor to set three values
    inline point(CoordinateType const& v0, CoordinateType const& v1,
            CoordinateType const& v2)
    {
        detail::array_assign<DimensionCount, 0>::apply(m_values, v0);
        detail::array_assign<DimensionCount, 1>::apply(m_values, v1);
        detail::array_assign<DimensionCount, 2>::apply(m_values, v2);

#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        m_created = 1;
        std::fill_n(m_values_initialized, (std::min)(std::size_t(3), DimensionCount), 1);
#endif
    }

    /// @brief Get a coordinate
    /// @tparam K coordinate to get
    /// @return the coordinate
    template <std::size_t K>
    inline CoordinateType const& get() const
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
    inline void set(CoordinateType const& value)
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
    : boost::mpl::int_<DimensionCount>
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
    static inline CoordinateType get(
        model::point<CoordinateType, DimensionCount, CoordinateSystem> const& p)
    {
        return p.template get<Dimension>();
    }

    static inline void set(
        model::point<CoordinateType, DimensionCount, CoordinateSystem>& p,
        CoordinateType const& value)
    {
        p.template set<Dimension>(value);
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
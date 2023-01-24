//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_POINT_HPP
#define BOOST_GIL_CONCEPTS_POINT_HPP

#include <boost/gil/concepts/basic.hpp>
#include <boost/gil/concepts/concept_check.hpp>

#include <cstddef>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wunused-local-typedefs"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

namespace boost { namespace gil {

// Forward declarations
template <typename T>
class point;

template <std::size_t K, typename T>
T const& axis_value(point<T> const& p);

template <std::size_t K, typename T>
T& axis_value(point<T>& p);

/// \brief N-dimensional point concept
/// \code
/// concept PointNDConcept<typename T> : Regular<T>
/// {
///     // the type of a coordinate along each axis
///     template <size_t K>
///     struct axis; where Metafunction<axis>;
///
///     const size_t num_dimensions;
///
///     // accessor/modifier of the value of each axis.
///
///     template <size_t K>
///     typename axis<K>::type const& T::axis_value() const;
///
///     template <size_t K>
///     typename axis<K>::type& T::axis_value();
/// };
/// \endcode
/// \ingroup PointConcept
///
template <typename P>
struct PointNDConcept
{
    void constraints()
    {
        gil_function_requires<Regular<P>>();

        using value_type = typename P::value_type;
        ignore_unused_variable_warning(value_type{});

        static const std::size_t N = P::num_dimensions;
        ignore_unused_variable_warning(N);
        using FT = typename P::template axis<0>::coord_t;
        using LT = typename P::template axis<N - 1>::coord_t;
        FT ft = gil::axis_value<0>(point);
        axis_value<0>(point) = ft;
        LT lt = axis_value<N - 1>(point);
        axis_value<N - 1>(point) = lt;

        //value_type v=point[0];
        //ignore_unused_variable_warning(v);
    }
    P point;
};

/// \brief 2-dimensional point concept
/// \code
/// concept Point2DConcept<typename T> : PointNDConcept<T>
/// {
///     where num_dimensions == 2;
///     where SameType<axis<0>::type, axis<1>::type>;
///
///     typename value_type = axis<0>::type;
///
///     value_type const& operator[](T const&, size_t i);
///     value_type& operator[](T&, size_t i);
///
///     value_type x,y;
/// };
/// \endcode
/// \ingroup PointConcept
///
template <typename P>
struct Point2DConcept
{
    void constraints()
    {
        gil_function_requires<PointNDConcept<P>>();
        static_assert(P::num_dimensions == 2, "");
        point.x = point.y;
        point[0] = point[1];
    }
    P point;
};

}} // namespace boost::gil

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

#endif

/* point.hpp
fRp5fDBahipMtWyKcOv39upeWW8pz4UjyL4VTB8h+KZjiXts/o0lS//g7K7emnD0MIDrQeRIyk9KUgHpRjomOQEBkZYGCUnJ0SBIC0h3Svfo3Gikm9EjpRkxBoxtnD7n6lyc8xd8L75X7/u8z/OZ39jC+01NnBt+nDFg4s6BpLfgjJYWniiTDhqrKw8wGtWfjMm7zC+bPDhqmIUd+CFMAlzLYRVyvpVBuevbb82kJkJDHkJvipsEr7ug2Xm+lgHI3+vUqCeGxaMxuUy60mSj5Q2B5B27ym9xhNaB5ktbH6OiJjPOOGtdzLaf54xymlHATyHTcR9jvkqVeDl6g1YqS8vdP6QOhcgd0v22yNq+M/a+YLWfiYwJhZEwOgWBZ5dd/O6F+KyL1hok4YwgtuZrw114wP1vDSbsRJWtp3GH89XOD4vSPT1v6LuJzJ0/9iFiOhkA6YBR+qSU6lVlxgBwmEg7Wvd0NumzFDRH0maFj7rar6Z6qMTKSUZ+1Tbci0RS8NPJji6p85UaEWNMzt0aMjIvSwqV6ocQ5nuSM4NyGjtdzbxCzuWbQvZWndOQogdUUl+wDh7uK4T1XNcXfJVXKyeTNmyrZNXCPn9tvcdREfsvBUFeCF2yv3Z0cDR6YtHwjg4l/smMUQsrzplbYSa7id42vdSHQttLNhZOn6eE5mUHJX4BQEy6woa20AVhlNeQYe5Rkz2pi71jCQkp
*/
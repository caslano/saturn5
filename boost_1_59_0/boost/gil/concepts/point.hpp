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
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
*/
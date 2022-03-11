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
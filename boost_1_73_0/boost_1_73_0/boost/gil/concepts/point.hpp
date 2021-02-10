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
H+gJVSsW/BF6ammlAT4Db2dOpoqig7VvohEgsPh4fPJij/nEQncSMoCmq+Mp4vgGdNVopBkDwz4CIuUB0ecBLa+jmwOQ0JGhN5xfzko0PtME3si1P4ncLfQUlOyu9pQ49AO1YQgrBuEL9KS1ImeemvFqbAPEOH/zWrz46cfvxYt2F52lcRAluaYJtUP081L03p+964mthvrQEUfHb48v4W9tu4a/d+h3uyZ4Jgo5EZ9xhscXvfcnVx8aeZP9ObSM7br7bcf71oZvK6yRxFfz8vT96cf+eSNvuutzaMlQiCPk1bYZ1H+dJiFQB1FIYPCZ8J7k/C2yDDIygs8o2KLCEIOW3EbqB8mjkvptdnBLNSoQi3agaDsEzWBy7CEdhEEcw7NZEqPbGlEe2ze0FYAF6BEHCkaFlp2qvoXCGB/SYuZoAtfgC3lYpzFtOxR9EoAon2jJUzS/WL6DRsTuHygnd0JMag7WViUcpnENdAyItMXpGGyvAOxN6ged+2k6YZ4RBjPeIbBNbmM5yU30ZQbLle12e024bimYhHS9aNCs0Ca48YqpAs9EMOYBCUyom9zBDIxYK5nwMClU7l4Kho3TG3yj3nwlCPABeWom0oeEAjEaCgp1gKrYw9vCMFGEDR4ZL6faQ4lKwg76DAVG
*/
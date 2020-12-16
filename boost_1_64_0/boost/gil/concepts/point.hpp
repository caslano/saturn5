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
OA9iJ3MwczX7cyb69Q9mNY6PlcNh9TCOyNYy+9eEUisR+25jOfv59xyI48H+MwbHHrMqz6yHo/IN1DWZt3SxZHN47KOr/QvpfjSrB8y2tGwyHHW216zGMCu+ayLO4c6f6BqI2Scb7w5BOrIgZouHdNuB+Mh68jm59cJ9KMs+4xjbMvZ5EcRAxsv5YsBIrN0S9lO/ZufN+a3n+6MdfjGuGaY0C7mF+jxonHedU0+1RHxkXuMjc5h027zuYHrML4eN87V/xVyYz1xk66wwegfBfxTG5gnjOuTOrR7VcTyyXSZ2Lt6/oidiP2Vca5gWDS2DPE+bVWd+fo8ucht9nuwSs0/Pt9Cvuc6YVWN2Xhl6YAvKGZ5oXL/k6PB7P9QnXXbPY3YzKBp9MJGsrkW3E9VWoh3UdbP6kI+H/Bc+RbuT8TYq+KhOZrQt2QFmBTZP1+0G3f80sXNA6SbHMW5vmdX7LN25V4UwF0ST8XM4vdgAiyUL5/1zzRnUZ8BtY99dnaek/k4hGZ97eta/hDxjyPjxwk7taoc2IrvMbPxh/Vo04Y4x3bIF63th/iRrxaxD2R76/Z67xnXk2An5SyI+sp58rfFuoQ5o23tmNYKXZYK+5osn68HseVi3oxhH982qFj9XNc/1JWIn68vLOePdhTjeA+O4vX6hdDjaiIyPlaljpjvRzzws+lkY0jmTjHXWYmq2LqgXD5sR330gjkdWgtmYGu80RhuR1WFzz6F45xTE95vx3LhxfP6raD+ywjCPe6OPzSqGWeXj2x+irsl4OWM3hC9H7GRZeRs96BmLPH83qw+YbavWHuvWcLJBzPZsjoWpJ8ayFKlX4QTKQsavHw5O29gV6f6g+0TMms+ueBrzoIdNu1D3JvogGV9f28Y7puB4ZHxNm1C62ynETsZjn3gmP9ZE6qnxerNP/y/Ho23J+Nhc8VWmnCgLGb8OWFNt1EGUhawv74OtJuN4rj/pvhSfJ45+/grlJJvI7OHLh8/QX56Z1Vg2Z437ZOdolPOFsV5Mzmb3UU4y1IvHb0TxZLy/XBmU+ARlIfMyZ9Fv7Mb6fP/geNxbc3qY/fOhNowjMr6Ware/5GLER8bXpgvblRuMspB5aSP6Hd1M7y2xddbiFwUx/l4bz38VAj4PxzxPOwvVY9a/3ULccwwny8znrKF7B6CcZAfS6Jb/7AOU05Xeop7xa8OrY5KQLoNFleHXxV3roq4TyOwshvtDHuhzayaLasnnnnaTApCnh+V++Dn6vMpsMVwfDb/7QzaUkyyKHW/QLz/i3m+An8XQfquz5a6HdH7GPE9WPbIC/YyMt22tHx43Q3xkvF9Xvjkd90ajs1q8rgcTyPgcee1ai7pov2xUZ2Z23RHa+QDKksOiOrB0Dbr2uIh071gM16L92rfVfw8gu8MsNLYpxrQjl8XQP8dfC8W8FE62nd/PynisH/pnbmNZMjU6+BviI9vG7GrV+eEYm/SBpvR8bTrpk9ZIR8avcw40mfwh2j2v0dKb/myItiXjMYxae/E52oFsKbM/j00ehnbPZzFcG15aVWwbykkWwNcFBWbgHK7yG8tSPOKOvp8AmbdrynDYf14bxpE5+TxfuG0OHK+A8XhLf/7ZH8fzsO5jtun7VpB5iyGWLCezuqE7fkTsZPz8MCzo1ADMWWTXmWVbty8tylnIOFaSipTAeAggc/A+H3rrGMpJNoavC7441BT92mEsZ8PFCYuRJ9l9vi6IPbkaeRa2eL3ejIX9Z70kkvFroMZXg9fgeEW8pwsn43X25/B/Yf0ZQ8br7PstJeei3Yta1J98XXDpyzwYt8UshmvYyx3T3Ue64hb1ilmucqf0+zYlLCoTzPgchPo=
*/
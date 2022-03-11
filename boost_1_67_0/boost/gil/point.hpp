//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_POINT_HPP
#define BOOST_GIL_POINT_HPP

#include <boost/gil/utilities.hpp>
#include <boost/gil/detail/std_common_type.hpp>

#include <boost/config.hpp>

#include <cstddef>
#include <type_traits>

namespace boost { namespace gil {

/// \addtogroup PointModel
///
/// Example:
/// \code
/// point<std::ptrdiff_t> p(3,2);
/// assert((p[0] == p.x) && (p[1] == p.y));
/// assert(axis_value<0>(p) == 3);
/// assert(axis_value<1>(p) == 2);
/// \endcode

/// \brief 2D point both axes of which have the same dimension type
/// \ingroup PointModel
/// Models: Point2DConcept
template <typename T>
class point
{
public:
    using value_type = T;

    template<std::size_t D>
    struct axis
    {
        using coord_t = value_type;
    };

    static constexpr std::size_t num_dimensions = 2;

    point() = default;
    point(T px, T py) : x(px), y(py) {}

    point operator<<(std::ptrdiff_t shift) const
    {
        return point(x << shift, y << shift);
    }

    point operator>>(std::ptrdiff_t shift) const
    {
        return point(x >> shift, y >> shift);
    }

    point& operator+=(point const& p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }

    point& operator-=(point const& p)
    {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    point& operator/=(double d)
    {
        if (d < 0 || 0 < d)
        {
            x = static_cast<T>(x / d);
            y = static_cast<T>(y / d);
        }
        return *this;
    }

    point& operator*=(double d)
    {
        x = static_cast<T>(x * d);
        y = static_cast<T>(y * d);
        return *this;
    }

    T const& operator[](std::size_t i) const
    {
        return this->*mem_array[i];
    }

    T& operator[](std::size_t i)
    {
        return this->*mem_array[i];
    }

    T x{0};
    T y{0};

private:
    // this static array of pointers to member variables makes operator[] safe
    // and doesn't seem to exhibit any performance penalty.
    static T point<T>::* const mem_array[num_dimensions];
};

/// Alias template for backward compatibility with Boost <=1.68.
template <typename T>
using point2 = point<T>;

/// Common type to represent 2D dimensions or in-memory size of image or view.
/// @todo TODO: rename to dims_t or dimensions_t for purpose clarity?
using point_t = point<std::ptrdiff_t>;

template <typename T>
T point<T>::* const point<T>::mem_array[point<T>::num_dimensions] =
{
    &point<T>::x,
    &point<T>::y
};

/// \ingroup PointModel
template <typename T>
BOOST_FORCEINLINE
bool operator==(const point<T>& p1, const point<T>& p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

/// \ingroup PointModel
template <typename T>
BOOST_FORCEINLINE
bool operator!=(const point<T>& p1, const point<T>& p2)
{
    return p1.x != p2.x || p1.y != p2.y;
}

/// \ingroup PointModel
template <typename T>
BOOST_FORCEINLINE
point<T> operator+(const point<T>& p1, const point<T>& p2)
{
    return { p1.x + p2.x, p1.y + p2.y };
}

/// \ingroup PointModel
template <typename T>
BOOST_FORCEINLINE
point<T> operator-(const point<T>& p)
{
    return { -p.x, -p.y };
}

/// \ingroup PointModel
template <typename T>
BOOST_FORCEINLINE
point<T> operator-(const point<T>& p1, const point<T>& p2)
{
    return { p1.x - p2.x, p1.y - p2.y };
}

/// \ingroup PointModel
template <typename T, typename D>
BOOST_FORCEINLINE
auto operator/(point<T> const& p, D d)
    -> typename std::enable_if
    <
        std::is_arithmetic<D>::value,
        point<typename detail::std_common_type<T, D>::type>
    >::type
{
    static_assert(std::is_arithmetic<D>::value, "denominator is not arithmetic type");
    using result_type = typename detail::std_common_type<T, D>::type;
    if (d < 0 || 0 < d)
    {
        double const x = static_cast<double>(p.x) / static_cast<double>(d);
        double const y = static_cast<double>(p.y) / static_cast<double>(d);
        return point<result_type>{
            static_cast<result_type>(iround(x)),
            static_cast<result_type>(iround(y))};
    }
    else
    {
        return point<result_type>{0, 0};
    }
}

/// \ingroup PointModel
template <typename T, typename M>
BOOST_FORCEINLINE
auto operator*(point<T> const& p, M m)
    -> typename std::enable_if
    <
        std::is_arithmetic<M>::value,
        point<typename detail::std_common_type<T, M>::type>
    >::type
{
    static_assert(std::is_arithmetic<M>::value, "multiplier is not arithmetic type");
    using result_type = typename detail::std_common_type<T, M>::type;
    return point<result_type>{p.x * m, p.y * m};
}

/// \ingroup PointModel
template <typename T, typename M>
BOOST_FORCEINLINE
auto operator*(M m, point<T> const& p)
    -> typename std::enable_if
    <
        std::is_arithmetic<M>::value,
        point<typename detail::std_common_type<T, M>::type>
    >::type
{
    static_assert(std::is_arithmetic<M>::value, "multiplier is not arithmetic type");
    using result_type = typename detail::std_common_type<T, M>::type;
    return point<result_type>{p.x * m, p.y * m};
}

/// \ingroup PointModel
template <std::size_t K, typename T>
BOOST_FORCEINLINE
T const& axis_value(point<T> const& p)
{
    static_assert(K < point<T>::num_dimensions, "axis index out of range");
    return p[K];
}

/// \ingroup PointModel
template <std::size_t K, typename T>
BOOST_FORCEINLINE
T& axis_value(point<T>& p)
{
    static_assert(K < point<T>::num_dimensions, "axis index out of range");
    return p[K];
}

/// \addtogroup PointAlgorithm
///
/// Example:
/// \code
/// assert(iround(point<double>(3.1, 3.9)) == point<std::ptrdiff_t>(3,4));
/// \endcode

/// \ingroup PointAlgorithm
template <typename T>
inline point<std::ptrdiff_t> iround(point<T> const& p)
{
    static_assert(std::is_integral<T>::value, "T is not integer");
    return { static_cast<std::ptrdiff_t>(p.x), static_cast<std::ptrdiff_t>(p.y) };
}

/// \ingroup PointAlgorithm
inline point<std::ptrdiff_t> iround(point<float> const& p)
{
    return { iround(p.x), iround(p.y) };
}

/// \ingroup PointAlgorithm
inline point<std::ptrdiff_t> iround(point<double> const& p)
{
    return { iround(p.x), iround(p.y) };
}

/// \ingroup PointAlgorithm
inline point<std::ptrdiff_t> ifloor(point<float> const& p)
{
    return { ifloor(p.x), ifloor(p.y) };
}

/// \ingroup PointAlgorithm
inline point<std::ptrdiff_t> ifloor(point<double> const& p)
{
    return { ifloor(p.x), ifloor(p.y) };
}

/// \ingroup PointAlgorithm
inline point<std::ptrdiff_t> iceil(point<float> const& p)
{
    return { iceil(p.x), iceil(p.y) };
}

/// \ingroup PointAlgorithm
inline point<std::ptrdiff_t> iceil(point<double> const& p)
{
    return { iceil(p.x), iceil(p.y) };
}

}} // namespace boost::gil

#endif

/* point.hpp
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
*/
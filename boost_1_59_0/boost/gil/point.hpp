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
+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
*/
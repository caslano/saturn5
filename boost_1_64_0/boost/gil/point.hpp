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
9iiAQvn6KV5CRAi3lWmXeOndBtcYL4+g9fBR6bMHs4oNkl3mhSrRjYPD3zGv8X5qmJozeLOyKXnNuB7mZBvkOFg70L5beFF1hxr5WuO+GO7rLtTK6bED3eu8jwZuNUVm05B4vKqCvqf/LOi2Vods8eTXTtM92A52+4+p9yqktWqDyt2RJ01n3yRxezwPD39MxZI1BsdYXnn0xDI64LnKLu4lpHs4E+eyETzEeH9pk6jBwE+k9x1iP0iP+5jyfU5wxfp5d08feASwOIHLAj/z2iqDFxzs09OpgCnOgM4DgV/hbQFmFNile/oHOyNq/99ffkzJ0nFRIB4F/ehUw5oZ5tulxrFq4wxD6fe8QAHEffJqirdV7/8fl7gmDeFXl/SH4fS7I+EeFrghfGYjPGPnnbyrl772gzz+ceVLaXKYQoKK6E6/O/rk+/1x5fNQRWVeuek/cPWP+Bc1/bTF21AQT9IfJW2/GO4QgW/w9o1vN3F3FwkxUSeAmZBPfvpx5V8HXhAm08sF02+QzyZZU+DmXlkXBvsoneID9vRtSifD9tK/VB8FIuZbnIET9MepYPLITZ8Q8kjPP/yUpnnYmzIuHiM/nk9o344whR3aTPFC08LG45TCT5D8pC3zifHQLIwx25c+oc52BI0jzJT2xOS7I88d8wn1dplnTQrddokHdz7wXIJ6bfxS9JWirxaG+cbxMv3+mAwyg8BtbJ6grMCDieDDHcwT9k46ow5dXTrrarhHZZKH6fdIshlcVXHsiJ9OEshPUMlffZTualtMbYEhweCSmxP1YTQfVZREeKjgfEwvj7GPueijQCx0aRq8TDo+uPy6selMPdr+e0X04aOPHKm7oNDIlO7LdgaB18KHGQGLmBNFeyJLhPTlvS76ST3I66Ep2u7wo9KOyok9GO4KNQ8hHAZKUwXTPIgB8Mm/75PchzNKY2N8fD0VVdI+AYcdPOk9RZDb+AZFsy/2bNWnPu0VBkD5jfN+4JmX120UQzWfiH6/QHamT0p5pWrLzDetr2hPRiTy++ryJ+W5EiA8L4qCbv0eXR3cC/G2bR9eRt/hdZp7wUfoQWZLojKsNB+QVc/i1umfEl3ZMs7H9U+q95vSpCav2o6Pg2Pwz9D8f1Lp9AbBq22t56KvGLG+LRZAMsz/p5T+aVI/wKHgsTxHlF9ibdl/kHTJT8nzCXkpEJqaho4XrtPIlxnXD+Xq5f0cL6qswNBmPTebFD492pnmii5iv+s2SwpFVydbJbrkD/4p5S9TJbDyGEd4snT5kp/ET1UfiJ1skAlRzQeZV3bBytntXfKrHH1ART+RffcP/TaqOmb6eij7MJhxf9+zFAP6aeUPWcSVX6b6XCI75Jl1mQfhMMc/jhzQcEcP3fibk8lAb5/uAgdPuRdDHECBqTU9mPgsMcQQbi/lTzSij8T6K6Rlnrl9MBmnu03z/2llZ4R5Lkj90tGfSDeGa3rIn+yx2D/BQ463a3jPwQfT8eAegOlIWOi8ej8SfFi/XSTbwaFyIB88js9jb3SinxD+pDbTahvZfoanUIwFlqQ7H1C7EVrt7gVvvJsOfUbJs3GBl5SUeFHGpN3Te+tb5BDCeDn+GclLnSFpnU2kKFP2cOm6D3pnsv2pz6j4hriMwiIc7miQt9vh5h28R1FkK18blwR+6kEXauAWF2ke4BS9cW5T5fwRuDVsnkVdQzUg2tyYQEeb9Bv7peK/hGKahCaYoL95Bhxon74bn1E2xzIqgiTKB9+p3c1OqXTikr2lKaUbrbGBl0Of1XHlMULO6ilebt4dz4bT9C7wWbW2yjBJ7e4mkpS1gGVi7MOleQzOCwUfBjE42PCZX0/wYaXrOTo6f3o=
*/
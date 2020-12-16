// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2017 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_NEEDS_SELF_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_NEEDS_SELF_TURNS_HPP

#include <boost/range.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/algorithms/num_interior_rings.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct needs_self_turns
{
};

template <typename Geometry>
struct needs_self_turns<Geometry, box_tag>
{
    static inline bool apply(Geometry const&)
    {
        return false;
    }
};

template <typename Geometry>
struct needs_self_turns<Geometry, ring_tag>
{
    static inline bool apply(Geometry const&)
    {
        return false;
    }
};

template <typename Geometry>
struct needs_self_turns<Geometry, polygon_tag>
{
    static inline bool apply(Geometry const& polygon)
    {
        return geometry::num_interior_rings(polygon) > 0;
    }
};

template <typename Geometry>
struct needs_self_turns<Geometry, multi_polygon_tag>
{
    static inline bool apply(Geometry const& multi)
    {
        typedef typename boost::range_value<Geometry>::type polygon_type;
        std::size_t const n = boost::size(multi);
        return n > 1 || (n == 1
             && needs_self_turns<polygon_type>
                         ::apply(*boost::begin(multi)));
    }
};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_NEEDS_SELF_TURNS_HPP

/* needs_self_turns.hpp
HA4MTkfOlr/7L5P/enVHl+TiuEGSHwBJHuqcP9cDSrz4FcDvZBfMKMGshC7YcxpmFm27jj6AHP50EkdP5oFsrVMk9I/GUPHmNnAj1xm/WtYDZ3bBR0kqWpGZTyFy7KYsRSufenvPtHLj+5JW/hIyOBMZMF6jyjSTVj4L+TGVjuXaUZfokMxMEs0vwh8zOd0kmo8MylRlFtvyZJWeLUtW6Wlj521HVkml44lUFh6ZDtpHVfEVVvHlLsUcuYuZmzzta5AyA+zNqAsJa+NbR2fTaly6XFLZcvH5haJESrUMKrtcY3ERwNCx+mZGjqxtQJieyndcdPzEDBCMLU0Mfj7VAAdVA6wfTcLTi+hoBmP7rUeULXTQVePXcXYp6m529gmRZQKXXoDv3erbX+TsIwwTXgp4pwmvBNxh61YqZwFTYGEZpI8VbqTCT6RYwFT4jRQLmAq/kWIBUlHwyoykQN9o3dL2RAhRaXdvH+7cj0aZULEihHrwKfpTPmKaotZv/YLdEhJyFtHrS/Kp/hOVDRfhBkERs2/blD1Un3hRtHoXNwT7mDKzXr5EU6Kx3EZu6YeDaw8kuJv5DtCHgQpNexE9clbRKLO+pteX5ctC9EIhiHQt6LNkxtx4fcsmO/bdUoV/Y/K74Z/H2LeURe1pTJTmy5grS4kSV5kose7I4DixOSjObdLaFcgJOU/toX3N1pFghKy0HdlXK3uIVFXdauI9xYVE+kzv2PhPgfl/xn/qh/BXUwHml6rqBjR9hnfIyPA+wu+LHSk/NeSOiu1Nx1YkbXfvT/YnvenB2Gm/PbkEPl+2MQO2el+6MKL1qPI89kGmd08Z/pG9K4GPsrjieybLEXa5o0YIckURpQQ1MSC7sIFd2HCICnhABEQ8qgi7NVZU4iaa7bgtrbZSj2q1ttar9tKAVhMiJIBAwIujFjyqX1y5PJIAwvb/n/n2SLJCUGvP75fNN98c7809b9689+ZHjBF8QYl5nacVC9kJ8KkmIGn7MyMxdf/1jNg896L28Q/aTEBil0KgnQY4SH860y9G+shLHhGH2r0Q/7pwVkxsJlOPE6RgF12OvqP1Ux1IZa51XHn/CcCiQf32pOJ1j6B4ic9GrBFfFnXcxy2iPv9pckskBfxkX6IFRX1SwCUI2AcixDEQdPgAo+GnuHbm53A/i9+KQUbDI/gNwxm4BWJ8k/DuhN9BxDkdq+UM/IL4XQG/Cvwex68Wv/fwsyLOAPyc+F2A32L8OiHuM/jV4vc5cP0YsD/Crx6/nvg2GPuZ+qnH3K99jwU/q5WutPRkf5uk4OnqYu/n6EpHt+79+vXo2a9X78wT9Eik32MJQMe/+v/n/0+qpzI7q8VBIXbFykSwzrc3cz7jSdgKbq9ptdxe5iXd5sHIbcUxH1GRLGUGLz6tOe32RCTacsUX4jKkZVwP4758ZzJrff+pXL46J50HXFGefB6wmeErMtqeB5zWAswTEkyXpPOAPgTDy8cwNyXi3S7jOZI4/Y1lyXDmyPCuSZz+N8sUnJ2YwhPZOldmqxe5xJL3/8Adkqm/7DiE8L7Bp/QA7Xov7kk97s5VsB1uxrK/KQTJpCHV3B+16R8l7AWHP5K9wP5cV1cl01MLqnQdjxVhVZ1yLtmd6kOQe0e1DCm2wtIGahIFK0l532fL+04fUaB96rAydweuUZA3JIr93gT76/QixfAiWfS4lFS4g5/01K2/JV1misY1oDzqrq43tZf+zta4I4ndKVw9RJfSA0a0xpJTHnf4+8yvTe+1p5L9dc14097W8EDeISjQ5XGTvyNiWtNeYG8VAN9YbQzYeDfJGkuesbHaFP8wlZ4noWc0VtvguZ6e+U4JU9RI+Mc=
*/
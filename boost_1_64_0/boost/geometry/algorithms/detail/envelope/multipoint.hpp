// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_MULTIPOINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_MULTIPOINT_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope_multipoint.hpp>
#include <boost/geometry/strategies/spherical/envelope_multipoint.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename MultiPoint>
struct envelope<MultiPoint, multi_point_tag>
{
    template <typename Box, typename Strategy>
    static inline void apply(MultiPoint const& multipoint, Box& mbr, Strategy const& )
    {
        Strategy::apply(multipoint, mbr);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_MULTIPOINT_HPP

/* multipoint.hpp
MFFFk46udcTtybIogGd4312AgQF8ynmf8WTbGvmS9B4OJYLvjh+k9WGT42Y2PM9zxLCWUm9MOQRl7b2nTPaF70+uJrT31rGDhLuvSUMYYrJanRe86M6NFHT57OzgKCqL97tEU4G8hWMotqIzJLGdfh9rpBUfSbKbI/oYuzBGWzQhhifUSab3K8gGiFcpWp91H2mzj3fyCS9yrfSa3czxCq6/z3a2Dm9V72zcQ4O739bj1UtMHF0qecw38XSt5LHAwfPlQI5ItPozOO89iKzLgBfwXZ45/skipcWfzbLyLyznJlu1qjkvdOCZLonReVvl4HoclFf7cOFeI1XPrQXHGWcqrcHqhS42Z0Qxx5NPw3ihY9FUmgdpyHi985km4K2dWZih2i+TMEZSZzYrJAw2a+c4wFLJtZHiGQr2Y2BpwriWHulT9x8v/eclRfTr1lMc2IUarGW89G0dA4AVpNdik9v0OmyVS6vDy2gsFifC8OxGuwMn6HVwuY593x1yoEaDdeBKttLzDg2H/fPllSMUTjRr7g3clz+MmYLHNJJAx1IRNL0jSkzinXWOcPBMiCSHna9wmfEaThgfX+7tw/lqoQdr7eKshFfs6Dksc/Lhu+B1SK8t8Lfs1y0vFHBuoeRWYtlPjSNtsevhPrnJd2sF+MNUkpm4nLCn90c77fATXRyCG/CORCYb71J242QfX6QOnw6MOI7n1qldFqKbreIJ2FbLGn9sXaN6N5toRlFK86GP8Smh/rez6fbjQUUDSu39hzy4/5zqbgVHNTMWev8Z7X0enAwdeks/ovrj7Yk7FTxnct0a2dnw8+fwc4awK4Xxs4P+LPxs8/FzYpCfSLkrrng6VeOpwOTj63iXrwE60N4aH/Lh/HcU7vbjBI/ztPOfB97nxwle5+sTfqu6wZ0ezuT5RfD8Fng+QdjtwnjO3redk2c2ocM0492T+ne+P8angLYGWO3pr8IDVnr3kAeHvVocd7cHF6y10cNWzfbf58EFSy39SHaqGMiDC1b27xlQl2dUwCw8O9Tvkwye0Yx1+/gFpE9+gbfyC7iVX8Ct/AJu5RdwK7+AW/kFvGB+oSgUUSw+/Bjrvn5qnBMXoultHm/6WZuQ4+WpFR4/cpO1QgZ24/+C/B1j8q0DtnNp6xof45OhApJX++xa16+JNDTw7Ng5Q12fl+rN5dXIKZvu9ekNeNfOqWd9xyt4hJW0sMi8+LUugZrTdW68TjhAkZFDEYW7XuLko/4yr/bpH7jgHXDWoeBUN31zvVHFVB6PdH95kwUfiaZ9OfXNisb43oVbFI5gQ6KV7Va44BnCbaqd5LpQGKVLtA3i2UOZJOdH9GGhybR3Z1uSawVe7T+FRwe1nE2O7aZZ3lru8uBZw7fd7eA6RWzaEiEyVf7rHj8Oqal7Xfc5OCwGeuWXPyoHTxgjoDfc6Wj2fJYdJwwH8Rhxl79PYmoVaz/gwrJpMwZycRwhAPfZMgn38+xhh15MSpfBI24cmEe/HnXxfejX4x6NqV9PejilX8G9rZ4ypp0Fh+75+PyUwnkymGy2M/XOoFF6p/f/VwePU3cnZuxhtj4viwUe2MM9gfsBf5N9OZ4CuD+3cNMKn01zXx3sMqxQ+yv02PL931b7u17bx+i42FO+nOPv2t4I1vRe0HF0EDDi3hj/MOiQCdxw8S8aeNEcmeZpj0PEMyV7dZm+FKThN6Ot8+UAXm6QPtozRf1M6JUgXgrU49NrOh5G6vH3P3VcJj+f3vTRmXx628ArPpnt7Xz6l4/G5NN7AbzkU772Jp/+HcRLPtlqhMLOentb5dwmXlYIZY4Kw0NvE9+jxKGfFBLfZzLk1CnL+eV6a3z/ibOO0vI=
*/
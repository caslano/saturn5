// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct calculate_null
{
    template<typename ReturnType, typename Geometry, typename Strategy>
    static inline ReturnType apply(Geometry const& , Strategy const&)
    {
        return ReturnType();
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP

/* calculate_null.hpp
7NEqCNfZpsDP8O8Rc3cQEAlIY/d0kqVwzJPSPc5OeFLSh2HyMZbyyQFUDA0QFXaSneLH3L/H7otE/XjgB+kqC7jO6jPfWZ899vuPQuaVPcL+Z49zrctQ5I8xzuwBH7gQp/62z/fY5nv6XuB/9gr+Z69zDb4Ly5/jifAZusNGLQ63RYbDZcpeytcPcmfz6FA2Q7Vh9DfqFo6PqA47NepL0p1PWtNeG27lVsg8vZfbLT5mqxc1qD6U7n4fN5J6aR6hAc4X4AIGVZnKN/HdvTY/8Y8h84Uok66X7vN4EimRSlggPx+uJMJmJcW6Fttna/9hkBm7j7fZiH3O9n9L3sNsoKKpy6nf18nOcwn8IJ/F9cxiq3sf7T37bD7aRyHzyj4uizmxz9k26ZJxA7tJFvfRzkd+PI0EUvNk6KlOY7DXU2wMMvumW+wXiads42cUZP7tKd4WP3jKuV/0J/JjGB+B/WJpd/tF41Od2vUR+EE+wGzqosm9MLU/cutTnfyRz8AP2nTqefwD7nlcxQxuU9qP2d9L43VmtMC3f8b50RTzL9Zirydk/rVF9H+Ls//vdMEAuI5m0JhRKex86+3l0LhRS1oYD06j5ZU46mrFCNllf+YQZF4S7z7W6d1XsPwmXgcjyXNL3+jPWwSfmb4/hKKQvr+frbXWDsORc82IU5zPbqsbgomiaizilKYP228xjWNgtp/qGb2T+kJHyWlI
*/
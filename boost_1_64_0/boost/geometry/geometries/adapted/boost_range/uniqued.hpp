// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP


#include <boost/range/adaptor/uniqued.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
#if BOOST_VERSION > 104500
struct tag<boost::uniqued_range<Geometry> >
#else
struct tag<boost::range_detail::unique_range<Geometry> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP


/* uniqued.hpp
9ynxXcVQ3N2JQKdtgn/tEM4gPUVnrGQltM67S9UdSwELG/g/jGmxsfWwqur8R0W1neGk76m6OzHiFFi4Clj0yTwo/0vtxNrvBjteV949tOGF3ejo2YxlUS3Fb14GNw0dF2LgYhnaXi6Y1LJobw6Lk7n41qUpqKTV5ybgW+FdFmrqXdgI36DR1i+snNVm5f+A6UeAR1i04uunyt/CXe0e4Qh5WPY3u1ooj4J8XU/TuuFWMQogt75IalDhbPCT9Q+tuaerzsEh6AZVIRJ6RLmddJaK9bli5XtKImWefONiiQ6aGy8Zr0HX+Dt1aYchq9xyupNrwYWY/vwJUa6NEF/CM8plsGEn8oF66e5k5jwbDTCvaKVVnuwu3OLTuWfCsLzlIpcemE1AuXLjRj1kbwOQAN/zg8PrGJjRqgEG9Y4elEd0SgXBy+l0RrCCJvM8kr+oQNfCDj238epyAJNOFHjNdbwFAOVJnBQbZL09CEbNczXr8f/IxRlgl9wY0jeZ3ckM3p3aW96VgRIV0DM5qgOHZXLlRo5z5UggGFU7Q0Q16JkMHHrtMGH6dgWKoQ==
*/
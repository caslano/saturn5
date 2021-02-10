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
wOERDaaVqymkTknBO1WmyeR1WBiAMGy9NWCdwTq7tWMvbrB3neHb3tWQvWv1+63u8D3rvWGt7ntk9nOnewou48FkEeP3s4jHMHnEvOnM97gj5/x+r921tT95wcifO5yto/WsmCfz2c5kHW+4oAWXnVz1z63TzqD1+rxtXfwyHOo0QOLYiY0E6cVXyEj4wuRYG5tEdhC7PDIGr8c8cFzz0iwKx7hy8+r0U5LkSX0INrlrSeSIBRhCmhdgw9gzbl4D8wV+YVLSySzygsQtuTHl0zB6yIk59xPPy42GlTuk1N1N2k++HScsvU37Ve7MW37AwCwaPz51+O18LGwCBvECztAM1sXgzDrpdbvtkyHEsOb9XrP8fuvkZ7q/X3L/8ur1eWfwlu6/KLk/uHo9OOl3Xrfh/k/7pfcFe7j/lxJ68BslYvOeN3MrkNJZ5+0uyzEXjOnOixzReafdHXZO6d7ePgOVkjWae/sv7NuRs476A0XjfnoTRmBXB0LkyLcjGwNajJsIBsQJfB2Rd49CUDS6l+WENXCgOWSwE7Qvt+MHtokO3mC3YejD5zDg9cMqYi8Yr0QPbiVIxzyJw9HHSmJ5fRQGAXg8XmOb+KWxVpXSxGYGnjyxEraJn6rkpi1vIbuq+StnUa8q+WBKaQk0
*/
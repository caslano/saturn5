// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_BOX_HPP


#include <boost/geometry/algorithms/dispatch/expand.hpp>

#include <boost/geometry/core/tags.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/expand_box.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Box + box -> new box containing two input boxes
template
<
    typename BoxOut, typename BoxIn
>
struct expand
    <
        BoxOut, BoxIn,
        box_tag, box_tag
    >
{
    template <typename Strategy>
    static inline void apply(BoxOut& box_out,
                             BoxIn const& box_in,
                             Strategy const& )
    {
        Strategy::apply(box_out, box_in);
    }
};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP

/* box.hpp
2jx6VENUSsTagMWiCL4IJ9HWshEmm/REwQxKUixd6KxWNlDd5XrxhyHlMXjJvFFERHkgI6EpzRF4ulSmMq4if6DY5LRK8NatedQrQCsSA/vdCQwn+zDjVtoIbobJ4PI6gZvueNwdJVO4/Abd0TQ4+z4c9WnrJZEZwFVp0BK5AbkoC4liw/l2LW40pUoLLxD2w+Yxi86XnXy/QQsZ7NW1QxxWVaM/nHS/XpxV1aMFBwdblnvj6VVyybrXyaDVoOJSnyn6ZhSIkHO0dGCQhwRLVXoHpCI4SDWp6AUR1TSrTQ8pmZ4qQ7WA3K6hLbjjUWPHtZxpXUBp9GodzpYivjTnBto1a+vTM1WpQe6kmv8lT3v3or56/j8EwgZD4hSVvWAP7fCyG/Ukrp12dcxeWTmn3dkEb/CnJ7n/gPRGltzlIW9LLUUdabjyjHuXs7RArny5Ox0B3ERFNxwo93vPzlN1nLYdo7ADT9Bb/8mC3S9QSwMECgAAAAgALWdKUrcFJvWlCAAAKhkAACAACQBjdXJsLW1hc3Rlci9saWIvaHR0cF9uZWdvdGlhdGUuY1VUBQABtkgkYK1YbXPiRhL+7l/RJpUNsBj2JbuX2PEmBGu91HqBQrA+V5xSCWkwkxOSTjPyS9b73697ZvQKNs4l
*/
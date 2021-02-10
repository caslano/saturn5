// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_BOX_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_BOX_BOX_HPP


#include <boost/geometry/algorithms/detail/intersection/interface.hpp>
#include <boost/geometry/algorithms/detail/overlay/intersection_box_box.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Box1, typename Box2, bool Reverse
>
struct intersection
    <
        Box1, Box2,
        box_tag, box_tag,
        Reverse
    > : public detail::intersection::intersection_box_box
            <
                0, geometry::dimension<Box1>::value
            >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_BOX_BOX_HPP

/* box_box.hpp
WAkAAIwcAAAbAAkAY3VybC1tYXN0ZXIvbGliL2h0dHBfbnRsbS5jVVQFAAG2SCRg7Vltc9pIEv7Or+iwtT5EMMT21dWt2WSPYJJQccCF8PlclyvVII0srYWk04yMvUn++3XPjISEASep3H06UuFlpqffp/tpudf+ca8GtOHJl6P+O/jCT3XiIkt+567cTu04n0H/w1Mf8fMpIT1YH/nsWPD0kc/QUkccI+VX+u44Twn6SLrRW49OfnToK67gMTo5TNKHLLwJJLSGFhz98stf4RCOXxwfdeCMxSGPwJY8XvDspgO/emrlbwG7v+8K/qoDXAKLuobVPAgFiMSXK5ZxwO9R6PJYcA+YAI8LNwsX+COMQQYc/DDiMJxeXI8nbzuwCkI3ICYPSQ4iSPLIg4Ddcci4y8M7zSNlmYTEx+PI3AuFRIa5DJO4i7I5SJ4tBfEg8SwSCbA7FkZsgYKYhEDKVJz2em6eRah9z0tc0XML87uBXJaWXKMSS/YASSpBJpAL3gGi7MAy8UKfPtEhuJjmiygUQWetDYqKvV6SgeBRRLzwXMiFVpuDbdzTITJIUeNQ0odIYkGiVkGyrBGiH4mLn2cxCkI/IJGXoJs7kMcezxSxsrwQYXyqHLwzNGt9PUhiVAaaAxvGdhMWTISi
*/
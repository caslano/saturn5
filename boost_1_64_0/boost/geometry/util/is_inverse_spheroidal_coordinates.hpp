// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_IS_INVERSE_SPHEROIDAL_COORDINATES_HPP
#define BOOST_GEOMETRY_UTIL_IS_INVERSE_SPHEROIDAL_COORDINATES_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

template<class CT>
struct bounds
{
  static CT lowest  () { return boost::numeric::bounds<CT>::lowest(); }
  static CT highest () { return boost::numeric::bounds<CT>::highest(); }
};

template <typename Box>
bool is_inverse_spheroidal_coordinates(Box const& box)
{
    typedef typename point_type<Box>::type point_type;
    typedef typename coordinate_type<point_type>::type bound_type;

    bound_type high = bounds<bound_type>::highest();
    bound_type low = bounds<bound_type>::lowest();

    return (geometry::get<0, 0>(box) == high) &&
           (geometry::get<0, 1>(box) == high) &&
           (geometry::get<1, 0>(box) == low) &&
           (geometry::get<1, 1>(box) == low);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_IS_INVERSE_SPHEROIDAL_COORDINATES_HPP

/* is_inverse_spheroidal_coordinates.hpp
8vyuAza137z6gW3RB1u+sbfjEMR77JLnFzyR9GWT1aud3b4dv6RyxmmlXp0dPbv0LHUzBerszKSzG0pxKcNAfbq+Wq67ha4bSdeNoutSNHo26JnpSc9ND7ouhnyDYkG7gLYGFc9UG4qHofUp/ONhfLEwC7f71namWJjAOJi0a0QsTN1xMMtwn9A5OmrGwHxeLQamdHtgDMzO7TXXfiz/3aQlHDRpqQdZ78lgMBgMBoNxoiAS+f8ycwx429vrLesLubwwTvFYyN+QDAaDwWAwGAwGg8FgHDci4f9vOG05utWZ52oA//9I2fs7+dn7XVEUs0/9EUv27cJQ9m2jwKVjOzNX2bK71WLLbqVdGjuVbIErOyrb9iCqdzPVG0f1xlC9CwLqzXMGr7nuur129MqoUPbg0HbflFbSzqovuL2T+auzloz+bEPLlzZhgf0SuT9l1L7HXr7A3dx8VrOJW/reD9XMBGmHXvXtK69Pm2pJHf/js4M3ViXtCN9O3CVZ7J99TUK+23zo4Dqz8/aPjxTMCGXvD99OH9yfILQdPbjfQGg7enB7eeT9A4Lb1732b5rLNMcX+2JWatqjY8keTdfRXMQcDXJdAl3XHlTM3dNBq8h+Pf2QqYYNe+JWU5127KW4jmzZPjt2CfbVZsteDupvz068Udm0jSB27VKc62/bNlD24f4HsF/YuWMqTUHt3Fgvo1Zbdwqus1eyjpLBYDAYDAaDcWIjEvK/yLiHMs7qcNbbB0D4qRvgLU35qVtQq81iNQyrLVu3a1rE9AMr44Te4jTZL0Ukpz8k6kO5F2UVrs/YIWUjaqpFJht0eFxWw5Zdp497vBYbK3x+P8J9bohyOJGzwGnT1f40Uafc79atnlynRuebQT+m/R7dPUG3U7wA8fk5iR+9wFQr0PNBVwv5cmd1PmU36h4P9STpEtKCswt+Rbubxhar+3Qdcv2FvX08hWhDehBeW2N/ZyVXYn+m1ZGDerFP6DA+k+fWWItB3itZtE3V4bE4dY+h26Ve5exdSjb9NFH1w/XUD1uaKM5PpxwNbbxNuUzmbcgI3RFn9+mTcSH+y3Q4u/aUfYK6gyDmb/auAzyKIgpvciCoSDdEhHgiYkAIASIiNhTQREKMGhUVvVxyF3JyycW7CwRr7F2jYm+o2Bv2hhgVFRUVFXuLn1gQVOyoWP63++9l53JHglys8/LN9+fezsx782a2zbx5e8JI2qQX6qRNRhnkbdjMGxlvp6IkdipKYqeiBHYqasVORQ47OcfH7A6GSafRn/1EpOeQv2F50vHh8zvGx5hWxsdny2PjAyxL53HOvpNLCi4wUZzhYCfrW6UvSzty1wr7cjODv5P3JZRe977sCv13iPXbDubvwbHfY5S2FCVsS3L7j2ZbchkwZLs02Et+p1nXkXGfO+0fu4a06Zz0rYjZfHRbzslE15XSFueqxZfxFzXIrw3iX85fsj0DOxkm5bNvdqN2xewbtUHOHglG0SVm+wBrPb/Oaz6XtjfIO6iZt11bzq9G4Sdpc1GSNhfFtXkk27yUbS7mvWAS7wVLVih9GPbObH2fU6ruAXIt7LPSuhZe3o/6co45ys1jQ6jv1gbHnJXfM37fEk9BUUFJW+aTaZ+E+o5Jou+4JPessdSv34aGSaOp3wjqV0/9JgSDk2FQqLmfFdXnL9aT8+dJ5o2TzXsnn6/ez23OM79+4Ncvvlq/9W7PL8343Tdgut6f9k/dnybz4FMMPuvxGTCf989Cw6JTMFx7yjHgGODpwALgGcAA8ExgBHgW8BjgucATgA3WPDvk8hmNz25S/xZIHfjcuSXydQUOAPYDbgVEMrYGDgUOAsq4HwwcCxwCnAAcCiw=
*/
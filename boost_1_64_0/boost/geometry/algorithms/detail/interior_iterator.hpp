// Boost.Geometry

// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERIOR_ITERATOR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERIOR_ITERATOR_HPP

#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/interior_type.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/*!
\brief Structure defining the type of interior rings iterator
\note If the Geometry is const, const iterator is defined.
\tparam Geometry \tparam_geometry
 */
template <typename Geometry>
struct interior_iterator
{
    typedef typename boost::range_iterator
        <
            typename geometry::interior_type<Geometry>::type        
        >::type type;
};

template <typename BaseT, typename T>
struct copy_const
{
    typedef T type;
};

template <typename BaseT, typename T>
struct copy_const<BaseT const, T>
{
    typedef T const type;
};

template <typename Geometry>
struct interior_ring_iterator
{
    typedef typename boost::range_iterator
        <
            typename copy_const
                <
                    typename geometry::interior_type<Geometry>::type,
                    typename boost::range_value
                        <
                            typename geometry::interior_type<Geometry>::type
                        >::type
                >::type
        >::type type;
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERIOR_ITERATOR_HPP

/* interior_iterator.hpp
qE+p+JT5Vot8q0W+tSrfOuRbg3yPQ76LgYc0bNvrHZz9jZdUu0+OxY4HjZeqvEwesm89AXhLgAe5cF4NKq+l1fSpvBpBY5nKq0zltRx4K0ReBkf6pE3V8EvVvpFTRP8UQf9Juoe+FPgsw0Lv5fRX+mN6v9ip1WosquavIxReJeevMT/Fb22INsr3n+FOf7yDxGOWZqHXDXl0deUEc409ZERtqiCI9a3FlyX4XmvzpQzM20kYc7QKXmYwL2JThgDl5WuSae39NeCL7+UBX0C1duvQfJyl6PeEbUyMWGvBvWsiniKap0Ou7aIspZIfwu+NyXXM8Dj5Tkmb0tUzKExxhndutxuUrnZQWO7VIPthdXVjtn2AFnQR+ei56y6CnT6hjA+nTLR/GLyafEye+o0Uw+sA9i7Lsd+ZBJfzl5UIG/1GmMtiYIQHm4l1FxUfKVTrLhSfbeuYf1NtPUpw3ves6qUXYYJjjsGFja7Lea0WUW9xZZf6Vf0MCJ4NnZP9PMFzQsWXKfu3048HbQOXMhmmvyvyt21yUmylSgC3n1FhL8eUDu6isNwvOwYdTEJ/R4Uc0sqWZyis7eJuaTdD4vfChtcoPs719cmDHQYf59FfzWut4nW/wKkROFInLqgWadS+uIyqz9cL/RlTfesb/fIhrkbV5ZtFfAZ1ifQ2/iLItcRzct087n7I7P2YM+S7K7B7RUG7h/fh42OjfYNR48nRHGF0OJW9E+/twsZFzAhkbJR6mH3ROBnGoDXQMXnew3gedOybYKodvVO1zXdBNhcLnXu3SnMp0lwLe/IehI0tlWEjFxk2een9lQam96p+kGAyvk215ctVPPSM468gGMbMVP/YLwgfwvAo9x9/pDq7jlDHuBpvmnelalN6zf7jyuYex/iOP41/FcXfCb2zdhn3+vAYw4aNfy/6UobpsUbCIvI4g8JAYpx6q9cx/+wi3pkEzI1HGLfJow1KBJZjlNWAESrn0xai82budRYV8NNC5zuNfy0VlIOYbxb690bVdt+p2vbnWLdgyxAuYb9b4IvwfBVfq+IXqvi5KlwT0v8SzMpLv/d5DfPAYZEm/Cz+N/1yA6dElfvbKl6fN/mOip+v0n9Xxes2c4OKn6vSf1/FX6rib6Rw6FpOvrqHffkR7Iu06SeqNv9j0R/cpGzWTxG+SdcRcK8N2UN7i18e4Fyn93Cr+PKSYPztKl7L806uc5uWz5hJHu5mGopH0Pgl08juc08rGvcSTr+Yt2t/ZQfNjXS1BifS/Hk0FW1myKI97RtaaUJlQyfmgBQO3cDSGm1r7m6jM/BiLu1+zK/w7b2BybSQGMxHmb7lR6JvOaDq/qDxrZVu/bpanqVSOJDDAxSWe3dn4429RzEWbBJvuB+aZ3Qs/OzlQ8q30O3o98inEm2YXFe+L++pYtsvB95ivGGRgcXiqaHRkQFxPv5P1ZNZd1lt83q4Ovu2qj8ufMTq+s6Uycdfi3qUba7BXdvaHaV40+bcT25vxGfuuZA86f5Src58m3V6gpliP27GAZBVBn3rExTW75ZKXP0O6lMEw9qDxseHdIUyLdYedFrghKXXaf9OsJC3YPPkN937p04DHJlOp3mWYPKdZw/zFc9VIzwjq6OZQsG38kX+Q+HFhDeD855MOWd4BTVoR4K+XjecWpOts8dAR9LVdXYU4YNn4Gs8rG/U8Fuc/Ea33OP4zILxe1NMnNybd3SNaOO25sbLK2N+q7yPqZmkvAqD8ipiWeTWCymLYsbPrRMSfx7hh7Qlm0a3pQU16P8QJ32cUoqr4Xn+1o6Wrq2dvs0voPbshxeLdZpja6xViiWSzmK7385GH8u0Wta0MJ3WljWKRrmjYXY=
*/
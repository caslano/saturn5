//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_DETAIL_GET_BASE_ITERATOR_BUFFER_HPP
#define BOOST_COMPUTE_ITERATOR_DETAIL_GET_BASE_ITERATOR_BUFFER_HPP

namespace boost {
namespace compute {
namespace detail {

// returns the buffer for an iterator adaptor's base iterator if
// it exists, otherwise returns a null buffer object.
template<class Iterator>
inline const buffer&
get_base_iterator_buffer(const Iterator &iter,
                         typename boost::enable_if<
                             is_buffer_iterator<
                                 typename Iterator::base_type
                             >
                         >::type* = 0)
{
    return iter.base().get_buffer();
}

template<class Iterator>
inline const buffer&
get_base_iterator_buffer(const Iterator &iter,
                         typename boost::disable_if<
                             is_buffer_iterator<
                                 typename Iterator::base_type
                             >
                         >::type* = 0)
{
    (void) iter;

    static buffer null_buffer;

    return null_buffer;
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_DETAIL_GET_BASE_ITERATOR_BUFFER_HPP

/* get_base_iterator_buffer.hpp
Iip4J2XUFtmb8OjGw/NiGm7cj27LD8XUj9Ein9MoOw8jLxmB1L/ieZO0Tkywj0pwzPuMDhJy3DA1s96TMY9pf16luxjzA1bp9KjPxH1bLZhaiToLZa7wyNPnEakGHxR4xZ2fcNruL/WZwsg41rr5xHvp88iVFLIfTDcN/OSg+HyxqP7D5UStBY649ep5rDAz/vBtI/8XTLxgILnddP4yQyjQdFPyvFrvy4R5JkRFPicwkMy0h72VvC4zESplTsqr5y2Kt2J2Q8zfip6awUbZqMao5zTKE3Za7f15jeKnyWJC97L5B4P0PfHgalFfRTJyimSX0udhWxoLbutJXgb6NDjtZt28XLns0kZp7e5wnplPCsNy7m/UWOBPZ/2uN3JZIClhH8KiwN6d7m+rm9ErSs10utjfwBRRF4xuMc4jlp/axfF53RaLBf/azq9CDn6RTYZ/leh11HlK5wfENOHeghsIvbF3WiyyyeicxertPGOTYP9Mn0eH2GiV7HlMxWFGeSN9Ss6I+Zf4CJX06nLYj6gnFNv52+1RVGoGefJkOiKrAUcKue30eY3B2UQ+jBzTKvtWW/S/FcrXMY23M9Av4EyWw/PI2KFhTsoxRX4t6nmTPEG0UOe7iD0iz7Y/b5BGpQbM3Yr+aXA9Yc8z7RZTRAr/tNmO9VqkKeS7ZrK/4e/mW442l3edKf4dpDmJCIcr+cj+TPJ4VkVt6LjV
*/
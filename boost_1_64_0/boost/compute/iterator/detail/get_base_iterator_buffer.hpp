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
mJ52ENoql9Xb1vRjrFYDFXWxtuq1m27wZYOzEtkdk6kiy6VRFDFZv5walaHyyzpZL4GpbmX1rwfqU69+kKY4p3jo02SYskR6lxLvitFBMdWMyg6qgz9yL+T3XPlo5+hPFaeKx/1vKA6nk0TQmPeOwWvKYFUT3fXsaSmUas7N5MrzzCqxCzzaw5IVfaZXXFZICsRl3oYdot8ZAbHTXpgWFXUm6TmL7ns70ARZSrgWZQ7hM94iNpnUhs8wKnRhM5T9TeTVzJVp2dL8qDiDtdwK8Ro+r2JPRotL0b3Lr9vtk7WHp/aV32+/5xRhhLkNj+Vt+nMmgO3HtfHjQxIa9eroOJT/mU+7AxaTCR1nl79zkan/lQ4qyHcKq365NLZx5mSDama0Ssqq8dbUDFNR0MwOSjwNdn3XNPOURzmBR2mB7OZgu58Y8BzZuCDqoZmqU1vUSCUkY3U5x6YDwocAQwyhC9YXaB0hPfkjzN5fmPVDuHxHXnAAV90cbOY7olnZyXP0VFNqhwiLx7fc2EVJKzB7yhoMIlHgfrGGKkOjOLtEJWCIa1FAJHsjV00Nhw==
*/
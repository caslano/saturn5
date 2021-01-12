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
el/sLiW21qSCP5NGocRKGqelrfYm7RAdb3mFOZOD7UHLsYPcyz+W3G60bE9J/Hu1PLTsRGVF8Fz2p+LnK/Q5RJWqH3KjpFmV60ozzw6dxG4V1z+BU4XRRjfQK0Xtyw6W4WXmjEYFCVNbzWgcEnORHp5ylaVXHDdW52YniCswX3qEfC0jgnZIQMeu/wy+GxZJF+I0z+n7+v1C7LXOpofahZev+YYb+cWN/Bbr30/ogckxzvtr
*/
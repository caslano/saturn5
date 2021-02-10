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
JrVvcBITbc8qjBem+5nFGq1Vz1XC4l0h1H3WAzM6TI3FyumiXtbgGAyjNxPG288KL0DrM1cDVcu7w6A1Thn3+qeXJGT4IM2WN8JdXnjU6oluhlfXUhKgjO93AclLWUwbk+e7u+4X19h5nKSXAST+peH7sdhFKn8eMmeZ1f3JK+tEVpxBKg31jZ7nQ8g8KKJhui9EE0UysevlsnlfQnZ6s2Er6v6rHsBwJLbZ4ZNmOauvRK6/Eg1sUq48nX7CGOmVM++69VSnhHmjJve4QFmYYn/TKsJkmyMa2GhVTlKpwQMvQP9v5fsSyRArzz3nbn0QTSIjp/FajAUvWg9+2oerWD9LbKFh7PaUowl243wM+YnV6bG7GuwB4HxWdV0bvvdGifU/B09PzkRODZxlKsq8bExbTVYIFOmDoWwu6I+CihaGvGjx4f2l7Ygl9JJSP1Aq2qim3gFu6UDRx51RjQnl49LNxIdVmB9k0KuJPktqadQ+kLvcKTxVzjeg0eyE1CzYtN6HRJTskKr+kiYUYbmqsuoArG8ielqt3dK4UDxkTd4RKCI68jbUKELVWamhPO1ZhCaA9VQjcaHPVVOHDiLdi5zuhDscFk/ZXYEcWn+TLUODmD+gqqU1DIBJX+RkGOOy2Aitix2Oinm5vNqw
*/
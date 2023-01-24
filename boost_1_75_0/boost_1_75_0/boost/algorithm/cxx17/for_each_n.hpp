/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  for_each_n.hpp
/// \brief Apply a functor to the elements of a sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_FOR_EACH_N_HPP
#define BOOST_ALGORITHM_FOR_EACH_N_HPP

#include <utility>      // for std::pair

#include <boost/config.hpp>

namespace boost { namespace algorithm {

/// \fn for_each_n(InputIterator first, Size n, Function f);
/// \return first + n
///
/// \param first    The start of the first range.
/// \param n        One past the end of the first range.
/// \param f        A functor to apply to the elements of the sequence
/// \note           If f returns a result, the result is ignored.
template<class InputIterator, class Size, class Function>
InputIterator for_each_n(InputIterator first, Size n, Function f)
{
    for ( ; n > 0; --n, ++first )
        f(*first);

    return first;
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_FOR_EACH_N_HPP

/* for_each_n.hpp
DSaAE2oGFOhojrzdNt2zvxxejwz0/VhhRXZrMpikrNsC8IWAaXbVFUDbjwZHIeeLfZrEiJf0zF78X0u9CCPaMSlHC/2eBHIbrRqhDqg6TVVhS9BPBPoPvr1Jn7OOKXTJua1vCebC21X8C/EuiWeGIrNDwCa1miSpw8k7ORwsXpeuAqKHHZSvpYgPTC1pn8Y++0XRZe5OfqSDuongWu4DxsAmgTm+3tcDUGf9QkG/DXSwyXZfKyAFf1dsbu3SlYVz0yR6CCwGxN/+s9zXqwhJ6Rhw5uW+08bbBgAqb4c+h78QP6ZKl7+/tokIfLT5FNCck+l+1CkGm26SmDA7pnNAWxu6V3J4aw/z1cxRXzIp6MjP6lB+W+WlcBqqqM2DboqqL4P1qVvTK/Ng+l6J6kS59KElOVb3uphI6Y626vKm1X8U5qsHiXR1q6yb1q2A1wZomJBX3X31B77y6Jv4bk8JKEKu3JYMX3FctehWUS4skw52vo8AjgcG+6EFS/vs64lR4IeO0kR7NulbgHeQOL/n73zK+9tjoZ0n85fFF37oBvODG4QLI+J+4+Vmlh9aixwBCLufRvUiFbpbZiNR1nk1uD/C8xMDPQWVTPr2JIZJt5GTaktEg49TV+ammvPOimjBZP13abfFcTBW35EwlrtcH+imyUJmUROGfy9hFy/Wh1tNKsfcfMd9Zc918vSD6QmWiFMGu6cWNtxUWQ8j
*/
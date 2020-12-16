/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  find_if_not.hpp
/// \brief Find the first element in a sequence that does not satisfy a predicate.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_FIND_IF_NOT_HPP
#define BOOST_ALGORITHM_FIND_IF_NOT_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn find_if_not(InputIterator first, InputIterator last, Predicate p)
/// \brief Finds the first element in the sequence that does not satisfy the predicate.
/// \return         The iterator pointing to the desired element.
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param p        A predicate for testing the elements of the range
/// \note           This function is part of the C++2011 standard library.
template<typename InputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR InputIterator find_if_not ( InputIterator first, InputIterator last, Predicate p )
{
    for ( ; first != last; ++first )
        if ( !p(*first))
            break;
    return first;
}

/// \fn find_if_not ( const Range &r, Predicate p )
/// \brief Finds the first element in the sequence that does not satisfy the predicate.
/// \return         The iterator pointing to the desired element.
/// 
/// \param r        The input range
/// \param p        A predicate for testing the elements of the range
///
template<typename Range, typename Predicate>
BOOST_CXX14_CONSTEXPR typename boost::range_iterator<const Range>::type find_if_not ( const Range &r, Predicate p )
{
    return boost::algorithm::find_if_not (boost::begin (r), boost::end(r), p);
}

}}
#endif  // BOOST_ALGORITHM_FIND_IF_NOT_HPP

/* find_if_not.hpp
D9E7HJjN+KnAPwX/fPiHUyPP09SG3dVV/bmdCGghx+7cvdPdz6aPcOCU0jLZbWv/m01Y/mAY3ibEKi/pfiUcMMgMuoUij6hdf6PgI7w7YtqYOxEB0W3F94nZL8TJuDJsBcz006myLwBNHJND6E8UFiQjbcNve8cpxM7T98ud+Jdj7oA7eTYjduarcDpNhiz5IdHHOLbXJOPHTOKDd+SWzmfnruJd/Ngo2slHtAgCJ4sC3VTyADYr4c2baPy8TWgMeFkmHHUBlrX3rmxCimbrxP8rOq20Tq1857SVWvmeqrPg0UybP6p3j4C/t32ZJFCnBX8+4CceS+8VvilubIDSiS188lU6xIvPV5krnkp8lXniqdBX6RRPBb5Kl3jy+Cr7iCeHD+J0sSQWOaTz8M1OrN70Vng0PSwYw/jCpJz96GUvEeN/mktt7/vPy1Ksc2fQX0OhszYkvguGam6bwpColuPjKs09sqHHhG5/HZLjWNrrLm+T/kA7QrGpfVUvJsjnd1W7MuD+w6dsN6TpEzQ+qn4Iv2NtMp+jRdwA3NkdfsutSMvJnInl0UrydV7p4Ih+rWo8YQ9vdkP8XkheuYoTcRGvXpOh+ter/kFDVH9giCN9v8Ot6U1YIF2kxO4zFD9Or3bYwcHU+FsonbCjGc2J9trU8OZOqlVqC1F7mr9O82trHJo/gKoZHBWNAQJqntpWud2VaDcw1CEaH6qa/tmr5chVOTgcW0imUESaj4yXcP0QZgQCgTrpoiH8jrHRA7kn4jlTb0IGPNjxwF+z6MGBh2yqh+twiiwOq4JcPHCWPL1RfHLhgT/1wQN/6itHgN/w+wjr851DYkOlJBkVsIykejJ8x7+FynvcX8WeXeTEqsXOi1e5oNS2gKvjFnYaHkWqWdqXV+iuWhBFLSIHbMCA0LhQjviWC2lsQs71qj5omerfgBE5IeS/+gRHN3/U/L4qDliCCkAXIAYuCmII6G0hZ5NJBSHdvgyUIIhgHYjADr0jTjnZDXw9tUPthZwbqC00coFJAhfwneOPE3Y97NWNTrHaz6NYG7lEIl5j02vZ8ZR/QdarI3KmXkdfZDt+6VMWfsklNdsseEUOjZ2D8zjM4rn4pTx5slnYxQ/Co1UU7xu5xBmIXOH+Vw1uj7BMfMtR0kGQGU5ir9/03l/OJ4XVxRni7y06MKzpmQqEsipOr9Ps0KL24vBmm9uTX6y0JpSu17Bo+rJa1IZ1k9qa0Py13AblUnSc6HAVhzfZlNZ2pQtk0KIW1XKmGiyxv6w4Wzlb9FKquNbtsYu876E1ZIcnjVyoInIUCoX0OyBa36GmoAcqzhWiFm4q5E9QNVRc878Vit7qA/8KRa8rowpw7l7GwL+u6pcUuD3xmxX3vXHS5f37bnZXrXfQe00oOgub/esVPwX8VqOzcBCzU41eMTmEYtE7Jmr+DaHoFVNRm4odR+zK1mp+zAIKFh695E4kf2c2LSdU1Mx1ijb8cS06ez6zT/iAANKnnjLDSKOtHYp/A/G+6HzSbAG1Fn2CTwj4cVLyOfbvR6noU3yEgsCqqFD9+1R/XI0+t95UGSeGMKOis4UaXqEo9PGxhHkPvKL5W0PR+XvxijyNVE10YQu/LdzEb491iqORHsFuPsbV+/+SP9CvcPVPxmpRh1n+DWXzUv4Nii5PInsuxTjRE7RVgl3U2ESbFjvXp5a/4X7w1+wbnoHosXrdnjpbtVus/0DCRvwp2/QunXwnE9ecgCQ68noOKzQO4S4y7GFhyGvCQCAu1INi5/9iLKQe5A/Gck0f5SHx6Lc3C1uyHmh2iBDxfs7OpmfjJJANH19FJUwbeC3DM1EBQfnANTA3Yf/U/cA8/jo=
*/
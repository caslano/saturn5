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
Ak5/QoP5aEp/XD2oaGMbKU8aGfWhodlmUr3aVuMyqe/VYj+s3poZVRaXMZDzZVUEbPygvXhWuKEiYJHtX3//rSL/pXVoVqc3xACc55LboV8TeArv9dFIQx5GW4BGxArVP6xAb8D4qvDD+8h+FPEK8S3YamhXzwEPZi08DDivW+133X5nVDl1rcz/lfHJPVdhzwOBrkO17znujWzyOJQE3JtsRKAjs2hk/xcszI3Di5rIy2MKHk/k/0jwuKYOSCb8+fxkVcV686lMzOI4+WC0HfTPem9wVnT0cXz0cLo92IQ7DW/CaBFmZ4ZTPKeUkOdHko34qWldPnCfTYWhpjsja3n/AlBLAwQKAAAAAAAtZ0pSAAAAAAAAAAAAAAAAEQAJAGN1cmwtbWFzdGVyL2RvY3MvVVQFAAG2SCRgUEsDBAoAAAAAAC1nSlKzXgwMHQAAAB0AAAAbAAkAY3VybC1tYXN0ZXIvZG9jcy8uZ2l0aWdub3JlVVQFAAG2SCRgKi5odG1sCioucGRmCmN1cmwuMQoqLjEuZGlzdApQSwMECgAAAAgALWdKUhRFOyF2AgAAVwQAABoACQBjdXJsLW1hc3Rlci9kb2NzL0FMVFNWQy5tZFVUBQABtkgkYHVUXU/bQBB8v1+xCi9Bahwn
*/
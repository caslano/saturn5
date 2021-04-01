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
FafNky2787wcM0UNBqN+0bcQtalj9r7OzBTCUNiPBo2TgG5q8z5p5DIk4OryiryT5z0j1d1BfpngAsffB1ec3vBovYW2TWeBMmrTYUlC2BJRKpmgyGJEwKXsEDdTmzkKs3FsybqdAkBJ7RX+L8MBP7RaTV/rXLjICtNFKantbGupOPKLQwPEzQakZTj7r/wqnE9zqdbE8Nha9jQChlZcAQMlSzFLvIai38itzkE+HPpeN60hoWdc08Yez3tdSpyUeVlFbMqWbpVGk+whi8oXSwgUBQJkLtG4hAe0r/BYoF0V2To1zYOyIA+3rqmjpITbK+eAal8vcJCJ3zMhbMEUInbCd/DG243KD98QNAEZJjjipZsyU3X5UyDsDY4/hPcJfBmBQcuicHfy0AfLw2eEPJk6snNsB8f9cEwYCZUzkK6mN5bTcTXwaWyDkY+4R0jgz1it6mEvVLMfJu85jol6wx2T+e9T6R+G6NiSsWH06dVOkmYpknUG1rohMYUH4bLVJVUuSCydCwh+4bnb3qvTT2N4jNOn2Wu2ShDUT/w1QQQm3E9BJ3TuRXjolw==
*/
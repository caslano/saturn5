/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  iota.hpp
/// \brief Generate an increasing series
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_IOTA_HPP
#define BOOST_ALGORITHM_IOTA_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn iota ( ForwardIterator first, ForwardIterator last, T value )
/// \brief Generates an increasing sequence of values, and stores them in [first, last)
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param value    The initial value of the sequence to be generated
/// \note           This function is part of the C++2011 standard library.
template <typename ForwardIterator, typename T>
BOOST_CXX14_CONSTEXPR void iota ( ForwardIterator first, ForwardIterator last, T value )
{
    for ( ; first != last; ++first, ++value )
        *first = value;
}

/// \fn iota ( Range &r, T value )
/// \brief Generates an increasing sequence of values, and stores them in the input Range.
/// 
/// \param r        The input range
/// \param value    The initial value of the sequence to be generated
///
template <typename Range, typename T>
BOOST_CXX14_CONSTEXPR void iota ( Range &r, T value )
{
    boost::algorithm::iota (boost::begin(r), boost::end(r), value);
}


/// \fn iota_n ( OutputIterator out, T value, std::size_t n )
/// \brief Generates an increasing sequence of values, and stores them in the input Range.
/// 
/// \param out      An output iterator to write the results into
/// \param value    The initial value of the sequence to be generated
/// \param n        The number of items to write
///
template <typename OutputIterator, typename T>
BOOST_CXX14_CONSTEXPR OutputIterator iota_n ( OutputIterator out, T value, std::size_t n )
{
    for ( ; n > 0; --n, ++value )
        *out++ = value;

    return out;
}

}}

#endif  // BOOST_ALGORITHM_IOTA_HPP

/* iota.hpp
ocT4LSVQkOKCiFsJVVV9sdf2Sc6duY+E9Nd3fSaoFeAHP5znZmd3Z3wCi8aO1rucsdzpBkrk1mk0YFzbKm2hVBpsjUdYDDdpeg818gJ1wNjJCVxJvmleASAkbJxoCsayYJwrWYqKCGE0Qo8bccKZXZ4xNuxPCtgcoMCSu8aCETJHmAfzWRCeevq15bLgmvh+PlxfwjyaRb+GtbWticdjq1RjAoG2DJSuxrXdNmNd5h2ou/0qKuc59VAK0kkNbbllLK2FAQ4Wny1suCEZ/vNe2BqURGgEvVrUgNLqA5AIQGLpz6kvI4w1oEqQdMBMy0m3wZZrbj0XNoV5GdAz37YNMgb01FN4ciIPLBJXdHY2g3o2mr45HEzDyUUYhRGE5/EkimfzAYQQer5rz83YJIC028zq/huI4nVTRjlNWpQWlZBs2oNqZSxIvsUPYLMe5lcu3XZDfb8PPHu/aIHGCsmtUNLXYp8/qvsGef4v8v/Sb7DzHovPrdD9cUHj9suxgorQOmy3135n3S7JjoVynUGfnLJoegJ/q3cCEHzwSE+SLJdwcxMnSbxeD3pOgnreP50jCPg1SQMWBfCFfIdcwnBCc4HwFEQJAzJLZ4oB7DnlB4/ZOcphFwHcSosVNdhqQfO0B9jxxiEMpbJA+dME
*/
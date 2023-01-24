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
9CR+4KlRc3Qd7GjuGb1I+vymEDR33yDUcTcrnfPe3A1xOMhzYrh0bdOJxXBG+x5Ws4YCUck35XlHtkZJTSBzshxCtcghD+IoKcVlZwlL3br9bASZap9ozq1LLgJLhiwJFzWmG00Q3X+5zYapxGvT5BUs13pYr1u6ZP7NpWyWDNmaPg6+R7laMq5bjDo00aEhxm4iM9L1zgpiCRwsEHUhiiwod9gdrsa0tDnzWBdR0E4U9N+VM7t92T3DqzV2aIlRo6/s8RRZdkniEPEx+NeIXkUUJdmyANmDnFseAs/uz9f8ZD815R78yu33c8QuKXLomCWM+tIiXRqgfNgIzcOxhxRVyijVqJpwcsPeGKy4HUujGkQdgdZp7DZ7o88GsnX66+p0P/li+uUFzdaCHDgIcUe7a2WqMxdhj3uYHUuiv46UOu7Vo9SEAqc8zZewvfORvNZXvbQYPC9k2lM4SIf5cX+c9WUUKjnqtD/QituxiYSzBQbatXDjuQPHQQJoAo0BMMr7i3cmmWqXDt4MUeQT3Yuva0MR2GNhK+kGfR+gVY49mYcUj9jqtPc9LvxqpP5hz4WwXbPkxYoPJ96/UOCKOI1PS8pT2h01UlhErOcwvyv1+70LH+hikDrtynnV1/06gon7lhaMZbMihfIDX/wAZtUGZf+lS4rtSoXqFtzFLCrP37kycSaVAxffXbwjYB1jVGA/0qftL9o7zYvC
*/
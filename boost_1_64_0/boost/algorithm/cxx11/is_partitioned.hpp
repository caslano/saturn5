/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  is_partitioned.hpp
/// \brief Tell if a sequence is partitioned
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_IS_PARTITIONED_HPP
#define BOOST_ALGORITHM_IS_PARTITIONED_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn is_partitioned ( InputIterator first, InputIterator last, UnaryPredicate p )
/// \brief Tests to see if a sequence is partitioned according to a predicate. 
///	   In other words, all the items in the sequence that satisfy the predicate are at the beginning of the sequence.
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param p        The predicate to test the values with
/// \note           This function is part of the C++2011 standard library.
template <typename InputIterator, typename UnaryPredicate>
BOOST_CXX14_CONSTEXPR bool is_partitioned ( InputIterator first, InputIterator last, UnaryPredicate p )
{
//  Run through the part that satisfy the predicate
    for ( ; first != last; ++first )
        if ( !p (*first))
            break;
//  Now the part that does not satisfy the predicate
    for ( ; first != last; ++first )
        if ( p (*first))
            return false;
    return true;
}

/// \fn is_partitioned ( const Range &r, UnaryPredicate p )
/// \brief Tests to see if a sequence is partitioned according to a predicate. 
///	   In other words, all the items in the sequence that satisfy the predicate are at the beginning of the sequence.
/// 
/// \param r        The input range
/// \param p        The predicate to test the values with
///
template <typename Range, typename UnaryPredicate>
BOOST_CXX14_CONSTEXPR bool is_partitioned ( const Range &r, UnaryPredicate p )
{
    return boost::algorithm::is_partitioned (boost::begin(r), boost::end(r), p);
}


}}

#endif  // BOOST_ALGORITHM_IS_PARTITIONED_HPP

/* is_partitioned.hpp
qzmFEIqq9E+fU0DbITzOlNwaeflcNnr4WCasNpk75p5PPyZmsl7zWVpxR6zyJnTomHJcbMD7RNMDBXzPhcmihOFRzuslfzgBsbSmITn3oC1y0BRujjpbBFLSc6vVNAULy/J8Wg6l+DycbSsnOgrT3wlHqt8zdi44etnkPnmFMHmICVaY/yOabXj59Sx6Z/czPyQ0inVh248AK+i6J5dAWXw7svswZSq5XrO2eaXqth2mQLYr4shy5IUAuGtz+zsKopFKXQ3zDRYtjhvy46IkJnlLtAgRl0VR74S74LMXbAsz6ab/BfJXhJ9/iU+1In9Mjgu9NJMULw3PxHR7rsGWaHl19yLsdkGNE2Un+9+5v8Gj6Cvp2zhVwFoHhJlCGElF6/eWLpCyrIUUGGEjz9HqvoEGk5GbfnDtU8dO1FSQnkp/GuEAPSQFhnzo8HyT5LnXvgc/dSTHpzKZKILMFuPzzMHMu94vb8Wn7YY4MMYx7V/Mj0LpdXgGE011UC2767xRehNC+aDReeBF8fgz1TrxTQz39v3Zk/RJKwVzmrv05IPVjugsLLpwrrxvCQ==
*/
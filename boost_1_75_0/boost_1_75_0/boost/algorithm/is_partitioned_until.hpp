/*
   Copyright (c) Alexander Zaitsev <zamazan4ik@gmail.by>, 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  is_partitioned_until.hpp
/// \brief Tell if a sequence is partitioned
/// \author Alexander Zaitsev

#ifndef BOOST_ALGORITHM_IS_PARTITIONED_UNTIL_HPP
#define BOOST_ALGORITHM_IS_PARTITIONED_UNTIL_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn is_partitioned_until ( InputIterator first, InputIterator last, UnaryPredicate p )
/// \brief Tests to see if a sequence is partitioned according to a predicate. 
///	   In other words, all the items in the sequence that satisfy the predicate are at the beginning of the sequence.
///
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param p        The predicate to test the values with
///
/// \note Returns the first iterator 'it' in the sequence [first, last) for which is_partitioned(first, it, p) is false.
///     Returns last if the entire sequence is partitioned.
///     Complexity: O(N).
template <typename InputIterator, typename UnaryPredicate>
InputIterator is_partitioned_until ( InputIterator first, InputIterator last, UnaryPredicate p )
{
//  Run through the part that satisfy the predicate
    for ( ; first != last; ++first )
        if ( !p (*first))
            break;
//  Now the part that does not satisfy the predicate
    for ( ; first != last; ++first )
        if ( p (*first))
            return first;
    return last;
}

/// \fn is_partitioned_until ( const Range &r, UnaryPredicate p )
/// \brief Tests to see if a sequence is partitioned according to a predicate. 
///	   In other words, all the items in the sequence that satisfy the predicate are at the beginning of the sequence.
///
/// \param r        The input range
/// \param p        The predicate to test the values with
///
/// \note Returns the first iterator 'it' in the sequence [first, last) for which is_partitioned(first, it, p) is false.
///     Returns last if the entire sequence is partitioned.
///     Complexity: O(N).
template <typename Range, typename UnaryPredicate>
typename boost::range_iterator<const Range>::type is_partitioned_until ( const Range &r, UnaryPredicate p )
{
    return boost::algorithm::is_partitioned_until (boost::begin(r), boost::end(r), p);
}

}}

#endif  // BOOST_ALGORITHM_IS_PARTITIONED_UNTIL_HPP

/* is_partitioned_until.hpp
w8LGMXANR1WlKUAkFrj4iVqbEmCfb468axFRAudpPii+siFV3MB567+WxVEdNynPYiO2UgOWh2S1krWXNgchYZyssBe68x9lPyE6T1BQyh2Svk8sp7I69AWYHs0aoBxZdakvCbJv+aywmlkbId2swAPV1NnvL8lI+Ls/VByRyHueWFkqf123CDx2pdVf5nZOGHrba9OnoJ2LkNrzndT38RN+cIq/ADcxSqnYFytU/g55lRvCjHsiLKwNSXeptUOFe4l9vGFse09Jqvk1tIV0L1/g6+J6K8nkseCZcsMSOAtcT/Whq5sE6rEMUxEif9js/YBR9HtmqtVz7kIaaXPIS1fHExETKOYIIHtGma3rFGFx37dp4rJ+qIho6OVIneVxMQmUUxyefiHhV0Dbu3y5y5r6uLdSwVFmI3RlodlLkk1kAm4xMsorCQy7F3OZTMnm6KFJrfRqNiePxIVvaVV+kUIRw02CK4Bfy5keHGqJaOsgTF/UGa/6765OVNw+8br0ed5uYCJRL/p2sK8rJix0jgz8XcwNEd9kjWlOpfmbkkmdXesDYsiiFj/J1gtddMwvSmsmGoNVmFiLNBFCHdbEXDAIECggqlwhjd/dbIY29ZaETfKDG+cd8ylF3sbxqM4jaAD+zz/to2ZqU6OY2n4WvGr6/X1ZteAia326T4add+gTGOQH+HszS+PgdHUfP73pEb9T0usqxpoUH3yv
*/
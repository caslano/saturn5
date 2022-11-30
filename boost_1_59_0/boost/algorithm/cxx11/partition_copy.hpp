/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  partition_copy.hpp
/// \brief Copy a subset of a sequence to a new sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_PARTITION_COPY_HPP
#define BOOST_ALGORITHM_PARTITION_COPY_HPP

#include <utility>  // for std::pair

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn partition_copy ( InputIterator first, InputIterator last,
///     OutputIterator1 out_true, OutputIterator2 out_false, UnaryPredicate p )
/// \brief Copies the elements that satisfy the predicate p from the range [first, last) 
///     to the range beginning at d_first_true, and
///     copies the elements that do not satisfy p to the range beginning at d_first_false.
///
/// 
/// \param first     The start of the input sequence
/// \param last      One past the end of the input sequence
/// \param out_true  An output iterator to write the elements that satisfy the predicate into
/// \param out_false An output iterator to write the elements that do not satisfy the predicate into
/// \param p         A predicate for dividing the elements of the input sequence.
///
/// \note            This function is part of the C++2011 standard library.
template <typename InputIterator, 
        typename OutputIterator1, typename OutputIterator2, typename UnaryPredicate>
BOOST_CXX14_CONSTEXPR std::pair<OutputIterator1, OutputIterator2>
partition_copy ( InputIterator first, InputIterator last,
        OutputIterator1 out_true, OutputIterator2 out_false, UnaryPredicate p )
{
    for ( ; first != last; ++first )
        if ( p (*first))
            *out_true++ = *first;
        else
            *out_false++ = *first;
    return std::pair<OutputIterator1, OutputIterator2> ( out_true, out_false );
}

/// \fn partition_copy ( const Range &r, 
///     OutputIterator1 out_true, OutputIterator2 out_false, UnaryPredicate p )
/// 
/// \param r         The input range
/// \param out_true  An output iterator to write the elements that satisfy the predicate into
/// \param out_false An output iterator to write the elements that do not satisfy the predicate into
/// \param p         A predicate for dividing the elements of the input sequence.
///
template <typename Range, typename OutputIterator1, typename OutputIterator2, 
            typename UnaryPredicate>
BOOST_CXX14_CONSTEXPR std::pair<OutputIterator1, OutputIterator2>
partition_copy ( const Range &r, OutputIterator1 out_true, OutputIterator2 out_false, 
                                UnaryPredicate p )
{
    return boost::algorithm::partition_copy 
                      (boost::begin(r), boost::end(r), out_true, out_false, p );
}

}} // namespace boost and algorithm

#endif  // BOOST_ALGORITHM_PARTITION_COPY_HPP

/* partition_copy.hpp
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
*/
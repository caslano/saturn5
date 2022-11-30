/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  copy_if.hpp
/// \brief Copy a subset of a sequence to a new sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_COPY_IF_HPP
#define BOOST_ALGORITHM_COPY_IF_HPP

#include <utility>    // for std::pair, std::make_pair

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn copy_if ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
/// \brief Copies all the elements from the input range that satisfy the
/// predicate to the output range.
/// \return The updated output iterator
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
/// \note           This function is part of the C++2011 standard library.
template<typename InputIterator, typename OutputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR OutputIterator copy_if ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
{
    for ( ; first != last; ++first )
        if (p(*first))
            *result++ = *first;
    return result;
}

/// \fn copy_if ( const Range &r, OutputIterator result, Predicate p )
/// \brief Copies all the elements from the input range that satisfy the
/// predicate to the output range.
/// \return The updated output iterator
/// 
/// \param r        The input range
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename Range, typename OutputIterator, typename Predicate>
BOOST_CXX14_CONSTEXPR OutputIterator copy_if ( const Range &r, OutputIterator result, Predicate p )
{
    return boost::algorithm::copy_if (boost::begin (r), boost::end(r), result, p);
}


/// \fn copy_while ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
/// \brief Copies all the elements at the start of the input range that
///     satisfy the predicate to the output range.
/// \return The updated input and output iterators
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename InputIterator, typename OutputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR std::pair<InputIterator, OutputIterator>
copy_while ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
{
    for ( ; first != last && p(*first); ++first )
        *result++ = *first;
    return std::make_pair(first, result);
}

/// \fn copy_while ( const Range &r, OutputIterator result, Predicate p )
/// \brief Copies all the elements at the start of the input range that
///     satisfy the predicate to the output range.
/// \return The updated input and output iterators
/// 
/// \param r        The input range
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename Range, typename OutputIterator, typename Predicate>
BOOST_CXX14_CONSTEXPR std::pair<typename boost::range_iterator<const Range>::type, OutputIterator> 
copy_while ( const Range &r, OutputIterator result, Predicate p )
{
    return boost::algorithm::copy_while (boost::begin (r), boost::end(r), result, p);
}


/// \fn copy_until ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
/// \brief Copies all the elements at the start of the input range that do not
///     satisfy the predicate to the output range.
/// \return The updated output iterator
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename InputIterator, typename OutputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR std::pair<InputIterator, OutputIterator>
copy_until ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
{
    for ( ; first != last && !p(*first); ++first )
        *result++ = *first;
    return std::make_pair(first, result);
}

/// \fn copy_until ( const Range &r, OutputIterator result, Predicate p )
/// \brief Copies all the elements at the start of the input range that do not
///     satisfy the predicate to the output range.
/// \return The updated output iterator
/// 
/// \param r        The input range
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename Range, typename OutputIterator, typename Predicate>
BOOST_CXX14_CONSTEXPR std::pair<typename boost::range_iterator<const Range>::type, OutputIterator> 
copy_until ( const Range &r, OutputIterator result, Predicate p )
{
    return boost::algorithm::copy_until (boost::begin (r), boost::end(r), result, p);
}

}} // namespace boost and algorithm

#endif  // BOOST_ALGORITHM_COPY_IF_HPP

/* copy_if.hpp
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
*/
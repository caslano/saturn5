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
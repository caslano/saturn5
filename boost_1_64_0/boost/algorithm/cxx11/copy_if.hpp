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
GraIWYV7GxBgmVQadxNeySDjU3/AI1GNBfJoZ7hqouN7BEUv2AGLXILte+dtOV+NGo89PVN26jaJglwYref9SXrWSPcc8eaxzeUnPB72u2aQ/P4Qb5YH7FEEdcUDJj+A7FngU+T8Xldq7e7HIlVbkVnpmox2QAXgKyA2rClZ3GWlhGMUQ6CYd1NW09D0BpsfIWulDIk8PCxndVhh+3sgp6oaE1fXmUe1uNjrl8wpOF/deSM1XiOBtEI+Cx0PpiX9CfXZs8s94+VeuCukC2beNlNX3IbGRrIEHpMcngHalGJ8PClUvyVGeAqUIL/71SA7kdtQO3cXhmoS/beRqHEHqDhTN2okm/soDll0xuEMm7DbmCWnT5tVWOAVi7BCwefVGXPOaaxZOnQmmtdhXdrOX+UqE36OkxXgZ6ZD/TTnkOF3HHDAvqLkMWXmDQ0GtYmOpCs9w4x4PhK1lfrG4BXl5bdqAV23KMc5gSu9dY9AWFEx3zx3lCOWbEDcsbUpZpxyW01ecd4DocjzQETHwqWjHv9kegblM5TaRKgSJCG5wQlw8w24KP+4+TLDjA==
*/
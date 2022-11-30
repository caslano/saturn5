/*
   Copyright (c) Marshall Clow 2014.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  is_permutation.hpp
/// \brief Is a sequence a permutation of another sequence (four iterator versions)
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_IS_PERMUTATION14_HPP
#define BOOST_ALGORITHM_IS_PERMUTATION14_HPP

#include <utility>      // for std::pair
#include <functional>   // for std::equal_to
#include <iterator>

#include <boost/config.hpp>
#include <boost/algorithm/cxx11/is_permutation.hpp>
#include <boost/algorithm/cxx14/mismatch.hpp>

namespace boost { namespace algorithm {

/// \fn is_permutation ( ForwardIterator1 first, ForwardIterator1 last, 
///                      ForwardIterator2 first2, ForwardIterator2 last2 )
/// \brief Tests to see if the sequence [first,last) is a permutation of the sequence starting at first2
///
/// \param first1   The start of the input sequence
/// \param last2    One past the end of the input sequence
/// \param first2   The start of the second sequence
/// \param last1    One past the end of the second sequence
/// \note           This function is part of the C++2014 standard library.
template< class ForwardIterator1, class ForwardIterator2 >
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1, 
                      ForwardIterator2 first2, ForwardIterator2 last2 )
{
//  How should I deal with the idea that ForwardIterator1::value_type
//  and ForwardIterator2::value_type could be different? Define my own comparison predicate?
    std::pair<ForwardIterator1, ForwardIterator2> eq = boost::algorithm::mismatch
        ( first1, last1, first2, last2 );
    if ( eq.first == last1 && eq.second == last2)
        return true;
    return boost::algorithm::detail::is_permutation_tag (
        eq.first, last1, eq.second, last2, 
        std::equal_to<typename std::iterator_traits<ForwardIterator1>::value_type> (),
        typename std::iterator_traits<ForwardIterator1>::iterator_category (),
        typename std::iterator_traits<ForwardIterator2>::iterator_category ());
}

/// \fn is_permutation ( ForwardIterator1 first, ForwardIterator1 last, 
///                      ForwardIterator2 first2, ForwardIterator2 last2, 
///                      BinaryPredicate p )
/// \brief Tests to see if the sequence [first,last) is a permutation of the sequence starting at first2
///
/// \param first1   The start of the input sequence
/// \param last1    One past the end of the input sequence
/// \param first2   The start of the second sequence
/// \param last2    One past the end of the second sequence
/// \param pred     The predicate to compare elements with
///
/// \note           This function is part of the C++2014 standard library.
template< class ForwardIterator1, class ForwardIterator2, class BinaryPredicate >
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1,
                      ForwardIterator2 first2, ForwardIterator2 last2, 
                      BinaryPredicate pred )
{
    std::pair<ForwardIterator1, ForwardIterator2> eq = boost::algorithm::mismatch
        ( first1, last1, first2, last2, pred );
    if ( eq.first == last1 && eq.second == last2)
        return true;
    return boost::algorithm::detail::is_permutation_tag (
        first1, last1, first2, last2, pred, 
        typename std::iterator_traits<ForwardIterator1>::iterator_category (),
        typename std::iterator_traits<ForwardIterator2>::iterator_category ());
}

}}

#endif  // BOOST_ALGORITHM_IS_PERMUTATION14_HPP

/* is_permutation.hpp
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
*/
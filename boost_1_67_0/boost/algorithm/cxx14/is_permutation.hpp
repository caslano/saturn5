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
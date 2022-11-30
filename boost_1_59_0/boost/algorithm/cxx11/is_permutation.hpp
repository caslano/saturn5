/*
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  is_permutation.hpp
/// \brief Is a sequence a permutation of another sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_IS_PERMUTATION11_HPP
#define BOOST_ALGORITHM_IS_PERMUTATION11_HPP

#include <algorithm>    // for std::find_if, count_if, mismatch
#include <utility>      // for std::pair
#include <functional>   // for std::equal_to
#include <iterator>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace algorithm {

/// \cond DOXYGEN_HIDE
namespace detail {
    template <typename Predicate, typename Iterator>
    struct value_predicate {
        value_predicate ( Predicate p, Iterator it ) : p_ ( p ), it_ ( it ) {}

        template <typename T1>
        bool operator () ( const T1 &t1 ) const { return p_ ( *it_, t1 ); }
    private:
        Predicate p_;
        Iterator it_;
        };
        
//  Preconditions:
//  1. The sequences are the same length
//  2. Any common elements on the front have been removed (not necessary for correctness, just for performance)
    template< class ForwardIterator1, class ForwardIterator2, class BinaryPredicate >
    bool is_permutation_inner ( ForwardIterator1 first1, ForwardIterator1 last1,
                                ForwardIterator2 first2, ForwardIterator2 last2,
                                BinaryPredicate p ) {
        //  for each unique value in the sequence [first1,last1), count how many times
        //  it occurs, and make sure it occurs the same number of times in [first2, last2)
            for ( ForwardIterator1 iter = first1; iter != last1; ++iter ) {
                value_predicate<BinaryPredicate, ForwardIterator1> pred ( p, iter );

            /*  For each value we haven't seen yet... */
                if ( std::find_if ( first1, iter, pred ) == iter ) {
                    std::size_t dest_count = std::count_if ( first2, last2, pred );
                    if ( dest_count == 0 || dest_count != (std::size_t) std::count_if ( iter, last1, pred ))
                        return false;
                    }
                }

        return true;
        }                      

    template< class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
    bool is_permutation_tag ( ForwardIterator1 first1, ForwardIterator1 last1, 
                          ForwardIterator2 first2, ForwardIterator2 last2, 
                          BinaryPredicate p,
                          std::forward_iterator_tag, std::forward_iterator_tag ) {

    //  Skip the common prefix (if any)
        while ( first1 != last1 && first2 != last2 && p ( *first1, *first2 )) {
            ++first1;
            ++first2;
            }
        if ( first1 != last1 && first2 != last2 )
            return boost::algorithm::detail::is_permutation_inner ( first1, last1, first2, last2,
                std::equal_to<typename std::iterator_traits<ForwardIterator1>::value_type> ());
        return first1 == last1 && first2 == last2;
        }

    template <class RandomAccessIterator1, class RandomAccessIterator2, class BinaryPredicate>
    bool is_permutation_tag ( RandomAccessIterator1 first1, RandomAccessIterator1 last1, 
                          RandomAccessIterator2 first2, RandomAccessIterator2 last2, 
                          BinaryPredicate p,
                          std::random_access_iterator_tag, std::random_access_iterator_tag ) {
    //  Cheap check
        if ( std::distance ( first1, last1 ) != std::distance ( first2, last2 ))
            return false;
    //  Skip the common prefix (if any)
        while ( first1 != last1 && first2 != last2 && p ( *first1, *first2 )) {
            ++first1;
            ++first2;
            }

        if ( first1 != last1 && first2 != last2 )
            return is_permutation_inner (first1, last1, first2, last2, p);
        return first1 == last1 && first2 == last2;
        }

}
/// \endcond

/// \fn is_permutation ( ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 first2, BinaryPredicate p )
/// \brief Tests to see if the sequence [first,last) is a permutation of the sequence starting at first2
///
/// \param first1   The start of the input sequence
/// \param last1    One past the end of the input sequence
/// \param first2   The start of the second sequence
/// \param p        The predicate to compare elements with
///
/// \note           This function is part of the C++2011 standard library.
template< class ForwardIterator1, class ForwardIterator2, class BinaryPredicate >
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1,
                      ForwardIterator2 first2, BinaryPredicate p )
{
//  Skip the common prefix (if any)
    std::pair<ForwardIterator1, ForwardIterator2> eq = std::mismatch (first1, last1, first2, p);
    first1 = eq.first;
    first2 = eq.second;
    if ( first1 != last1 ) {
    //  Create last2
        ForwardIterator2 last2 = first2;
        std::advance ( last2, std::distance (first1, last1));
        return boost::algorithm::detail::is_permutation_inner ( first1, last1, first2, last2, p );
        }

    return true;
}

/// \fn is_permutation ( ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 first2 )
/// \brief Tests to see if the sequence [first,last) is a permutation of the sequence starting at first2
///
/// \param first1   The start of the input sequence
/// \param last2    One past the end of the input sequence
/// \param first2   The start of the second sequence
/// \note           This function is part of the C++2011 standard library.
template< class ForwardIterator1, class ForwardIterator2 >
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2 )
{
//  How should I deal with the idea that ForwardIterator1::value_type
//  and ForwardIterator2::value_type could be different? Define my own comparison predicate?
//  Skip the common prefix (if any)
    std::pair<ForwardIterator1, ForwardIterator2> eq = std::mismatch (first1, last1, first2 );
    first1 = eq.first;
    first2 = eq.second;
    if ( first1 != last1 ) {
    //  Create last2
        ForwardIterator2 last2 = first2;
        std::advance ( last2, std::distance (first1, last1));
        return boost::algorithm::detail::is_permutation_inner ( first1, last1, first2, last2,
            std::equal_to<typename std::iterator_traits<ForwardIterator1>::value_type> ());
        }
    return true;
}


/// \fn is_permutation ( const Range &r, ForwardIterator first2 )
/// \brief Tests to see if the sequence [first,last) is a permutation of the sequence starting at first2
///
/// \param r        The input range
/// \param first2   The start of the second sequence
template <typename Range, typename ForwardIterator>
bool is_permutation ( const Range &r, ForwardIterator first2 )
{
    return boost::algorithm::is_permutation (boost::begin (r), boost::end (r), first2 );
}

/// \fn is_permutation ( const Range &r, ForwardIterator first2, BinaryPredicate pred )
/// \brief Tests to see if the sequence [first,last) is a permutation of the sequence starting at first2
///
/// \param r        The input range
/// \param first2   The start of the second sequence
/// \param pred     The predicate to compare elements with
///
//  Disable this template when the first two parameters are the same type
//  That way the non-range version will be chosen.
template <typename Range, typename ForwardIterator, typename BinaryPredicate>
typename boost::disable_if_c<boost::is_same<Range, ForwardIterator>::value, bool>::type
is_permutation ( const Range &r, ForwardIterator first2, BinaryPredicate pred )
{
    return boost::algorithm::is_permutation (boost::begin (r), boost::end (r), first2, pred );
}

}}

#endif  // BOOST_ALGORITHM_IS_PERMUTATION11_HPP

/* is_permutation.hpp
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
*/
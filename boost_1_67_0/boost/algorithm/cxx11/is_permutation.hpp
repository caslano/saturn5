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
//  Copyright (c) 2010 Nuovation System Designs, LLC
//    Grant Erickson <gerickson@nuovations.com>
//
//  Reworked somewhat by Marshall Clow; August 2010
//  
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/ for latest version.
//

#ifndef BOOST_ALGORITHM_ORDERED_HPP
#define BOOST_ALGORITHM_ORDERED_HPP

#include <functional>
#include <iterator>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace algorithm {

/// \fn is_sorted_until ( ForwardIterator first, ForwardIterator last, Pred p )
/// \return the point in the sequence [first, last) where the elements are unordered
///     (according to the comparison predicate 'p').
/// 
/// \param first The start of the sequence to be tested.
/// \param last  One past the end of the sequence
/// \param p     A binary predicate that returns true if two elements are ordered.
///
    template <typename ForwardIterator, typename Pred>
    BOOST_CXX14_CONSTEXPR ForwardIterator is_sorted_until ( ForwardIterator first, ForwardIterator last, Pred p )
    {
        if ( first == last ) return last;  // the empty sequence is ordered
        ForwardIterator next = first;
        while ( ++next != last )
        {
            if ( p ( *next, *first ))
                return next;
            first = next;
        }
        return last;    
    }

/// \fn is_sorted_until ( ForwardIterator first, ForwardIterator last )
/// \return the point in the sequence [first, last) where the elements are unordered
/// 
/// \param first The start of the sequence to be tested.
/// \param last  One past the end of the sequence
///
    template <typename ForwardIterator>
    BOOST_CXX14_CONSTEXPR ForwardIterator is_sorted_until ( ForwardIterator first, ForwardIterator last )
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
        return boost::algorithm::is_sorted_until ( first, last, std::less<value_type>());
    }


/// \fn is_sorted ( ForwardIterator first, ForwardIterator last, Pred p )
/// \return whether or not the entire sequence is sorted
/// 
/// \param first The start of the sequence to be tested.
/// \param last  One past the end of the sequence
/// \param p     A binary predicate that returns true if two elements are ordered.
///
    template <typename ForwardIterator, typename Pred>
    BOOST_CXX14_CONSTEXPR bool is_sorted ( ForwardIterator first, ForwardIterator last, Pred p )
    {
        return boost::algorithm::is_sorted_until (first, last, p) == last;
    }

/// \fn is_sorted ( ForwardIterator first, ForwardIterator last )
/// \return whether or not the entire sequence is sorted
/// 
/// \param first The start of the sequence to be tested.
/// \param last  One past the end of the sequence
///
    template <typename ForwardIterator>
    BOOST_CXX14_CONSTEXPR bool is_sorted ( ForwardIterator first, ForwardIterator last )
    {
        return boost::algorithm::is_sorted_until (first, last) == last;
    }

///
/// -- Range based versions of the C++11 functions
///

/// \fn is_sorted_until ( const R &range, Pred p )
/// \return the point in the range R where the elements are unordered
///     (according to the comparison predicate 'p').
/// 
/// \param range The range to be tested.
/// \param p     A binary predicate that returns true if two elements are ordered.
///
    template <typename R, typename Pred>
    BOOST_CXX14_CONSTEXPR typename boost::lazy_disable_if_c<
        boost::is_same<R, Pred>::value, 
        typename boost::range_iterator<const R> 
    >::type is_sorted_until ( const R &range, Pred p )
    {
        return boost::algorithm::is_sorted_until ( boost::begin ( range ), boost::end ( range ), p );
    }


/// \fn is_sorted_until ( const R &range )
/// \return the point in the range R where the elements are unordered
/// 
/// \param range The range to be tested.
///
    template <typename R>
    BOOST_CXX14_CONSTEXPR typename boost::range_iterator<const R>::type is_sorted_until ( const R &range )
    {
        return boost::algorithm::is_sorted_until ( boost::begin ( range ), boost::end ( range ));
    }

/// \fn is_sorted ( const R &range, Pred p )
/// \return whether or not the entire range R is sorted
///     (according to the comparison predicate 'p').
/// 
/// \param range The range to be tested.
/// \param p     A binary predicate that returns true if two elements are ordered.
///
    template <typename R, typename Pred>
    BOOST_CXX14_CONSTEXPR typename boost::lazy_disable_if_c< boost::is_same<R, Pred>::value, boost::mpl::identity<bool> >::type
    is_sorted ( const R &range, Pred p )
    {
        return boost::algorithm::is_sorted ( boost::begin ( range ), boost::end ( range ), p );
    }


/// \fn is_sorted ( const R &range )
/// \return whether or not the entire range R is sorted
/// 
/// \param range The range to be tested.
///
    template <typename R>
    BOOST_CXX14_CONSTEXPR bool is_sorted ( const R &range )
    {
        return boost::algorithm::is_sorted ( boost::begin ( range ), boost::end ( range ));
    }


///
/// -- Range based versions of the C++11 functions
///

/// \fn is_increasing ( ForwardIterator first, ForwardIterator last )
/// \return true if the entire sequence is increasing; i.e, each item is greater than or  
///     equal to the previous one.
/// 
/// \param first The start of the sequence to be tested.
/// \param last  One past the end of the sequence
///
/// \note This function will return true for sequences that contain items that compare
///     equal. If that is not what you intended, you should use is_strictly_increasing instead.
    template <typename ForwardIterator>
    BOOST_CXX14_CONSTEXPR bool is_increasing ( ForwardIterator first, ForwardIterator last )
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
        return boost::algorithm::is_sorted (first, last, std::less<value_type>());
    }


/// \fn is_increasing ( const R &range )
/// \return true if the entire sequence is increasing; i.e, each item is greater than or  
///     equal to the previous one.
/// 
/// \param range The range to be tested.
///
/// \note This function will return true for sequences that contain items that compare
///     equal. If that is not what you intended, you should use is_strictly_increasing instead.
    template <typename R>
    BOOST_CXX14_CONSTEXPR bool is_increasing ( const R &range )
    {
        return is_increasing ( boost::begin ( range ), boost::end ( range ));
    }



/// \fn is_decreasing ( ForwardIterator first, ForwardIterator last )
/// \return true if the entire sequence is decreasing; i.e, each item is less than 
///     or equal to the previous one.
/// 
/// \param first The start of the sequence to be tested.
/// \param last  One past the end of the sequence
///
/// \note This function will return true for sequences that contain items that compare
///     equal. If that is not what you intended, you should use is_strictly_decreasing instead.
    template <typename ForwardIterator>
    BOOST_CXX14_CONSTEXPR bool is_decreasing ( ForwardIterator first, ForwardIterator last )
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
        return boost::algorithm::is_sorted (first, last, std::greater<value_type>());
    }

/// \fn is_decreasing ( const R &range )
/// \return true if the entire sequence is decreasing; i.e, each item is less than 
///     or equal to the previous one.
/// 
/// \param range The range to be tested.
///
/// \note This function will return true for sequences that contain items that compare
///     equal. If that is not what you intended, you should use is_strictly_decreasing instead.
    template <typename R>
    BOOST_CXX14_CONSTEXPR bool is_decreasing ( const R &range )
    {
        return is_decreasing ( boost::begin ( range ), boost::end ( range ));
    }



/// \fn is_strictly_increasing ( ForwardIterator first, ForwardIterator last )
/// \return true if the entire sequence is strictly increasing; i.e, each item is greater
///     than the previous one
/// 
/// \param first The start of the sequence to be tested.
/// \param last  One past the end of the sequence
///
/// \note This function will return false for sequences that contain items that compare
///     equal. If that is not what you intended, you should use is_increasing instead.
    template <typename ForwardIterator>
    BOOST_CXX14_CONSTEXPR bool is_strictly_increasing ( ForwardIterator first, ForwardIterator last )
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
        return boost::algorithm::is_sorted (first, last, std::less_equal<value_type>());
    }

/// \fn is_strictly_increasing ( const R &range )
/// \return true if the entire sequence is strictly increasing; i.e, each item is greater
///     than the previous one
/// 
/// \param range The range to be tested.
///
/// \note This function will return false for sequences that contain items that compare
///     equal. If that is not what you intended, you should use is_increasing instead.
    template <typename R>
    BOOST_CXX14_CONSTEXPR bool is_strictly_increasing ( const R &range )
    {
        return is_strictly_increasing ( boost::begin ( range ), boost::end ( range ));
    }


/// \fn is_strictly_decreasing ( ForwardIterator first, ForwardIterator last )
/// \return true if the entire sequence is strictly decreasing; i.e, each item is less than
///     the previous one
/// 
/// \param first The start of the sequence to be tested.
/// \param last  One past the end of the sequence
///
/// \note This function will return false for sequences that contain items that compare
///     equal. If that is not what you intended, you should use is_decreasing instead.
    template <typename ForwardIterator>
    BOOST_CXX14_CONSTEXPR bool is_strictly_decreasing ( ForwardIterator first, ForwardIterator last )
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
        return boost::algorithm::is_sorted (first, last, std::greater_equal<value_type>());
    }

/// \fn is_strictly_decreasing ( const R &range )
/// \return true if the entire sequence is strictly decreasing; i.e, each item is less than
///     the previous one
/// 
/// \param range The range to be tested.
///
/// \note This function will return false for sequences that contain items that compare
///     equal. If that is not what you intended, you should use is_decreasing instead.
    template <typename R>
    BOOST_CXX14_CONSTEXPR bool is_strictly_decreasing ( const R &range )
    {
        return is_strictly_decreasing ( boost::begin ( range ), boost::end ( range ));
    }

}} // namespace boost

#endif  // BOOST_ALGORITHM_ORDERED_HPP

/* is_sorted.hpp
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
*/
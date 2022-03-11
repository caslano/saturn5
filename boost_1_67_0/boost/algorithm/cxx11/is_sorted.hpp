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
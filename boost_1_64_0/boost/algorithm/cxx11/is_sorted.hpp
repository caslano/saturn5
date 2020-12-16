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
QUd2uueftorvujjIyYuqOZl828o3PDdCEkZkOY2S5g7uYJJrSv2zhqipbjz3/doC1nIeFxSwKGxQnlP+Hvtpvcg5auqZgzVuZCs9IHyc85RZCM5fuw8J5F/cgkXRhaldjam9KjS199UDdaVnW2rsPvEp/gadDLHPcSDpFvO77iqe3yXkbQ58AOf7jux2hR0N+++iI9z4RDReUgPU+q/BoBu60BSyCiHZhAx35DT6C9dbmI2F25RHeO8fosfY9pynpn4NPlqcHWMrOZdQTv2YXxNsJR3wRodUFnailm8npnLxGcxUxoCpjANDSRf79V9XDj3RH9BOcYppFXgJ9aIj4I37J96DTe1ttfO8Z6xMfCLuvVgvYddRdFTFIjflNqccIJYL1llDZ3JvbqaTvUbqrkxMj3cHJPFscaIi3+ApGHQcCErKyO8JCqXE8Z2LzutGwZxL12S8NZYs/6oYJAwgDPpkDvfC4//Eh8knHiM+Dv5SCFf28YOJetrcFmeq6per5Xrl/U16EwvbOTg+Pi3cbRllVKLhnX0S0gvw05TpWfGhvm4IQ3FUUKwB8ieMI+2n7S51w+wcU6EVzB3vnno4ccJgYBywRTYrPUJYniY6lrC8+RarqTK2Cx0zNcX0JPtTnCcI+pjVhnGWj5Zug+5qm5PtFT1pUvlGGnTXVj6gpTEbXbtsa4Pqi50llb/HjKBaKdvYoMKsmMglA+TymFOQyxYmF49OLt2/JcYaqidYqs7sgx0/SgxCCfbnm0ixD+jiBh2lJJTBj/UgFbcrxJvLXJkb05viG7PmWKBUmaua0NFU48kfQEX84MCz2F9T3HjZ3dPRB3eUo+/n2d4oiRnsameSH7gvCX9clg3qPqwzLPUGy2P4t4V/x/LvOP7dhn/H828r/07g3235dyL/TuLfyfy7Hf+20W9sJoPoi8UD2pmW4v9K/H8T/9/C/yD+r8f/Lfi/A//34P8+/P8S/7/B/+/w/wj+q/gf50Kd5hhLbFybeGuCXfy0TUxKbmezt/oj8jf9Uj+514acnXWJZfrK8rs5lkbL81OuJr1p/yQ6KZHKSWdbtA8M6nLlvPVEYfVEYReCXrL6CwpbwBR2l05hGw6AwnTHadCoYmKRfnkwq0zY2ySM8QsHhd33yMK0y539Y+/Ci0F7eC7BJoLt5DyoCpd335MV5VY8ln4zNafUP/X3/r2xuW3XlVFEJVTueZu0kW0QyFXyXg63D5oag74o42MhRKTylULpPL1fkol0VLYzYfl7lyaEvCqEkFHI8w18AnJIvWLiltS9YsC8JGB6GzANykdQ+UvlS0XFZ2sVv5FG1hS1k9V/hziIqGJkA5zuzliv31+MRUis9hk1HtpUifNPeW0Q86UV+Q5XeKiGDmI/AqJIylPX6kWhYNmFc2DzXedq9yexb2/rLFlfmOooQ/0Mpwbz1GoCuns/VRRTZs6OKUzT4A36Wgv66q3x/zxLEMfGJ8QqGD/G4LfAr+Xvrz3577f6cchNxpqQzWuCX1sTAsFfQj4WR4qPmfTVCePn4LUGd9jU1DcGYbe8HoLEowEk4sgs2Nr6e61Jtz1XUwdf2YHtPtuIldJmh3W4xWZ3wRJ9kF3OTff2T281UB3q49Myi1YftrMcXhmKxHHiLGyDxcQC4p28XyIX4G+1mdBLKgruRnymfr6kp6mbD9c6YMoQOGKT5EBA6eKwVEvjAyt7x5iwUiC+i4VC8cQc3uWw7JJ8/c3jqxeAz5Z/vH/1myiIk/xVtAmAXixFkv1c3C+N978OPm6UzaguP7Nv9VkOy+7+vqT5sBalL26TAketkryWi9SU/wnn1NL4DQ8lED6Bo3GcgfTahXIPR8aH0uE=
*/
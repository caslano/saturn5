/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  none_of.hpp
/// \brief Test ranges to see if no elements match a value or predicate.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_NONE_OF_HPP
#define BOOST_ALGORITHM_NONE_OF_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn none_of ( InputIterator first, InputIterator last, Predicate p )
/// \return true if none of the elements in [first, last) satisfy the predicate 'p'
/// \note returns true on an empty range
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param p     A predicate for testing the elements of the sequence
///
template<typename InputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool none_of ( InputIterator first, InputIterator last, Predicate p )
{
    for ( ; first != last; ++first )
        if ( p(*first)) 
            return false;
    return true;
} 

/// \fn none_of ( const Range &r, Predicate p )
/// \return true if none of the elements in the range satisfy the predicate 'p'
/// \note returns true on an empty range
/// 
/// \param r     The input range
/// \param p     A predicate for testing the elements of the range
///
template<typename Range, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool none_of ( const Range &r, Predicate p )
{
    return boost::algorithm::none_of (boost::begin (r), boost::end (r), p );
} 

/// \fn none_of_equal ( InputIterator first, InputIterator last, const V &val )
/// \return true if none of the elements in [first, last) are equal to 'val'
/// \note returns true on an empty range
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param val   A value to compare against
///
template<typename InputIterator, typename V> 
BOOST_CXX14_CONSTEXPR bool none_of_equal ( InputIterator first, InputIterator last, const V &val ) 
{
    for ( ; first != last; ++first )
        if ( val == *first )
            return false;
    return true; 
} 

/// \fn none_of_equal ( const Range &r, const V &val )
/// \return true if none of the elements in the range are equal to 'val'
/// \note returns true on an empty range
/// 
/// \param r     The input range
/// \param val   A value to compare against
///
template<typename Range, typename V> 
BOOST_CXX14_CONSTEXPR bool none_of_equal ( const Range &r, const V & val ) 
{
    return boost::algorithm::none_of_equal (boost::begin (r), boost::end (r), val);
} 

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_NONE_OF_HPP

/* none_of.hpp
r7Ye1dIkn7RlQvXNkm/2ozhmsmywBPo+Bxxsc2SicdKe6lkBh3dkkrd/ii/2msDeGEdGTfm6vy98WDpcK6lrJctWh/dae+Boov4pb1lZmfdaK7L50Ym2oVlxEl33A44B6bCCZ8lSE0Jvwto+GdXSBH8f76BYB5ppJgy8iXRqyPIU/p6w9PPzf8LtXZgwvjreIAjtCC3xIIs+iMcqojjg5XcsyVYLU5wFQB1keBpLGJpGmQ8/gxyKF0BUJFPbJ9CR6R1covA96nAZIBmoMcPRtU/p+pnJpf5p8er6uNlXm02l66clwmYmXg1cRK+0M4/x2qBPxB8Lf4t7zfjgz5BCHL6B34KwnPIu8oFyIQaS/249SvSNMaQh9yW19SVdE9gHatgqFX8VA5qbiO+DJHzerqcT/ayVtjYapFzepbTu6nCCBCnpdI0q/JKvyI9rRoLgQd2hCRP3+n1EgSfTGsFfLv2BB404iEs9N3NgB1Mr9qhoanm8s8da0CVGWJJ3YXCdvo52KXDMzlcUu9CUHR+kbndaPszYNUGy9rFIsROq+1hslt1FxyhjRqKkBovq6LEuuXTPtARJ3VjERRwwmub+c8hXpUgqmur61uhReQP6E91p2aD3ZkAqVtCb1UZvzj3rVHqz+1l6bzbtScnitwxIkizBaRqJWrVroOiIIP/2tuHjRU72phl2ZL+U8dBP2wdD9eDwPaxx1sdM4pQK12iZ5x6ulT8MHLPxsFh2jQ+2xF/B2fpF8tcknb8eSQlnzy3z162gwEc0/roWvMsa6nnBX6tb4a/bQENO7+kGi9UZpt/Xfwt3ImKDxDi88dzR4L2WDZJlvbcd9/Uv17/NXJNceESbCn2HF6awiQcJv7WeM5Wrf2S7AHuEMw9Iinp8y0xIdfdkw99GGtV07tvC1pYWw78zZSS3QZW0bfWOs8pV55pmsxMau63isM3bP9aboxzfYewdRwP80ykAx6a/q5Jc2aDKZ+SsnXkmkquRrNyZ8K1KdwxkXGa4yqoOtkvlHwu58sjvk0y0lx8FZW3ItDESa9QzleqJ2ctGKR9I5ftE8QouvlHpguKQZ9du+kV/dHkkeJi7Wd4NPOoni2beSySd6e2Ed4g89dQVye/jOWub3KiMWcfv7+IdSH5hJePDTzhpJZLARbKU1A38vkSAPEIgJd9QEmolRUPcHOTgTxn+COkGBv3WdRrESakNjB9xbH/wELeGVjkgkM6f4RsHqR3JIQodtbp9JBzlVjTwqXbwROiRNZBPiqrlI1rlwTtTtNgPygAoJ3n7FX9ZEl3bs0jluWYyIliNInSYzKS3QJCejHIw0fghTrvRI4IZElJ8TJ3Fx8+5qOxWQCClK42FMncVqiq4rmtXbGSKkMGHwA5ff6uaequjg6kX4GaeJx8LnUczAOs8kmzwOIuVfJY1B1Az/sE5qP/6S8kyahAhugYNEEfI7HAdxDmJblL8jOU4yv31oUI+GXiQ+zNrDx1B1YLsNPmDd4G8AcwdRZNj5CQmSo9dGXGUZwhR6hVIZL/IfJdE5nAQ3WwVh2xFX9Jk5jA2NxDhAv5S3n8UT401FUpwSd0X5nzH2s5CSM5cO5dGdYdhaCZu3J4vCnlqCBfU3wwhlKr7YtPJ/4j1fcj3OlMrxidNhW2ZL/CGYZWFAMagVzA279EQ+5LntEHSW2sa1FUxzNnirkQppQ9ggF6vuFy82R7zU/GfHCk+H9S6fst3jAXsHzl2b7IJ9eAkkHr5Mp8rqOwBlsqUjaHPfnoHPrsOqQDejmeCTBIirjSKDojkuHE/ni7sLISHdQ4h7eW40iBfHLypfm+cAzDKRn+DmhPXC49yo81H2ms4MRl2mJrd6ew=
*/
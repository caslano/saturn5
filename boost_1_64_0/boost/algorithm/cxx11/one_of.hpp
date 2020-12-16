/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file one_of.hpp
/// \brief Test ranges to see if only one element matches a value or predicate.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_ONE_OF_HPP
#define BOOST_ALGORITHM_ONE_OF_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/algorithm/cxx11/none_of.hpp>


namespace boost { namespace algorithm {

/// \fn one_of ( InputIterator first, InputIterator last, Predicate p )
/// \return true if the predicate 'p' is true for exactly one item in [first, last).
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param p     A predicate for testing the elements of the sequence
///
template<typename InputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool one_of ( InputIterator first, InputIterator last, Predicate p )
{
//  find_if
    for (; first != last; ++first)
        if (p(*first))
            break;

    if (first == last)
        return false;    // Didn't occur at all
    return boost::algorithm::none_of (++first, last, p);
}

/// \fn one_of ( const Range &r, Predicate p )
/// \return true if the predicate 'p' is true for exactly one item in the range.
/// 
/// \param r    The input range
/// \param p    A predicate for testing the elements of the range
///
template<typename Range, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool one_of ( const Range &r, Predicate p )
{
    return boost::algorithm::one_of ( boost::begin (r), boost::end (r), p );
}


/// \fn one_of_equal ( InputIterator first, InputIterator last, const V &val )
/// \return true if the value 'val' exists only once in [first, last).
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param val      A value to compare against
///
template<typename InputIterator, typename V> 
BOOST_CXX14_CONSTEXPR bool one_of_equal ( InputIterator first, InputIterator last, const V &val )
{
//  find
    for (; first != last; ++first)
        if (*first == val)
            break;

    if (first == last)
        return false;                    // Didn't occur at all
    return boost::algorithm::none_of_equal (++first, last, val);
}

/// \fn one_of_equal ( const Range &r, const V &val )
/// \return true if the value 'val' exists only once in the range.
/// 
/// \param r    The input range
/// \param val  A value to compare against
///
template<typename Range, typename V> 
BOOST_CXX14_CONSTEXPR bool one_of_equal ( const Range &r, const V &val )
{
    return boost::algorithm::one_of_equal ( boost::begin (r), boost::end (r), val );
} 

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_ALL_HPP

/* one_of.hpp
a6x6PDfRHVfjm1L5aMEQl1ySRFdoVil/eltHDcrIHgBhFz3r9VJubw+Xd5RVSREIn0MIwwPXV9u0UvIu5Qh6AFLoGLUKX116tdWU0/fF46ebZngB/+3tKRRjX5ln+ValAz+L25uOm3x0S3eSlQxAYrFs2CUcAghOjpZqPt3RejdxsFC/VNyq6SBuFzqIf1xMOoi/QQexUxn+CbXtDtG2zcggwfoSKzP7542CN4mCL4cV7IKCgJm96T/5I/htaYO2yQgQ/7+NKYOuMTJrtVV8ayOSyCUDHZ5qYo4tWm/cfbkOxe67TV9cV2Bc5dO1xXUCkpWUGFpc+9tlXBQbJBZXVXTYU5lidTTHC9aVyzOJv8uv9PSTk6LZ/Hy9XjD5GJiE9zJ7klzyNXaaXnnqGGvTacb+NMx5MsXBo/CQcDJn7Z1k99BhU8l6TwP0Nr/xF1ebW8NBjkH9NndBv1hyyzHQm+RX+8UGI/E5V+DD3rvuqG5QI/PjwvLv2tk8/4sDofz8vzfPXxeWX9RC+UVh+ZevbZ5fGpZ/m9I8/5aw/CWbmuc7w/J3vNk8/9yw/H2Wb5u3P/z7X7XQ/n+G8l9c00L7Rb5UfoOZqeqKHkkmBn4JKtdm/gkuFIXmikJyXA2M06DZjM0xexLl9i45z6pMxEeYUKLdP7hKq8AsYiNnxHhuAcFPR230lYuUxau1eXAOkguQrCSpNGWGWWkWhC4luIgq5f5W5IRRYIpBgSFIQYs/xyOALi/+5RvRoywwVo0TKF+gHKzQUO6M5BVIVkZASudJa8eZkSUrIMQ6SlHGg2uIxBOX9UTXp34TGs9t7zYfz4Nfh/JvqmievyMsv2F/8/zXw/IrWqDXx8Lyp0LBEhF/Q4vcMlGDkuNG5YZiCeEe9jCs2p0W/gmr9rD12LbDHgqyH37jBqvnIpDf3Wfwsj83DZVUvsaSCFbfO1EArrYeCwjeWjuGaFXYa09V5uylbq5nCTORL5WtEgzys+pk0yo7T6KVQgx1MVAlknqNSinMcPUanVZ4rlS+RsD/3YA/uELAZzL8Xym7V2cEci9/R0B6DciNGmQ2IGEX2WuUlcDWCrCbDLDnNbBcAstz0Tn2XJd8Bulrzwe5PDw2xeQ9y+WdbFVKq2lN3Kjp5VEBHdl1hqdENUj2xMXHLDMri8emf4vLg3XDKsZra+T7Yo1sqErGGvkM1shdyrEPqFvcH9FOcDfSpfKdfPpJ2lLURRVh1u8SHyoHAC2+ryOXZg361QgcdHsjKtJipJJF2ilMnV/lR9hnxH2lUZqj6xg9+pbQ/qrYqDY3xIigV93DgZja5bWaRJ6lOuVaSa7n8Lv7nBCHU9Ategh7/T57kM+Hsr7ha0duEoMAOdOhyW++WFx33fRExtqtjTI8QC1f5ypozEPcWQp0vBMqwlj5u7q4mfG+Ceacf87YBrpIPOToOtXs6Zul1vWix5jCS0r3zOwqyQd996iHP0EVx10F5KU4z/IBV+GxqhstP5bumaUg72NXwTFUzxeW+FQXqEVifJInvPzzE/6MsvY45WpsAZ00U/7GKujttgc59rtsjvC+Bs9rXf5OQsskK84o+0PDzL2DqOm+pFIeuIIjMDGWbQjG5AU5wlcaYnZVGvGgzf16x2KhwVlFid9TD1OLOGbq6Ms4p7yxrs3MBKfvWrMzZ+uM5/i2D3gHa8lszmMITMbaG82zaLdTsMDIvZZpRbDBB79kSkFcY4kCC+2X5ONEJe0keR2xRu5t8Ho6OsT4le6xPehDMaYXzNP2ryaZqEfGaMGoeuUX3A01fZYgFkXrDQSYR4fkWX4QHSJlOLameDo5IYj3zJOv25oG+688OINRFjmtNPnXrEw=
*/
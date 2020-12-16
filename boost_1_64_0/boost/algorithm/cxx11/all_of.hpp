/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  all_of.hpp
/// \brief Test ranges to see if all elements match a value or predicate.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_ALL_OF_HPP
#define BOOST_ALGORITHM_ALL_OF_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn all_of ( InputIterator first, InputIterator last, Predicate p )
/// \return true if all elements in [first, last) satisfy the predicate 'p'
/// \note returns true on an empty range
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param p     A predicate for testing the elements of the sequence
///
/// \note           This function is part of the C++2011 standard library.
template<typename InputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool all_of ( InputIterator first, InputIterator last, Predicate p )
{
    for ( ; first != last; ++first )
        if ( !p(*first)) 
            return false;
    return true; 
} 

/// \fn all_of ( const Range &r, Predicate p )
/// \return true if all elements in the range satisfy the predicate 'p'
/// \note returns true on an empty range
/// 
/// \param r    The input range
/// \param p    A predicate for testing the elements of the range
///
template<typename Range, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool all_of ( const Range &r, Predicate p )
{
    return boost::algorithm::all_of ( boost::begin (r), boost::end (r), p );
} 

/// \fn all_of_equal ( InputIterator first, InputIterator last, const T &val )
/// \return true if all elements in [first, last) are equal to 'val'
/// \note returns true on an empty range
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param val   A value to compare against
///
template<typename InputIterator, typename T> 
BOOST_CXX14_CONSTEXPR bool all_of_equal ( InputIterator first, InputIterator last, const T &val )
{
    for ( ; first != last; ++first )
    if ( val != *first ) 
        return false;
    return true; 
} 

/// \fn all_of_equal ( const Range &r, const T &val )
/// \return true if all elements in the range are equal to 'val'
/// \note returns true on an empty range
/// 
/// \param r    The input range
/// \param val  A value to compare against
///
template<typename Range, typename T> 
BOOST_CXX14_CONSTEXPR bool all_of_equal ( const Range &r, const T &val ) 
{
    return boost::algorithm::all_of_equal ( boost::begin (r), boost::end (r), val );
} 

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_ALL_OF_HPP

/* all_of.hpp
stBQSGisIXmhkLzoUrxd7rmltu7yAqeij19e5KXkBYfCfZ1KoiK9GfQ7JDXfVk3bTtyhTEx9CBNoIywN8Jvk+utkUksOFU77Rmwk5h1O1PO8UzDvNJp34qV8b9XFHPEOSQiod7BKJgyE393EM+6ctBl3oZKcccquSkyw8wP6fppxJZw+gqacVm5MW8YQVg3pdl5TwI/5p4zABBR96OjI4l7I4Q9T8/BD2ftKch7WH68I+/29n10Rdlx/4dpDFA7VJh8C+ckOefamnNb3Zm/OwUshry1rNktyXgteSyL9tKjqqzu8P/zqb1j3Tw9c0hcJQX21HN6cI3tf06Bh52J+mPdihvdL04aqepxUsojsEE++iJwrnkoicp54KozIzg6H0iA7mK5nb3kpEFHd+BaIDMRnchiPyC6R1xOR+4gnR0Tui3i8iVdXOrDZcgwO90fw75dEf+jmWH0FJjOYRmxQkO0J6I/Dqpo4DABR9eWJ61eydfMoTWqxKxxkQBvvQL1q10YZLtWYr1/BfK3Fbc1xVapR4+2Yr5ljYIWgDrHFHtcIYL5CpjYfpTdJIeywhHD3AhWC2y6MUCdPvd3itH1qk5x2kqZ/jzcqKbDRC9Yym02tHEmf3RpaKZyvj5X768zQ+M+ZYdSHKyJ+KF4w5zSO9endpul7YKShm/A7u89XTzax5UU5eC5GCAhjaKMa3y7COePah9UAbpW7H5i3fLod2vjaPetP3jh7y2xs/eAS/k1Uw/S+7gXZ7gXw/Yxg3nbk4q20LoKrAYP+jbA3YWIPD0mr1XCd/eKYfQDwnV+S2QZU5+FxeTBzeU17Tl4r+COSRthoODLxv0akBjNr5LzllRFtAIyUK5CQ2SbnNdI75RgtUcEV9CqpMMrc8+go8J5z9HUanXQD6ZPO4SuezT3zrlDwhqXfnxqJKc9+Kwe6f1sikFczKmI/Ry3/0H3/Lt5CJgzphLFkyFITsah0EjGe8+7iHWMaPuY7/9zTLkf/YxKoN+PlF7AstxbNNVMs6vrDS6lFcyp87E7S4hay9QuGnheEbxAuogbRUZfJLK9vgCkdyyRhASM6KIQaFcTNNX1gQ3EvkPyNEdepHTjrjP9ySuMR+6kRMpsbdW5PoHiwu18OmwwXa7qoPrmQ2nanWEjNTy6kPqVFFO+HaDRJ0tY1gqU8dxvjA3Q7X1giWsllICK2MnjALbTskPXThHWTYqDQEmGwDLJWjGa9SSVlLX+IvyWSPyQywLyN3V39Gu2BiGWhgXX94zxrD2n6dhXW15C+VYUBVvMe1LzvYAtChcCLb8KqopNscZM1/BLR0cQUbi+88mgFVVcNWUxLJb3JuxqXQcTfk4xaWEhcyjCbopPN1p202SYsAFSs8sko4t+oEu5/T1VPpslwp9VdVpYvsrGxNtmYaR/Djnkd6aSlmExDaXSHRlylvOZ6p93ZAyEDkgiB0C+tjWQzNoAXEyHP9kLIu8CJGn/fDkyoU162dmOm0tLmTrH+F0eMxMqL+n+RvEisFesC3qYQIhbF2yVNqocZWzZw0Q+GLgOMOme0nt8Pqy5Yh2qVKBAzbq8abrdVv0VajkDIMkbI+9B3FJrlPREyfVgaMtak2Q+bGB/5w0QfsaZB/wQ+ZOF/NIkkzn+sIiD2+8QtOg/fYjGMe5ekM4wXmGHIWNRCNDFvCJq3EWwI773P/eAvM1mOQFwkRQ+fSDP5RZscG5nzODiyVBvfK2H6PcXBnW6owZJ7egX417cftHERcWemdzUOT+LgmaAHkCIM+xIco2zwII9oBUZEO83gwX27/WKO196Go+pUy34CMry30H1/J4M7zsCiFhG9SA4WKlK7cgPc7sCdaLcB25A=
*/
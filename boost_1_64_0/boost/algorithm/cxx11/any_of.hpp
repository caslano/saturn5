/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

/// \file
/// \brief Test ranges to see if any elements match a value or predicate.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_ANY_OF_HPP
#define BOOST_ALGORITHM_ANY_OF_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn any_of ( InputIterator first, InputIterator last, Predicate p )
/// \return true if any of the elements in [first, last) satisfy the predicate
/// \note returns false on an empty range
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param p     A predicate for testing the elements of the sequence
///
template<typename InputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool any_of ( InputIterator first, InputIterator last, Predicate p ) 
{
    for ( ; first != last; ++first )
        if ( p(*first)) 
            return true;
    return false; 
} 

/// \fn any_of ( const Range &r, Predicate p )
/// \return true if any elements in the range satisfy the predicate 'p'
/// \note returns false on an empty range
/// 
/// \param r    The input range
/// \param p    A predicate for testing the elements of the range
///
template<typename Range, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool any_of ( const Range &r, Predicate p )
{
    return boost::algorithm::any_of (boost::begin (r), boost::end (r), p);
} 

/// \fn any_of_equal ( InputIterator first, InputIterator last, const V &val )
/// \return true if any of the elements in [first, last) are equal to 'val'
/// \note returns false on an empty range
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param val   A value to compare against
///
template<typename InputIterator, typename V> 
BOOST_CXX14_CONSTEXPR bool any_of_equal ( InputIterator first, InputIterator last, const V &val ) 
{
    for ( ; first != last; ++first )
        if ( val == *first )
            return true;
    return false; 
} 

/// \fn any_of_equal ( const Range &r, const V &val )
/// \return true if any of the elements in the range are equal to 'val'
/// \note returns false on an empty range
/// 
/// \param r     The input range
/// \param val   A value to compare against
///
template<typename Range, typename V> 
BOOST_CXX14_CONSTEXPR bool any_of_equal ( const Range &r, const V &val ) 
{
    return boost::algorithm::any_of_equal (boost::begin (r), boost::end (r), val);
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_ANY_OF_HPP

/* any_of.hpp
M3MVXAoTftncmRxHmwG0Q4e17T5NRwJl2O4O/4Lt2fvpbZU7zHGqpTospymhyR0mMoHP0hmnZWTM/maO0Rhu3GTUwJTK0e/IVHlDQvE2onf8RuTtbRGP3hrQLz/K4bpCVaqlC99pne3A/+weqLYOLLjjtOC2ZyBJc3hoUe6hL4rH+hTI8Gjla+75S+iGulB5/JtfFnWjOe968YjmBF73En8Rzl1SC66EItTS9VAngG/nRewXoPg9UMaWiaHSG7Hk8tbG90mI2ot1DDAZB1O3F2Jjtf1pjpa1XGBWj5OQh4vGsiXCoTEhezdSm4M1qRWy5SW78Ajk8STBP9ZaB2DdRUFd8Bxv24wlRFsir8VcCRyklcAh/K+mLUFZ2t7Cd1z2PyISGHDQvaDWTN3EqTWUSplHGJzetjmvlpIMnqgPMW9Plz5Tp7H2MPG/ZZMw7Y9FH+n06dsFC24wr8cSc4+PN2MiCyHIwq9dPxmcvfjm+cQKT9HrwNlJCpSVhshjUY70VS1B9wbJmYVE9C96eOrA2MlXLKnlB9337xUOnTgZHW+3Y5tfmRKHzeAdoU2Li4mI6ROnEGKYliOP8Y7gARKJmncLSUMpgQUJs2aLo0AoYxiJEQkRsVpIrSCpjpd59FUWvyYaULCclxojebSOD9cY1R1QC8AOMkW8Vpdd8WMz35WjkLzwrq1+3+pRSDoYkt7BNmX1j3UGGCByewIUi4wsNFo4JKb4mClFrqc1lQgGXwvzGYwDAFIF1/FAvgr4ZMCnGlJnRWRYfBsArDeq3+sub0jUjCi1DycNmikYDrbC6TRa0JEZPZkNzNZGwr91d/FY118cdNx3nXVSGgSooUdiMBHEpCD6Y8YsSPB8xcQm40sgdRDTI+0Py6Vu1WhIJ8c3RdHkdVdLXSJo1K0uLXadC0PDQyXH33EA831it+/mSEJyX0oRj27zUaxTNiA30YJHf8OMl9vF+1jlnYp7VGdA2iaD4sqXVWWDoQX9H7A6hjUbLDccTrHNggPZ4gl4qdqL8SQUZDwI/TgQudUdnPdBtQ+rGn0l7gjAfuVR6FdUSoQasQC0+qbEt9oV7yFN2qNJh7gT4VEwcumMF4EPRra18HsWD9b9BP42swP17DeH/WFcJ6O3pPfDqD+WrgxOs38FiqFQ31hsQA5Ezi6Of+AILzOq37XGlbXPXusr+/BSe7/u9P6EoHdJjhbQMmsqRXv/z1tmsSJNVgrEEnDzfUijxfjGI5nxhDm+dZ88vwv5nceQn+y9mJZJY++PrrHWfN96Ps3HC1yshrnYDnA79u2yPP13kOfWTLqT72VqmRw/FnqYpA6E33Ujcq/SUNNpGKi0AQ4n0wc2wIYlgnnWQVbQehDXeuxCbAFxFZ6PbK4hCs1M6yCuSfhCiaQKsQSNiSdROjaBXNp4KZf4OpYcKG01IrOmx+1w5ZwJZbTYKA8EBqclhqOMwgmAHWu5pO/QFbelGRWv/udw1fT7ExX9/YVTaRAGXG0NQtZz5iAEIa2rJ4X0tzT965NDJKL3p+P+ikyh8U9mjKn6m+CF7sD6JO7rNGnv9AJ4nxFyGzTy+Eg8/RW4d0tdqmTgskJIzRbgGLqO2xNsETiFNS1UA6+VmsQAXJkkMtVQGnL56aFZjU1wa+U7ZuZSqlLeWlWGwxicApPyuqqhGszvIWFgXls1CMWbxcoZ9WDFXZWnYtn8dTIJT6YKNCz5vVDC3+QX7wbxs6OHPfnSrBq4+GSCp2t9arRYkN6yNSmOH3LmkUs9kUv71AQjDvb2ae74fFp5sZ/Ul5GEtXOwBv8bYO4buWk3aQC7osXGd5Jfj/uBOtZX90OFWMTbwpUGF9WkBi12MfJpp7w=
*/
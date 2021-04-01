//  (C) Copyright John Maddock 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_IS_CONST_ITERABLE_HPP
#define BOOST_MATH_TOOLS_IS_CONST_ITERABLE_HPP

#include <boost/config.hpp>
#include <boost/math/tools/cxx03_warn.hpp>

#if !defined(BOOST_NO_CXX14_VARIABLE_TEMPLATES) && !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_CXX11_SFINAE_EXPR)

#define BOOST_MATH_HAS_IS_CONST_ITERABLE

#include <boost/type_traits/is_detected.hpp>
#include <utility>

namespace boost {
   namespace math {
      namespace tools {
         namespace detail {

            template<class T>
            using begin_t = decltype(std::declval<const T&>().begin());
            template<class T>
            using end_t = decltype(std::declval<const T&>().end());
            template<class T>
            using const_iterator_t = typename T::const_iterator;

            template <class T>
            struct is_const_iterable
               : public boost::integral_constant<bool,
               boost::is_detected<begin_t, T>::value
               && boost::is_detected<end_t, T>::value
               && boost::is_detected<const_iterator_t, T>::value
               > {};

} } } }

#endif

#endif // BOOST_MATH_TOOLS_IS_CONST_ITERABLE_HPP

/* is_const_iterable.hpp
KeoRZliKPhWbjcEuyrAYjCShq9ROyUzuDgX7pKHl9RFFT6UIM1mimmAlutyZpk/t0CVCIUfz0RhPaSq3jEX2MnSws9n/K9u7qqmVYML49KF/RIY0BG4hCZTvOVnAqjlixZxHaX0eGy7GNCiX1ICpMj0CV/R2pSqv/KvmcFtxka/Sl94L/8izHurL5q8qKwuCq8m6/K3bv3+QXDCkM0F3REuoluSgrzvkQ79+luXNuDWtqcgh9APxZt3WZK0L+uKJ0c8k7qdoWPuqzmZ3wKJVqqLyetCKif2MAc8Iar4WzaupvfdD1yXU3X0CoW7Q6QNBvharcNvYy1Soc38qY8fo423cJ1ENxQj/OL+Ie6SMWUzwqF8aTkQ50m60/suNrLv3R3BqfdCJi3I9v1hi/G4nfUkMvADC0SjgZUZROvkSe+Y7piV/H7F1dXq5zm4dq7CLeWPWjbKK4RLByr/jk+FVWsIJ6t/MSOl4cqMlWoie3HqkFw3ynz5VIX1LSHvX3toGJMe3RiRBRskxrWR5sAW537SZApECfd53pBolDVDOZw33wS0rQlGPs8GwBw==
*/
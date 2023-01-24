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
22K2r95LD6uqcFm6Iuie4Bz+HC4/e5Cmjy81Czzg56E8qXabGb1n78jWnN1IzFVphPQgBmKpl62XwMuWLtviyTF9IcuBNSHOi0KbHRznReTpeZBiInARV4nbNwP3sVfWlT/hldZV2axyS8WdRuoCQm6p+DO8JSd56OS1GIzskOz0Z0Jus5J7tBGXOp6hRVMKhvUgTx6W1+FmCfuu07SQeJShsRwGw+mHkWYHwyElitIYsjpy8+ApG/9k4p8M/GOzb8PKnHxVFrSJ55eYWTwqYItqrUOwVqlh9QbEu/RY+mM4oI+lP0jmDdtRlDeEie+KI/mW/I/tAZe57cP8PsG8QbtXV+FCf1tjfp999vJPhTLcTLXbcW85QVfo9E8GE6cuL128k7rFYQVqBFCnq6DCmNGuFWsawLcNZ49s7QcgslhdnuF4Zph6gFqjbF20FwAeqGANB4mFBZyTXiQw7cch1Ta/AGMbatkjy0Anuaz6CXeZWZiuIHQ5P2sfvN1+VSoP3dX3LToq5LBsb07FD1cqH+Lfwvm5CQdt+50qSefvRZqJrxtlvpMPHlIyxTC6Kx7lNegCRBZkNVBF27FIYANtVZHWEhHg/H+awovRM8DklGq3G23806q9ZDSw3vNITqmydWENEK8Z6Sk/sPJnPmMsFbifgpYSQqtGIKEgqQkKqTXHdUxquGdHJYe+e/8viWyUhxHZjd/riKwWQJYe
*/
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
kHkmk9imJJYZ6tqNLyiFEyMkn32e4fDgAMufEfsmHKW41OoTDo/xo2/DzTFmR+nRl9TXfL8sIjYCpghiEztseCWeKGKn2mtSLrkg9ejqFPPhSJF0jVYpZKvtu6pi01FA+eN414pGRSxiSaV14vWP+jK+1TsYOW2b0DYakcPGl1QkXG/Iu266IYbdQTaKy1ntXJdsr1/PkCmxpjGDJCQYYsVL42qofk2mkWi1FG2trcP7tJHxsROZ1Ou1UGXOkkdMAknK+fR8eVPMF6t0GpDnq+V1wWcHR/PJexCk6cxreevf++ey1GRV7CCkpM4vCqIsvSML2xuje1VSiYcN7u5hNaanF4uzq0CJxkL3jmWdIVmTfMpZR6ZFQph0xuMjLvzMYOh333g8lFSJvnXDJDEmisHvli9GU+ED4h1FDEWI77z8+xgfv068iR2ZN7SdyjCvWx9itUEYJUTlzcHVNHLVwuKBSGFia+08yvNQmwfp2mmp25yFcQzJ4fWZRuzci0vxn4gj9ssPNjl59PT+ofWm5dPbs+ubxfIqYidDjin2+X54Y0HyK0nG35j57uf7C1BLAwQKAAAACAAtZ0pS6BaKXzUCAAC0BAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEwNDdV
*/
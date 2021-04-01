///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_EXTRACT_EXPONENT_HPP
#define BOOST_MATH_EXTRACT_EXPONENT_HPP

#include <boost/multiprecision/number.hpp>

namespace boost {
namespace multiprecision {
namespace backends {

template <class Backend, int cat>
struct extract_exponent_type
{
   typedef int type;
};
template <class Backend>
struct extract_exponent_type<Backend, number_kind_floating_point>
{
   typedef typename Backend::exponent_type type;
};

}}} // namespace boost::multiprecision::backends

#endif

/* extract_exponent_type.hpp
DIoNi+X6np5Cy3sj0g7Evcu+aXQzDShT3J3vEWIhXXOybwyycYs5CK5kKykvWc34sgdVcPmZzwtsqUI2ms8+ntF6+xA65u4q8zKHvzm861ZpUvVNDpZbmgFP747J5PRL8UKQeE0GI04tdSItSf6ziysK+nirHxYMnU9BEOAM1MjCYTqPRF7Xl9bBZFu4fiGjQu84/ZLjYSIRYMh/OEXEOGOkeqMM81SdhlZOPgU2Rs1EaAfjmoyKlBTddA9b+NhJ2DwMb8icXcRHijHL+yXsV6u3Oiogwr7LHlv85wFwTzuwbvNuGqob7KaMi3KDtnPhQ2bFNN8XLmyKs/vTW1LKsjKQrzpV1U+CZH2vOT3xYyVL+4/Pb/6St42OcLhLzsWc3Tya3MUYDyVEJ+Sha792cyzedSghUiGFV9T8Y+5HcHjhglTsCJIST00KkxOfgc8mh1ExHVesCGUkXMJ3Ngg41pGLY5b1GEbN4LIp2JsPfXWyC/EYEBmMu6Q8yh+AVLa2prhm7KTRHi865oYDO2pPrLYpWFQqHkFuJCXr6euYsfJTJYuOO6NBPpPJFg==
*/
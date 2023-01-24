// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IS_NULLARY_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IS_NULLARY_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// From Paul Mensonides
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/detail/split.hpp>
#define BOOST_PARAMETER_IS_NULLARY(x) \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_IS_NULLARY_C x BOOST_PP_COMMA() 0)
/**/
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#define BOOST_PARAMETER_IS_NULLARY_C() \
    ~, 1 BOOST_PP_RPAREN() \
    BOOST_PP_TUPLE_EAT(2) BOOST_PP_LPAREN() ~
/**/
#else
#include <boost/preprocessor/detail/is_nullary.hpp>
#define BOOST_PARAMETER_IS_NULLARY(x) BOOST_PP_IS_NULLARY(x)
/**/
#endif

#endif  // include guard


/* is_nullary.hpp
R1pkqgWMyxOfJTNNf9G4cX+0G0tU5HAk4f5tIxPFph1jmqrGtvuTz+Rd/0DnU2Wg0NZG52es1tywvLKtkM/+6WFGxSYYI2Yri5qeVdLKtC0HXNpNhjXhj1q31FJTVzroX0xafNvbBBb7biA0DAnUeGZV2qx2LxzNY09QNEMiV36fWc0pjLIbbx9xQUamCP64ffzF0cxFupis1mD6I+u4iZds0aGsZiMZw8OLIHvhA03UE3syITvay7lBZh1JZKCS/ZBbjDDNbSNPvZmw1ck3aJ+Se8jlo0O7IrAQ3I5kyO9AvtrlAYhspnfJgTMKr0VyMlqP6ZT6pIAXMl5DWspjxTd2iKfwp66fXxPvwp5ELu5k1hm7ZC5xL6JpYB/Bipcil5xDgkPf6GAf7TI6/dw5fJCtWUN+EEhGZ5nQ4O7zLjRjF/k2+S6DncunDM6UfJeZLYufthfdID+8pJvqQME82wDLwpffEEEKcNlcXGJJpEGEupSQU/nta4R99DVa2Amdd7t3mQ65xounGnoSJv5Wlbg1C8ewHS3jyifdb3qC7U3kLScTMPlY24A110GyWXUXqh9ntI8Xggs55P5tL5/DJSrXKA5uRuxIi3JW6P/q7teULygTBhCMLfNByhNxijisb9pv8vKR3OOMYwSENFBdYUBbG3fmJhuYh7tuMHbc7+8GsYgfc9LT4MokokSKlWgSkVu7obs+/g607LE0
*/
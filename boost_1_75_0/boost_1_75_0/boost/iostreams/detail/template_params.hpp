// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_TEMPLATE_PARAMS_HPP_INCLUDED

#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#define BOOST_IOSTREAMS_TEMPLATE_PARAMS(arity, param) \
    BOOST_PP_EXPR_IF(arity, template<) \
    BOOST_PP_ENUM_PARAMS(arity, typename param) \
    BOOST_PP_EXPR_IF(arity, >) \
    /**/

#define BOOST_IOSTREAMS_TEMPLATE_ARGS(arity, param) \
    BOOST_PP_EXPR_IF(arity, <) \
    BOOST_PP_ENUM_PARAMS(arity, param) \
    BOOST_PP_EXPR_IF(arity, >) \
    /**/

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BUFFERS_HPP_INCLUDED

/* template_params.hpp
hLPBfqH5xDdU2c8onR4QlatVQHqalqtyCwqsZR20uyb90ewV5VnJsVEX4qvrqb6X0c9SW+v61Hp6PoRKN7refDN/d4CJ8jHWDxsbjn1JfnBI8TasiwQr9dN8ztJcHliIbcmlP5DcvpMvsrhld7OJwcghHXg8QEI8K0w8EHQt+8t91Wlpkd9XoN5vCdjxlwbsUjufrosCuGn7cxQeFEB4vYrhcYckcBdqg0Zxa7FKyX96Fm6BV+LG3kdQgZNu8rHF/meVswfr5PuHgoxFf2BAyORgE/K3ZIe1q05tXA7u0QwR0H1ThVhgtzlHFmjAd4fCzP+wir534FL96fGoPQITYGpiqKmn2ZtRRM0/Ki5ydn+HqS7ucRAgh+1RQSboJHrTXyI/Zib4sF0zJi5W6YkS72eA4bjVv+jFx7fEIV9rGd8k/xokNEjx+XPlvZ96YyiQqrlWnnzkUD4KZmGBjrrSET1xZy33gznom104/fTEEMzF3I2/nuzIQ+YW2C3rat+n5MnrexgVjwo8ORD08UqvCMtV28AatVns+uU+k6Wsz6x2XpWI38OhzYvKqo5XqdKvU2zHF5w3oJcsYLbAWPv+d4XGylD4nhZzL3FpvcUHyp5xF6RMp3alH8x4/Cyj0WNssnvr59bSJNhu37+R8Xaz5y15tVprZR5/Dyu/wiuWZ+8ZnD3VL/la10vX9042gGgBpi/0LKB0J3gkYcgU
*/
/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_OBJECTS_HPP
#define BOOST_ALIGN_DETAIL_MAX_OBJECTS_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct max_objects
    : integral_constant<std::size_t,
        ~static_cast<std::size_t>(0) / sizeof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_objects.hpp
r0nS0TWCXGqVWfCaWAgcREltAunSuQF9r6K2i98/XRSpDg3JRYKcBA80pvZJ5MphbHuQWQreDhCeFwojbqOxwN6T/tKVKzRzdje8F7g4MihmiGP4qWsw+U1NnDdzcg/Ib/4pB7DklKlIOqzMaJ/6u04BKEbgAwpAhO5r0/fJqxJRqKi4QsiyY12oaFAT7c4nx+W/BPJBkLi3H21jmedTZ9VhUL6Jxy+pFoygk6KJdEo2P9Z/ZCGYQTR31y76C9sP0UYZqUYO2ZlCz3OB/dL1LMzuVYbWTH08VevjkJINlscvmr2w84KlFo/DNLN4Z0P+bRElli5SOF3+GDpUI9fl7zVp6CUQHuilEmeeqqtMAFpMclmdGF4nWSclgk/Ap/T5vN1pb9erNL7EgbtB4AHd1shQU617cUJYZvhHzBh7o1G40yigoi72uiMT8oRity05hQFDCCR85PLzvxucDoYlc5QjUcyANK5+BjEfW4Evv8bTmKf0mYxHco7bq0vjyKGmdspQ/f6viYqTc7LnVrt3aLIqZLkTBErwcbFp6d8j4RS5/LGX0308AIUbwA==
*/
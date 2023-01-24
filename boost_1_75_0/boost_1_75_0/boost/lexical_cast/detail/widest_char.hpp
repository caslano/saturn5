// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov, Antony Polukhin, Justin Viiret, Michael Hofmann,
//        Cheng Yang, Matthew Bradbury, David W. Birdsall, Pavel Korzh and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006, March 2011 - 2014

#ifndef BOOST_LEXICAL_CAST_DETAIL_WIDEST_CHAR_HPP
#define BOOST_LEXICAL_CAST_DETAIL_WIDEST_CHAR_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif


#include <boost/type_traits/conditional.hpp>

namespace boost { namespace detail {

    template <typename TargetChar, typename SourceChar>
    struct widest_char {
        typedef BOOST_DEDUCED_TYPENAME boost::conditional<
            (sizeof(TargetChar) > sizeof(SourceChar))
            , TargetChar
            , SourceChar
        >::type type;
    };

}} // namespace boost::detail

#endif // BOOST_LEXICAL_CAST_DETAIL_WIDEST_CHAR_HPP


/* widest_char.hpp
AzGz9MslmwqpEfTX4kn8H6BIuGW8+h/ShIXOqhPK4ykJbQz9hkaVy5r1/da+F3p78pfg2WDk6Q3FrTw05qQbUfI0ZtVbfpvjUdTU49IFFyXNBj7WlRaxiEh3kVTEGM8Rfj3/I8z9HDMsMz3/8G2fyxWcVZ00dZUNPpxMtFGxaU3jSo1MXyress8gm2IIO+H18/VD6/JF1/GoFvnrKQVWeBeyeY+t18yqOhfR+cU66RkuFOsJ5u5CUHoYAyDJz5pkbPS3PPqzh5lxcziy57t8tdPgzEEhTiTsKeytFt8vJrTo5/oAvH0ObXdHfWVewJguY8a7DbMYplU5koG63CjO8o+uIcdMHHUEcXIWTNi81eZC+zbcH8iFdi+CY4v6y8Dy7CC2RzW0L0QjdQZsy9BSzekgSrUrhtxt1Z9lwiKYTKlGjuE1G48qeuNcSVKjBtyYDKv8Vn6KidOuZcjGqW70LSgGjIb3YORSaRdUsrd4uqfNGZ8jMXsQfdNlacA2bWJE5RUhiUe6As7qO2WlXh6+W1xyO5IFD5rL7ZlfKYiFyadkX6Lfu8cFG8PIlg8PJiquPfRgz68BzNW5gf0ggeISnqfg2kZ2cnLkuUHIt6Jhz3BH8QLHmVQdtYrwNxUHb66EKsUsRqoW63zvoOAnmI+u+l2q7SwtC+QIXtMJp/5aJLGzRLv/FJrPpylWQnH7PPH0mKrtRQBnfHqleQ10
*/
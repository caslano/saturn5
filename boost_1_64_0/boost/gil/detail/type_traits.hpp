//
// Copyright 2017-2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DETAIL_TYPE_TRAITS_HPP
#define BOOST_GIL_DETAIL_TYPE_TRAITS_HPP

#include <boost/config.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

#if defined(BOOST_LIBSTDCXX_VERSION) && BOOST_LIBSTDCXX_VERSION < 50100

template<class T>
struct is_trivially_default_constructible
    : std::integral_constant
    <
        bool,
        std::is_default_constructible<T>::value &&
        std::has_trivial_default_constructor<T>::value
    >
{};

#else

using std::is_trivially_default_constructible;

#endif

using std::is_trivially_destructible;

}}} //namespace boost::gil::detail

#endif

/* type_traits.hpp
d01akY42wvZmsB0TpMHWblpLSnr8Como8Xx0yqfeTq5c0ZV9JRNDtEZEWthF5i34JcyrV0qQFcLHkmVeiUd6TYhF/Khaheb9go5wxhmC3Sc5my1ny13tnweyXAiO2662rtjFJziRCSQOGeDsSApoPRAyO81QcuZeA8fPHFiXTkIcri4SzowKbNJHUXws81aUUlUYt4kuw/nee0KIAQGDs3haO3yndsdJcr8f53s/NUHqOFGMlGPPukDdNUbBEZiBJ/ja4KQh0bQqA9ot4y17sVNwOJDzBwjWjt/oAGD0XoWx36vaNXvqViSNdb7VRZoQcJQ6MX3elQL7mRZz8tYjFPcme/OZwjRmn8XvsZ15DzB4NwKYejY4hWtY8QLhxsMUiqs4k48jtHi+0+hDw5YTINGnloduWM1TBoRvFuTG1bKBE7A/fpeW2iBOd6Y2z7h2hgquXKZ59qfs5GEW0kKHOqpsmOn7OToYHo2zWOjR7PHBopasKy/Ls/+kY9OnMdIU5n5g7TCrR2dwMIeUMU1HvMnYyCRBpXo9bk9K0aIh05wN6P40Ytjs3pHVYQ==
*/
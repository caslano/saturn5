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
8B82eRESUkf1uVMtjZuITKxTAIlYJKbRSCTCQPMSjIl3N1l0W8KM3idWhMOhzJCKeARlLiD/c4QBCal0HSafKIzbGWMeRAjqEx6ZBxEWgAzbzTRHfC6psRFmiUJOyIJpJKNSURKXiVuOLKTkJRZAEsZFJMY9Y4r6E3M7d9fJ7pDUlWbGoqJSCZ0ZZswqzmQc9QnjQjt9p0ESWQht/o1GRUlcZD8w/wsCZVzoc8FukFQW5hsw
*/
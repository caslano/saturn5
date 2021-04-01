//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_GLOBAL_SUITES_HPP
#define BOOST_BEAST_UNIT_TEST_GLOBAL_SUITES_HPP

#include <boost/beast/_experimental/unit_test/suite_list.hpp>

namespace boost {
namespace beast {
namespace unit_test {

namespace detail {

/// Holds test suites registered during static initialization.
inline
suite_list&
global_suites()
{
    static suite_list s;
    return s;
}

template<class Suite>
struct insert_suite
{
    insert_suite(char const* name, char const* module,
        char const* library, bool manual)
    {
        global_suites().insert<Suite>(
            name, module, library, manual);
    }
};

} // detail

/// Holds test suites registered during static initialization.
inline
suite_list const&
global_suites()
{
    return detail::global_suites();
}

} // unit_test
} // beast
} // boost

#endif

/* global_suites.hpp
wpUl/HxQhJfZ6JcWMK6JhUoP7ZZV45p8h0mHSTM4YEab5q0kjhKEvybhyW4tzh4guxQ/Qii+8ccdDGpLlNkHsg9Y3HGB9rymQWmqvJKVJ5g4LVpf1WqyYuhh3Rn3LcVTWq8OaWWm/RBXuPNwJMwacrANpUpqU8GyHSWmyWTlEJN2ddPjUSsWvvoTVc45rP3xFkHIPDnfCc7PGOtTJuMNQoOn9To0pj3ZTmcpc2CJVqZhoC1AcI/BoVvXkDg8hz8/imekTuKIbnH9vuYdQQlV39mDcioM7eQjEkVLrZDQDLvZ/dUufJoe/GOoyvDE4fxTrg7fEjYBaxaO5KXE4Lvi6HlNmv+WOxSdbAJOVO8fYR0c3VaWF0hJnMbeeARZ9M8rSAVZ3DeHFiiOMCdjAHE581chUYylZQWfggFhpszbokXydYJF8l7qd25HDdzXlZDYVgv5k7EBMYKCwhR1BawyCigKTQrXtiXDGgC+X5kkWHr2v9pdkIUGyrKGDHXBcFzradPuI8aGH0WmjjOIbDdsdJ7QzycAKmMqE5BNcIFn7P3nm9XchqDB2Zprlg==
*/
/*!
@file
Defines `boost::hana::default_` and `boost::hana::is_default`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_DEFAULT_HPP
#define BOOST_HANA_CORE_DEFAULT_HPP

#include <boost/hana/fwd/core/default.hpp>

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename Method, typename>
    struct is_default : std::false_type { };

    template <typename Method>
    struct is_default<Method, decltype((void)
        static_cast<default_>(*(Method*)0)
    )>
        : std::true_type
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_DEFAULT_HPP

/* default.hpp
rcPcSLurE3qFPQBEpb2LPcyDlRygrSZz1e03mtCk5pt+VmCnWB820H4S8SyPj9/lRaBsOZecS4BEE+1zsST5E9yW+P4BnfSlPWw0khCtujud7B5+YkWjdxy7vVswkBNqHMxabq+wZ5zZEHDD0Ivn/NU9xIO1jNceKNkeyLK+VQWDxTctRw7NXH/Cn/uFHBq9Caa/laWN/urFGPlqVElWy4TAlAY5gMRufqsG0msIcHOhtMBSqFjY/yBjAu0VXykZaOPNe5d2TcXX/wBa1oheacyuv3LyVzYNk3IFCHXJ7BjKu4axKO4mYfNawl0d8IAyjQ2tXNBZqHonZ0qJYu12NIoEunZrFkx0dKHzX8SanyGAR2k9hCvMKVkfb5ypJvuXCHQ0KPa0hWaXFDk0KC1na7CweZOldQwjhSnJwR+qBjr3k1QHCzsqoP0Fkpcr15cNYp4JMgC/kE3XMl7FJoW5bcASBG59z2UY8ngUJpzIEqhRuHkxOIJ9MxhpoX2QWqgvjvABWmMeOkCTQTqxuejMuGfOhHGPWX0UwolvOY5G46LFUR8qyR2ooqb4/fdDYjafNnNY/H99FJ5gqn7vRfinNqh/RVByh1GpfQhuRuxVKIHy9ON4feJJLGd43RN4PhogPKGJTkoT0KxVS+moJv7aKjo/TUr20zMgq9Dp9z+H5a7EQ5r4bS16vaAz2HUUOlbuEEY0+FJqj0rAY6W7
*/
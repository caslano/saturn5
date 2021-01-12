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
1QnwP21dWazrC566srxN3ifAb9kmR9jk09anmhzxNnnKZAD/K5Bm6t7nQSPqbfIKAe6zaPSxPc82ptBAjLfJJYkXQzz6m2toO6YvttU65Yy0SWH9trBuFnaLpzDEpNNvW0hAbqwzs0SucaGgQbw5JIh/sjGFOGI8s0SARwBY7TApmFxHLvp6+nUkfb7Lswsu5cjrBNLn+5HIx7vdXIW8WyArAeSUD4LsRn9LC/Pnoj6uu+/H
*/
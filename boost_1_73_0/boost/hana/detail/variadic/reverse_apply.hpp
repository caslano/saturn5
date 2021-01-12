/*!
@file
Defines `boost::hana::detail::variadic::reverse_apply`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_HPP
#define BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/variadic/reverse_apply/unrolled.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    BOOST_HANA_CONSTEXPR_LAMBDA auto reverse_apply =
        [](auto&& f, auto&& ...x) -> decltype(auto) {
            return detail::variadic::reverse_apply_unrolled(
                static_cast<decltype(f)>(f),
                static_cast<decltype(x)>(x)...
            );
        };
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_HPP

/* reverse_apply.hpp
7O/K2iFmreSNJmsj3KwhKyq3syNgFUe/Is2nHqBOdHZ68+lEebIKE/E7AJ/qMaFn0QteP8u7kkHZe89iI4Cw/aQYbukT1y5evHyQ9UxKx+BDszJ1DN6rPk4VKHMi+Wa4VOgcbTjOZgnLz/eq57N1KagTIarFm2ZR2wuhz6uPyiTxmgZdd3FvtP4ufE1HgItXYDfJlNMtiZ3CxNy7kGs1MQ4u8PHomi8H8GgAey5GXqXAHKXg
*/
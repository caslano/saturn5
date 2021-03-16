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
/JaJ1ln1C/uyxlDG0vwFbpptaZK9KtpWQYH1WsWoM/xWMYq820j7FRBoTxAzWUvDwoa5i+JN9fEGOXFoLxEVY3yD29Wn95wgFe9OPd+lq7kilUquUC1PjcIX/DZkaYrMkZnnrS44dwruZWx7khQNODzfUWvSlIVlCd24qDWuD4sE17xo2Hs7op3cV1MUcvG3NNeelBKcxu/aTO3cX8ldvSb3s2qbFzUtjJu7V2vTnol8HP+ysrSTRzq3u+yhdZs=
*/
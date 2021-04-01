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
p6lqCjpKkCKWMmfCj/NQ/LZTXxmlxqRH2vv0pIt8ar5XNKnGtCllTUZkOtPEc9KFKldaiG3HAPG316vvZ/VnosZpBt8UeajVVhINLfAudP5Na6NJio3tPRtHHXo/rdBp2+1jfb/YuguBnPHKbXvGGHJE7ah1uZU8jsQ8bAqhx7olo58QCxiD3F2cNIQEl28OS28aF87j8fsSq5s0PGQ6+jpihQDKhP+1slNZFntyuYpYtdcHk18koc8Mu6yAbHvAKQaHOm9JQitbgLWkhu3y4/Djap6V56wyvUO5cwLg3hssjJAAD0mYQg0/sLtSahjZ561HKxjMT45+00be39UyeTtl3PSOmcsYPfQ6g2D0EA9luZBEv3Y3UCOEtPMf1M1I5+sf9HNQ6Eb7phBLAD9wveqKJT1HH1YFeqj3kMZGf67InFVW6EkuE0er5kxfm/TFLfQcn3eGJIBymuesHlCE49SED/F+wjpYp3BvxuqEgL8DJ77NCrTNz6Dxqrb6btzq7c2lGTm/Q5fGLbGwGma1StjArW6qa5ZqvhbQHHkOiLHZEcbzfCSuNebC4Q==
*/
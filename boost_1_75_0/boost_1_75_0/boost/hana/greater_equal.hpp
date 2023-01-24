/*!
@file
Defines `boost::hana::greater_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_GREATER_EQUAL_HPP
#define BOOST_HANA_GREATER_EQUAL_HPP

#include <boost/hana/fwd/greater_equal.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/concepts.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/if.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) greater_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using GreaterEqual = BOOST_HANA_DISPATCH_IF(
            decltype(greater_equal_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::greater_equal(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::greater_equal(x, y) requires 'y' to be Orderable");
    #endif

        return GreaterEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct greater_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X x, Y y) {
            return hana::not_(hana::less(static_cast<X&&>(x),
                                         static_cast<Y&&>(y)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct greater_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::greater_equal(hana::to<C>(static_cast<X&&>(x)),
                                       hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_GREATER_EQUAL_HPP

/* greater_equal.hpp
ItW++XvaDcwadGTQ7alldyfQsKM5RjEBnf+yGqJWT52/Vva2FSJElzb1LdIjvhxQj6V03Nkf/lDdEnBz03H4vPu7dtVrDdEhh9tKe/aS33dy9by3WQEs+HQG+dXazL9dENiCm9eIxJudtPslMHa18BZzxbP+XtjY1rD78klRNKAI8QZrL2hmrq9TD9QqBbp63cYS1BW7+WAm65ng1megXSekq6noeqEyV1s7sfz73O1hXBeVDuHXSaE1QaF5lqoPQ52tCZybuC5PIMMZ+/DlnwJ1F/vTTttpX+t974VVFIHgNZ8vd3LLP+ynayd5WTmgG4hTW3xPG3FXjduSbT2rVV3YN9zT2Z9DGmy+icTfI+Hizf2RsJwxNMZxImwJcXKVJpN5ca3Jw+QKUvWgeQgzuCwfvms4sr0J+Q2gMfpkPSLYKOdR5MjutxsP7WelO7JtVA+g6gtvy+n/mA1VfM9+9r6xV8OM3i1e7S6K6gtCyn+IntvXk8BlHq57qYsJyUjA/37baLu7bCaWlogPHx4vz1zVhzsemykuxjF0HCzZuDc6QvnmNIrWVy3q28I0fXtiBb+0N0e6J/1ymXeWR5wag++H1pct6rursn7QBtc5ytMuUdn+2w6Da0T5IZ4oyBwxeMVstHXLLE8o/eDOhry2eKYgtMDp6yePjx4kHnApVJF0lQRayH4Yv+C5qNwJLUg02uBPDBkOXm6LMimQ
*/
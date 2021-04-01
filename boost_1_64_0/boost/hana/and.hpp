/*!
@file
Defines `boost::hana::and_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_AND_HPP
#define BOOST_HANA_AND_HPP

#include <boost/hana/fwd/and.hpp>

#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/variadic/foldl1.hpp>
#include <boost/hana/if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) and_t::operator()(X&& x, Y&& y) const {
        using Bool = typename hana::tag_of<X>::type;
        using And = BOOST_HANA_DISPATCH_IF(and_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::and_(x, y) requires 'x' to be a Logical");
    #endif

        return And::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }

    template <typename X, typename ...Y>
    constexpr decltype(auto) and_t::operator()(X&& x, Y&& ...y) const {
        return detail::variadic::foldl1(
            *this,
            static_cast<X&&>(x),
            static_cast<Y&&>(y)...
        );
    }
    //! @endcond

    template <typename L, bool condition>
    struct and_impl<L, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::if_(x, static_cast<Y&&>(y), x);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_AND_HPP

/* and.hpp
/5+HB4a6/bXFnrhItuiqP9Jw5Uh2b+ihKtR3pFjm3eyZr9w/9q2gRkjQaBs25ULM6hBcvAdk5vn6AtFGsiWhI+Oy9+Mmfp+siekDHUqKzJzBkWm9h1e0tirOGG5rujKohZD9PKF5dK4MvWRGGTmsYM4AGHg35y4kJy5sWvFYhiWxQfs8SAJ4Lu/Tw435VN9BYjMVe3H82dHwGeyPypcYthELXsLnyXYHd7zmLflY2WBNg2Or8GJQHnTjaIB2SWq9gF0K4TnZGN3AE1cQ+47AbyRLZtiN01RKnE3RT8rCjbgzS7fAcDGTkTfJjB6iJ+0nh7G3e+tx3U2T+KB6iMEvlCzthUQz1Pde4D0jyQrShzLuTtThdu/WU9iwy9PN2MfFTQpwZD+xoOWLjWiBlOnsrGupNNEOYtmwz8O0IO0Go4zgoeJ8+lmNSRcbAXUFSw67SlJOOL6zSD4E9T3YqyUJk08DEgJEA0LXhPvWhTFX3+OhOYa8FJmihaUft6J4Uib2SfJDJGw/5gAG1UrvXPjcIYmT01D6r5jfS+BhzVebYqZTyDYFD9VUvuJypQ==
*/
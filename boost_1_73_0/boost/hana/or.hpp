/*!
@file
Defines `boost::hana::or_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_OR_HPP
#define BOOST_HANA_OR_HPP

#include <boost/hana/fwd/or.hpp>

#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/variadic/foldl1.hpp>
#include <boost/hana/if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) or_t::operator()(X&& x, Y&& y) const {
        using Bool = typename hana::tag_of<X>::type;
        using Or = BOOST_HANA_DISPATCH_IF(or_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::or_(x, y) requires 'x' to be a Logical");
    #endif

        return Or::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }

    template <typename X, typename ...Y>
    constexpr decltype(auto) or_t::operator()(X&& x, Y&& ...y) const {
        return detail::variadic::foldl1(
            *this,
            static_cast<X&&>(x),
            static_cast<Y&&>(y)...
        );
    }
    //! @endcond

    template <typename L, bool condition>
    struct or_impl<L, when<condition>> : hana::default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            //! @todo How to forward `x` here? Since the arguments to `if_`
            //! can be evaluated in any order, we have to be careful not to
            //! use `x` in a moved-from state.
            return hana::if_(x, x, static_cast<Y&&>(y));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_OR_HPP

/* or.hpp
4YK29RgFIvqbQwbRg5RHy6ij3ctGZOQKIM7LRlvnZWnWX+ix2ATJ9dZ0c1nIs1OKL2oZsXbBMOFR1ZFYI/Cpcz3Du4vp/MeLq7qyV+WS9RdYIcXxTJLsvVdgARAe7525tNcxpFOt4zoK+qSJsIges6xoqDr4lH73cYiVca3WDdGIsVLpuBgfd8MUjonqhnszplHmbL+MXziboyqWO9y7CZy8pIsNOlJO+Um1kShG44qTAmSl
*/
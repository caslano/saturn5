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
/nLIpxYXhCijW9vurbF3c5i3FeoNbHiZPvq0HCjIMdLg6//hCbij80OFtM33tpAXMFIh2vexazWBzcbU9G81TFIKf30ZIUgy+j5kZv8WP72aDhmCDm9E748O5vYA4scpOq4tqUNOXx0G8rrULwy7fbCI/ioMXkoIjqCtG7i38hhZ2tl/LMHFu1z9sHFtWg1vA1AoMyIuuwWORS2STFjmjV2JBieDgxMQ46UyUR/XtvsojG/9pZCWzHvAw33vvlMkSW+f4uCLQ64PwUw9J5H2E5ySnghya6lUj6FHQ/KHpe3xSA7VDO/2p4mdxVxLb5/t48iaR164SjiyM24wGb3PN0iluWRIcVXslxXCyj/i5I8IVo5cWse/Xj+/qSjE2hb9pgWbDbcYsc3WWoCN8xebyU6Z1KDWZ6vQTPvnyJZqG1mf2Sa9Te0kVlnPctMK1u5alev9U87o0TUoZqYS3lZCrfgZS/f4zJGSVmPmCWqJtqXvEPeyqmxTYEEIUrv2mOAU7TL5aygkTGympDYFh7y2GJigfDiOLmaIsmKidmGlmdpJ13gIu9t9kwcZ0KoTUNu7OOncR87Exn65d/2aAXGF9d0bW9H8fHt0gza2cJn9wY85ETjYelvnj22NkJkEwZ1ok1lweh9cTCmHwR5NBzKvXCA3Ra7NiHwWA8EcVb+FKy5rR0eBa6h57gc8LSnrSLp59cGTRunDXT/iPaLq
*/
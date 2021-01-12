/*!
@file
Defines `boost::hana::first`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FIRST_HPP
#define BOOST_HANA_FIRST_HPP

#include <boost/hana/fwd/first.hpp>

#include <boost/hana/concept/product.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Pair>
    constexpr decltype(auto) first_t::operator()(Pair&& pair) const {
        using P = typename hana::tag_of<Pair>::type;
        using First = BOOST_HANA_DISPATCH_IF(first_impl<P>,
            hana::Product<P>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Product<P>::value,
        "hana::first(pair) requires 'pair' to be a Product");
    #endif

        return First::apply(static_cast<Pair&&>(pair));
    }
    //! @endcond

    template <typename P, bool condition>
    struct first_impl<P, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FIRST_HPP

/* first.hpp
+ZBzkl6hj699I3UDTxrVnkyUTC8/CYXMRKGXgBPzNOfotz0tlgFc9YEqfbkxVhh+oZa3W6WNnbgbBTYiJ8/6u2bbA8dxnJ0pAN9nDIb0oa5YWUZcFA5cWu4Ywu6ygLtLXSFF0i5NotTJBw0Qr5ujbB0PrBdwWn2DL2nhjguk9ZCemuwh3NkNkn4oqiStfsoroilvn2uQY8Da10D4uAm3Inz7ihtXwUhG1Fkmd2jvV4D3ZyOx
*/
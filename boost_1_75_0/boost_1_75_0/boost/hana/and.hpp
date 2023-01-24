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
dcXzzI/77TVkSYmv315Vf79strweVtmSfB1PnPuRWINr8tkrcL1/pIF/3gPqK2wsJefN/POXTCz00Kk6g4dg6dvWGhOGgN3d2ZnH5Z/I84PIFj0lxhu1agivLvzJup/tHro5CY0/+AQMyBhqaFoXM0JZiTrC+/TSl63ZPqM/yjeWYLoRGV/8WnPNTE99u2ejW7c8yNYaSe41PtFo0gBJZvZjJjKXUzBgdv9cZAX5MPBIrF6glk7coBLCbZ70KTQVun2k3sttdKQw5FZXzWB3KjeotfKn6pKkSAf1xJCKISuC2RhSnot6XmF/vWqVU3cHdf3QWBCHJu5ZUsQjI1TNK6Vtj86iEo1c7TsvkgRmQVQdClyHg012FQ984svhwA31pFep+GYbnbZS/2o+ok1jwY1HZIoHeaOBCkPyQMHuuGaYtyNKYambJ+//U5JOkJbw3g2pXIAzcjoQxR+tr7NLiBGxZoTBIg/u4J7WYeG2+bb052u3uEmtP21Cf9cgXdxs22G0Zuk0dr0xNWA+VY2B6zxIlVbNknNSptqG4/g4ATX4g2PFmg4z9aMMZUxwNf7U86crwORrMaznjzjU+WxJvI2A+4xGkQj0+jjcL/azhpgZRTxBm2O5Hvi3mbxPvXQWy1E0wSLmI/YfyeiZf6sUTDAJsETJmsoEgRo6R++0PxDSFR0YbBeW0NvktpQhFyxHzrjM2YdoxsVSDqWt
*/
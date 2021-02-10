/*!
@file
Defines `boost::hana::remove`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_HPP
#define BOOST_HANA_REMOVE_HPP

#include <boost/hana/fwd/remove.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto remove_t::operator()(Xs&& xs, Value&& value) const {
        using M = typename hana::tag_of<Xs>::type;
        using Remove = BOOST_HANA_DISPATCH_IF(remove_impl<M>,
            hana::MonadPlus<M>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::MonadPlus<M>::value,
            "hana::remove(xs, value) requires 'xs' to be a MonadPlus");
        #endif

        return Remove::apply(static_cast<Xs&&>(xs),
                             static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename M, bool condition>
    struct remove_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& value) {
            return hana::filter(static_cast<Xs&&>(xs),
                    hana::compose(hana::not_,
                                  hana::equal.to(static_cast<Value&&>(value))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_HPP

/* remove.hpp
m3xJbVpJWX2T7+mUUzJwOlLnbls4VjIN5aG/X4k1hpdrYCQjKnaAC+UOCLAabYK48cq9YfOg0OCS0I1VGlNuaQ7vRAlgWbXhxMSc/YlbnbUC73vDiKr2tEXK3EPdWXZMKNyBPIgMBpvUiwMhs5RMD59gAnr2RU/hq1xxkERhyWFm5syxBPFmBWIynmqqIGJ4vPXMqYGYc4VxnbwFyuASknFiHSM7aMlaLykUjcfmHsKrNkZP7q2hEq4oyGi4XixsSHzfhyR8EA70PXwlnvpA8RRoCWsmrZrzco2IpaQ+XmqDquEIQZJaQ9c5E4yiIOod2e8y5pBmhfm2WK5fJK6nib+YPyMNGYQ0DNvOrhUgM3a+H3HKZbsBYFFkhKnt2PB6aebffx3doimZRbhAoTHg+7RPiDzx2w/NrBUbGAZrW9zicSSiZS/DoRmQNJ9roq7o8bkytDCVN8xMg5pagrk6WUeeCvsey7xy3u0ZM0PX5ERIUSqA9ZHU1DisW51pQnSY/PEuFi/a91ic5e6aW7k2suUDOVnbUv6c0Qy7ZOaswo9eXcS+aH0Z2sGG1SXZti2mbdQMDEKcXq/DD8qtgJgb8gcbCaDFKr8ME0qyaVZFXOGNBkMWLFd1hTMSeprCkooh+VbV2NpsGftE21g2
*/
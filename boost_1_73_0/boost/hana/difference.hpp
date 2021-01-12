/*!
@file
Defines `boost::hana::difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DIFFERENCE_HPP
#define BOOST_HANA_DIFFERENCE_HPP

#include <boost/hana/fwd/difference.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/erase_key.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto difference_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Difference = BOOST_HANA_DISPATCH_IF(difference_impl<S>,
            true
        );

        return Difference::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct difference_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DIFFERENCE_HPP

/* difference.hpp
+9SrNdJp34is59msOb6sZ9isw+9lJFr7FqAYgd4a+w4GaF92PtB7YMZIXAOxrWwIzjwtqwnh7JYtaRLVoaQYJim6HSFVF8TlshPXaPF778oA6mPC5WBuIULkhsdpcCVu2StjC3HBAPZWxipGQzO+6VsocBJqlrxodyQOtrUsBXgV7ntJmBmqXFKBubiDd/Sd8Qo0vUseSgL3VWEIOiC43VnlrmV2LBz72loWsYJyr4K2ekSw
*/
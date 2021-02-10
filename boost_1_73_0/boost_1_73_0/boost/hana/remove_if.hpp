/*!
@file
Defines `boost::hana::remove_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_IF_HPP
#define BOOST_HANA_REMOVE_IF_HPP

#include <boost/hana/fwd/remove_if.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto remove_if_t::operator()(Xs&& xs, Pred&& pred) const {
        using M = typename hana::tag_of<Xs>::type;
        using RemoveIf = BOOST_HANA_DISPATCH_IF(remove_if_impl<M>,
            hana::MonadPlus<M>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::MonadPlus<M>::value,
            "hana::remove_if(xs, predicate) requires 'xs' to be a MonadPlus");
        #endif

        return RemoveIf::apply(static_cast<Xs&&>(xs),
                               static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename M, bool condition>
    struct remove_if_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::filter(static_cast<Xs&&>(xs),
                        hana::compose(hana::not_, static_cast<Pred&&>(pred)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_IF_HPP

/* remove_if.hpp
a/FmnSz8pRzekV0E52KCbGJm7FUwkbMATbHeQskA8zWGjuPzBjV0LfrMgzvsrCm6Y2Q0Yz+CJxZSMFQzFYEd7hcKkkxY4tf2RoYkXSJiZ6HXdAt/5kiAP9nKU/rzkg5MoPi3TjsX0BHDinH5YohaiRck7+1ZzrQH7FfT+TMHV3fjtz8xltA3vx98YxeoinSrvhFzlaA5Hq8AWomW5JBHldBe/bHuM2PNnBaFHryXjFdU7tz1P9IoCeoiTipdSaGFYmz+WchIYIqRWvxHSiRBUrIGcM40OmSQJU00bWPKEiWFxch5TDHqOX6KmyOe5V9hsA/kRqG24eVjXW69u9mTYSUFNzD4XPF2zUcz0ssu9VheZ3zjl5imKksHSzS/epCZERMDchXPZ9fp/KmMPzdb2yYlpU/VhB9nnS1vm7xvEp4H5HCw9ekoVRZTiKcm2ajlyA4+0prlEkeHlNP8MarCO09gI+sdO10oTopRJ9C1l1Mua5uP7o8xHRTkNr/sq9LHMIllUTajCem0vKEKteEcIsDyjGSfRHkf7W6WHarWTSOHnvqyQ/LiUqkUHOnOYk44tZ3PKsVI3YOC2P+5I88c+01J2kA5es06WoYnEdqmqI+51arIppIIPxpBhFRCcgnyuTEmEN5xf3rwdH5e
*/
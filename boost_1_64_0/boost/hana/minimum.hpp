/*!
@file
Defines `boost::hana::minimum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MINIMUM_HPP
#define BOOST_HANA_MINIMUM_HPP

#include <boost/hana/fwd/minimum.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/fold_left.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr decltype(auto) minimum_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Minimum = BOOST_HANA_DISPATCH_IF(minimum_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::minimum(xs) requires 'xs' to be Foldable");
    #endif

        return Minimum::apply(static_cast<Xs&&>(xs));
    }

    template <typename Xs, typename Predicate>
    constexpr decltype(auto) minimum_t::operator()(Xs&& xs, Predicate&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Minimum = BOOST_HANA_DISPATCH_IF(minimum_pred_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::minimum(xs, predicate) requires 'xs' to be Foldable");
    #endif

        return Minimum::apply(static_cast<Xs&&>(xs),
                              static_cast<Predicate&&>(pred));
    }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // minimum (with a custom predicate)
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename Pred>
        struct min_by {
            Pred pred;

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const {
                auto result = (*pred)(x, y);
                return hana::if_(result, static_cast<X&&>(x),
                                         static_cast<Y&&>(y));
            }
        };
    }

    template <typename T, bool condition>
    struct minimum_pred_impl<T, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr decltype(auto) apply(Xs&& xs, Pred const& pred) {
            // We use a pointer instead of a reference to avoid a Clang ICE.
            return hana::fold_left(static_cast<Xs&&>(xs),
                detail::min_by<decltype(&pred)>{&pred}
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // minimum (without a custom predicate)
    //////////////////////////////////////////////////////////////////////////
    template <typename T, bool condition>
    struct minimum_impl<T, when<condition>> : default_ {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs)
        { return hana::minimum(static_cast<Xs&&>(xs), hana::less); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MINIMUM_HPP

/* minimum.hpp
TIFDs4NmWyA4Fa60utdeowSCW64MjD2QWK5cMhXV4hOz6sEdqmuLrsePfLtHTRvJmkS2664XVj/DKXjbg4Zfah6FHxaNt9dTsAGO9L4AWk96KvBpwCUmKEoLHXzTheJty0KCZqJicTh+CwfSg6fJLlIrXVxxZYqKbkiuFLsEZezlf8JNu/J5vqle3Wn4nJ9Vbrf4hx59fw0JL4ECnVY6FtY5BZNyvVH0yXNX1VzvGgAHn4gGp1uN4DqvCOxx8Xp44foWtVAx+OkjUwvxyFv7D7hNGc1aXL+fjMa+mOG1eicyRJBn3VgT90aoFXZdCcP+e0HmOKvDlynbzsr4vexBetsrooSDSD7DLkLBhs2dSedDjCJ7OXe/uwHyF/S6u6RTKtMAEHMQ/2LvEEYjgH/sMbmSIjf2Rcpc6k3cIsi2xgoNVocu9K6YK3NDcBpXApN49w6BM5w9Bcon6rUFoJbi6tE0+S+lTR6u7ToKabAjg0obpjOoB1f1CMrqSHvJVwhiY/PWhvkSmlhJxWLUqzv9f/+1mtEwFPBimCO6joH3RvZ5wGgE1HGAo5Awyg==
*/
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
19G22Af5uCR4ShmSFglbnY9Lc57zcWNPBe2E5/3g4QO8ucb3gZeNn4sBB3K5h+GIbZ2fk+OddDPfwc2aqIZv281XGLihrxKkgXfl/mUs7isM3LlfpFhjfMCryc5g7/Ehbg9g3xzaWOStpZOEmffxG5zf05hWeN/Ks5stQpt3n+btmMA+La2C2AVuWj/1PoK3YdpD8pcyskO5Lxjbv88Z/YsStKMCPyR8u38/5m2eKhEoH9mYuAJ2qo33V4Y+8LIUCgHZTVYG2jZqYC8ZOtW1wQkPAIA9sF9tERVs5yiHzavQQ3KEUsBO7J+cNmF3AZa1oUqR1g5TdIu1QcPuNvAmKYQuSyGb49qw14CNsCf3EWoM2DFt2GfAZnhEE8rbEbAH9x9u+VPuYsCGeYqLCFklYGF9HjJh9xuwQYJRc2zZhsOHpvebsjbNYaeRTM7PEXsi+zZ1EPq2PUciwDP9LF72K3Ai2l0Gl/tKQTP4EwZ8BMWRwrVC8NA3bfhVA97LSqQk92KCh1OgDX/GgM8TG3FklQKHamq3/xkGPFQ5Lh/GGVXAhr2N/6UGPKLe4JnNfYLH5rsN/yazv6HrR3FA/KHNtAH/XgMeKQqQLyKg9mBjPAL/aRO+xNKdZqmCnx6B/4YBn1UJLo0GPsFDdNrwF01+pplbImqM4LEZacNfMvubeT583TQAS2P6u+uY0f4KngP4XQl+TH/3mvCegx7kGcGP6e9dDHhxoBWVbkDwY/o7/W/OrgM2rqYIH/2n995C7+AkduJQ95V9vWH7p8Ph2OfYxOXwnUPoCNG7EEI0AUIIAaIJEAKEEEIIECB670I0IUAIkCgCxLf7dufNvrtAgJ8k9tvZmS2zu7OzUxz4MsmDNCorAz+nvwmHX06hbS4grSr4bcb+jP8d+KIqkiyVsYG37M/534FvoKmHPqnR8Iz9Gf878NDtS4gAqYGfx/8OvPSCOIMAoOEZ+zP+d+D9KK+wAYcanrE/43+3v2npyTRvx4exP+N/Bz4vC8xW3raHsT/jfxfeqwvsV5WBt+zA+d+BT3zl+ZG37Tfs755jv3bHJ4qrRBYavON+4n23r1Hlqc1EAzPWZ7z/SKftvrJDrKoWfl5fb+XCV02RY/Mx8HP6ek8HXkf0rKughZ/X12UHHiq5ArtzCz7T14TDFiKrU+WXVmvoi0yRcBsra/yofY+ALGTfI6gsuaqSK4YqNs4QplJTbYNg5btBVxaPpgXkB/2ao5aGhfk8g2lGo/MVVE6bDa4IgLE0PspgVndHo7GOX2Z0kaxMgr4xkaQ2fJeVt8/3a9vqssvb8FMGs2YseSyYfYf9OsUx1DHs9uz3f/xCf68QXGf/xNl98qm5sxODcHcfn6YUQ/DH9k0XOs1ErigQfD605Zu9chPI6NDivuovqVzrJPBp3ZZdgTIeH1CV2XfQD3/Plsl9rWpAcEGbj8vSvsEvXRgboNDiuFm/XAcg1EgI5jZdG0aXonOMwcyjc3dWfik69wUMHycKHsVgTsyDMY+/1g/sGb3xpkBO4/VN9eio3iEsvuU5+DRLYNosTzyUYPDshem230P2HY8IK3bOMvpOd2PbfthL8HiOrQ7KxHPctDBNWz8Yxiv1ldYR7Fwb15DiHFkYPFeqMUJ0wyHiCcGtS+OiXGrNjzo4M07DO1gcvExnaTt3eHA07mIk/bJf3hpzmJhL5yzcWQ6HYEXKyukI5jpKE6TgbL/u/2MGZ4N8KGRsLW0bXGEytGgA0MVN3Lflqx7ZDdiyKSszthPnb2HLdOzKFZToQdixbX/aL+33CfO32xtNtw82Byx+3XMsnHblPj6s8SwP7z/i/xf80sYsBEzTGgfkaLil/zJT37Q=
*/
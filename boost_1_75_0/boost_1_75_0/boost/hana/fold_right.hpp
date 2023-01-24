/*!
@file
Defines `boost::hana::fold_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FOLD_RIGHT_HPP
#define BOOST_HANA_FOLD_RIGHT_HPP

#include <boost/hana/fwd/fold_right.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/variadic/foldr1.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/fwd/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename State, typename F>
    constexpr decltype(auto) fold_right_t::operator()(Xs&& xs, State&& state, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using FoldRight = BOOST_HANA_DISPATCH_IF(fold_right_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::fold_right(xs, state, f) requires 'xs' to be Foldable");
    #endif

        return FoldRight::apply(static_cast<Xs&&>(xs),
                                static_cast<State&&>(state),
                                static_cast<F&&>(f));
    }

    template <typename Xs, typename F>
    constexpr decltype(auto) fold_right_t::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using FoldRight = BOOST_HANA_DISPATCH_IF(fold_right_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::fold_right(xs, f) requires 'xs' to be Foldable");
    #endif

        return FoldRight::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    namespace detail {
        template <typename F, typename State>
        struct variadic_foldr {
            F& f;
            State& state;
            template <typename ...T>
            constexpr decltype(auto) operator()(T&& ...t) const {
                return detail::variadic::foldr(
                    static_cast<F&&>(f),
                    static_cast<State&&>(state),
                    static_cast<T&&>(t)...
                );
            }
        };
    }

    template <typename T, bool condition>
    struct fold_right_impl<T, when<condition>> : default_ {
        // with state
        template <typename Xs, typename S, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, S&& s, F&& f) {
            return hana::unpack(static_cast<Xs&&>(xs),
                detail::variadic_foldr<F, S>{f, s}
            );
        }

        // without state
        template <typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            return hana::unpack(static_cast<Xs&&>(xs),
                hana::partial(
                    detail::variadic::foldr1,
                    static_cast<F&&>(f)
                )
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FOLD_RIGHT_HPP

/* fold_right.hpp
ES4mgIE77Dqs97GVWcoAkV9Eu4LNGJOhYh4pe+/zGlbioOY1xnMhIZYEkewe0Zc9DIOPmHSmJN8LyYVMSEXQhPdtTyMQXHAkcSKLXf40ugdvEDL1I0IivX81gffmximYXDUR4NOcfLi2iX9QyuVnRWgUDf3T1YD/NVsAeSWiLu7uYt+Nq3osD//aptbPAGDFmnbRy58fCHsbuHwL4BwpJPzzj9v60Fb3hAIQjaTQOCSOwh/ajaflHOQaA5iN7PaqmcsIDtCPZRDvptonYwXewGnHZLqEkz21UjKWEoyMI4Ujt0UnWDOKc5ilR4itBQS3d4lzzgNQPrNq0obLpvb2gxGldrT2yY66gncN3/1FSVM40A4uX0n1NnSgp8AOOLK8x1bHFHtcFMITxtUVc7U86FiP1LIgfG19fYKCzTKwuufZMqjiQ9r3MW6ORIfBHHQY4Bmb7pUeBqn/jG9CsSMu5kCvqK34y79lnDXpccsxZ6z15pLNIN6lltkLXwHNFy50JfvD3J0o56B3D8gt/Y1id2G8q3UUvMR1OIe7HBxxN0QaSwm7GtZ6e3Lmb7b2gmz3z/tmztHMXp7GX1Qr55wF5kZz94A5XAme4fBOgvutDpQbEIb1THCG143Jhl92GaLc+5upZlHZgwUoA5DDoM6hAmrvbFHcI/2IrnXPqFHN7Y9gBwfY3m4Q0tWzeROrddy0tBdf+fgSUu5sR0Xc
*/
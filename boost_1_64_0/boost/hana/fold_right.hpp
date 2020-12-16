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
N4Ee6Ugn3WOex/CbneXhqfzkQfjH/sns0J9N89x9+K+WPrdev6jOushx+uE38/Gz5Su/nHMsPTIYT5+lbujDWnFYOIbP6Gr960z+UlzKHGt30ZfTrevNFKcGODA03Peqr7+Tv+hAV8jf4q746Tj7nyvhd7n1DH2k7bPpnlF8+QeO4+Dto3zTX56/RP9FnRfg0/r/0hV9YtYT6Of2+O93/K9us0K/sAIvXAnPh6mX810n9GHWXSqX03ctzPMb6q4c3ndPtK/OczUGx+Kb9bnD70kq5stHuf9n+L8d/X4Yf1gdta/cuhm/03iPun9SPE+JGFf4/0ET9cPxZPh94Pcn8Od0w2S+1jpb1qv4c4y6PdT8vBHB43Awpt7ot1q+rW13fbwf4a79h6n4p+frfMNX4nwTnXc5f3SZ8T1LVzaqq2PV07Xy8X39sKflxQG4FX4vZ2/xkCfL8Eem/kbKqfr6O+1jecT+guOD4+wD6uEX9b09ar3a5y7l4/bih+7Wm9vzy0P1eV1nkbgsLKTnHtRX+QMf5STo00SC43rxeIjeCb8H8lQ8G+J4W/US/l5VlfkUl+34ea7nzQn329yl7z6b3u2MZ4/1XKf7HN4oOki+fg5vvsPfVfj3C/zXki93TCltZl8OPuBDa46gv+sjeCg45veX542uF+5bg+959EQDfs5PNh/4rK5W/X1lneFr4z8n/F1h+Pt5mId0wRfh903yjxmeN8L38hvRj+VFlnFF6RfXLzgWDrSyntERXrypjgpdp5FOKnWf280rnZ4zA97yCTN2q+Pm8usxdYxfppyIHzPUVYP6uIseeEBepaiTsfqn8CTGT8Zq4Hk38z1P/+RUvL5CHd8IBx7F+4n8xgfiTge2nUX347URdfhTPGoXwsOOcOt1feAF5pNfLxmIf6fivRbWNSfqj+G76bfRVf+G93R+48Xy50I+fWNi8L75y2kHh9o5PweOPQW/b7Be0x6vZogHXVA/TL1Uie8T+oIXeF9/N208HLkKD92pL7FRPu0JjsUFeO44OHweXs8LjqXmZ90jeHAHXAvx/e7gWJJNT7cWpwfDfdH8ep7r85Ept9IbQ6wX9aHX8H7Re+pL32H7/RE+Vh3hiRlnw/1u4e/T6W8/Y1y1YR+ejylSp/Mj9v1E4ZS+zDA+dAdfPpxuod/mdlRH/s5/Q56NUEfi0W1kM/ta8P1BwbEIrkWPsX9iaiQ4yq+pr9H9O40//L35K9VDsb9PUH/wN4VfnDULv8/nG/iFfi+rv+PkFR9V35u/1u9JScCv8q/lNHorAw88y7e0hc9V8n2GeRuur/Q+3XCqeT2Szq8Tlyv0fZfAvb/okE3y+m95fJ0+wHI8EMfPldbL6Obt6fBjHTxZ7f5pifp6/PVFUfgND16hF59QL5v14ffLt5eNfxX8+wiP8ck1X3lu9ZH8vHxrjn8vM/7SxOD5xGXaVHWFtwv0jctf5Qd+oadfwSMh/l1snAvpAPqn9hD3U+e1d4uPvmeWvvPc6epSXldVWdewD3/6OXjlNHE+RF8SHy1PivC58vY8vHgTv/6p9ey98pn+zf2O3nmAfp4oT/mfqRX46mv66QG8Wcf/ZcGb7/mZe83fUvpvkD7TPe43JjiuDH/H/lfrEOdajzRPs+4L/98RHb2Pn28HRw6TdwOt8x5uHFfqWwyHE/Bqbg91dQE8SKTHwt9Zmmc940HxVEdNO+k/+1JbloizfRTRnvzmGLz3ozjZVzLPPsEtbT2HeVsoP+tXydNleEd+Tm1Qt3RtFr0z/Uufb3KdZnTeOeKaG+6bpxte1NdVB2355rxe+pNwb9lAfQr9suLwe31b4+Vc9ThPPRbT4VdE1Yd8pcs=
*/
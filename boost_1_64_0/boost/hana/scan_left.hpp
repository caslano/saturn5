/*!
@file
Defines `boost::hana::scan_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SCAN_LEFT_HPP
#define BOOST_HANA_SCAN_LEFT_HPP

#include <boost/hana/fwd/scan_left.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/prepend.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr auto scan_left_t::operator()(Xs&& xs, F const& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using ScanLeft = BOOST_HANA_DISPATCH_IF(scan_left_impl<S>,
            hana::Sequence<S>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::scan_left(xs, f) requires 'xs' to be a Sequence");
#endif

        return ScanLeft::apply(static_cast<Xs&&>(xs), f);
    }

    template <typename Xs, typename State, typename F>
    constexpr auto scan_left_t::operator()(Xs&& xs, State&& state, F const& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using ScanLeft = BOOST_HANA_DISPATCH_IF(scan_left_impl<S>,
            hana::Sequence<S>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::scan_left(xs, state, f) requires 'xs' to be a Sequence");
#endif

        return ScanLeft::apply(static_cast<Xs&&>(xs),
                               static_cast<State&&>(state), f);
    }
    //! @endcond

    template <typename S, bool condition>
    struct scan_left_impl<S, when<condition>> : default_ {
        // Without initial state
        template <typename Xs, typename F, std::size_t n1, std::size_t n2, std::size_t ...ns>
        static constexpr auto
        apply1_impl(Xs&& xs, F const& f, std::index_sequence<n1, n2, ns...>) {
            static_assert(n1 == 0, "logic error in Boost.Hana: file a bug report");

            // Use scan_left with the first element as an initial state.
            return scan_left_impl::apply_impl(
                static_cast<Xs&&>(xs),
                hana::at_c<0>(static_cast<Xs&&>(xs)),
                f, std::index_sequence<n2, ns...>{}
            );
        }

        template <typename Xs, typename F, std::size_t n>
        static constexpr auto apply1_impl(Xs&& xs, F const&, std::index_sequence<n>) {
            return hana::make<S>(hana::at_c<n>(static_cast<Xs&&>(xs)));
        }

        template <typename Xs, typename F>
        static constexpr auto apply1_impl(Xs&&, F const&, std::index_sequence<>) {
            return hana::empty<S>();
        }

        template <typename Xs, typename F>
        static constexpr auto apply(Xs&& xs, F const& f) {
            constexpr std::size_t Len = decltype(hana::length(xs))::value;
            return scan_left_impl::apply1_impl(static_cast<Xs&&>(xs),
                                               f, std::make_index_sequence<Len>{});
        }


        // With initial state
        template <typename Xs, typename State, typename F,
                  std::size_t n1, std::size_t n2, std::size_t ...ns>
        static constexpr auto
        apply_impl(Xs&& xs, State&& state, F const& f,
                   std::index_sequence<n1, n2, ns...>)
        {
            auto rest = scan_left_impl::apply_impl(
                                static_cast<Xs&&>(xs),
                                f(state, hana::at_c<n1>(static_cast<Xs&&>(xs))),
                                f, std::index_sequence<n2, ns...>{});
            return hana::prepend(std::move(rest), static_cast<State&&>(state));
        }

        template <typename Xs, typename State, typename F, std::size_t n>
        static constexpr auto
        apply_impl(Xs&& xs, State&& state, F const& f, std::index_sequence<n>) {
            auto new_state = f(state, hana::at_c<n>(static_cast<Xs&&>(xs)));
            return hana::make<S>(static_cast<State&&>(state), std::move(new_state));
        }

        template <typename Xs, typename State, typename F>
        static constexpr auto
        apply_impl(Xs&&, State&& state, F const&, std::index_sequence<>) {
            return hana::make<S>(static_cast<State&&>(state));
        }

        template <typename Xs, typename State, typename F>
        static constexpr auto apply(Xs&& xs, State&& state, F const& f) {
            constexpr std::size_t Len = decltype(hana::length(xs))::value;
            return scan_left_impl::apply_impl(static_cast<Xs&&>(xs),
                                              static_cast<State&&>(state),
                                              f, std::make_index_sequence<Len>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SCAN_LEFT_HPP

/* scan_left.hpp
TQB7GZ3jUbdBaRd9NI6uU5Il1+ECdRZZ/dxx17jWMG/JAxv0aN1T2qNVV1luYV4+ZHsyZy1nYyAamA0G5iVENllcPDpenxmt7njLm6r3tHddSrTXSfMS4/sEcaq7U1pflIdhtq+KxjacndoENeXiqWPpUSDRPy+nl1bxWnVlpJ8ACF7uh/E2St95O08H85YzQMwDE4nFJQhScTqhAOO9Oi9T9VI42KZimbstzivz57yM8YZfvHZDGWgVLYP+vu/K7bYrYXVvawmn5zmAAt5YjS0EVL9Yclr28Kissqrt297mZbHWrOzSqGxX1LJtrCZloZfz63Wjsq7vqraXPC87v96zo7Il71pdVQ0pCyM1v96LR2W5q/3hJfKytF6yL9OyR52Rpuqr2vtGo8/PIu7LGa3VXeVM23ja8zO076K0x6u+b7SF+b97+ui97gb4qtm8/RqlvchwUxecc883a/PdMG5/Ru+0aTSviki/to70af4tvDubf7I1XvNGCuCoTm11DtEyPVOO17JqKyxz11iI9uMwLXNRU5Z140rliwDxGezHLVMdt83bpWSrYKL2WActlcos5e2SpVC9E4a0Cwthu+qsXb3pSl60sZrtOe1yebtKWwurKoV10FKpzIPzdhkrqkIL2iwsg+26mJZZ0k5yBQcnA6PGVfrhUZ58Zkbvbae6wvSBHntN6V+a0dtKyNoVKtJvz9K/L6PnbWcKKTWbwFE0tz2fy+ibCqSJ2kVybA6hv5DRS2F6XnV1KDC3PX/OvlvrTA1L068huodQefs9lF53ICoY2Xr6+e25fEbfebt76fhAv03ocU1QesM4bBad5MVQACLE0s0Jff1GZWqpmrp0oQxsBFkZxDqmZY5rbWVR9nDsnZl2G2nvkdG2RsqmswpoY5cprchobdlwDqsHaEl30a+D0t6trIzoe9HCjjrZO0YajWP54IyeG2hx0xSJHpuN9DsZvW5LCbIasp+dCxdn9JLXtTOliwWw+WTuU/ql0hlYXZozMNw8twpXD/y2iPdF6cuWNWUn6lprZjYmMQDlBK1cR1yOp/WQ8SiAR10KLSWLlgN3y8udQ9sBWg7mk7NNXxa1IXWfA9kR3hPQCGHchMtgrNP35jbTomjK1tUW24AWuTgGx9DWkpblnMHO2kqu5L9rB7JjUz8r9t6x3as0fq3EGz0ZhxwbyGXlNNMK5FHdt6T+yGHUfRAfUt1nR/3XIPmC9ItVj7tfpvmVlYMqpfDW3mJO3WMWZ++Z5lzGo2Ku0KXWRcNiRIi7wcVpzgco0K82K29Z2TWVLNse2zCKLUE45fIE5bNUyrpVfe9nwATs8qfXig20lR/1vXRaCGc4qTeVhefc9YDLNFRJYlMTG8Uz8BIOiieR8pYuPc17+ARcsCAv6arfGmwQg+2r9fG8AN5xF8zieLL1fhfNB4uLQLO2fmr/IQuTRPOBC8RPPrxhDIbd2wvT+Gwfy2hMDU8Rj6R42Z8Z5Udfecz/0jh/A9QH0JPUhm+M8yHII0CxQewybCdgpI9oQLXir7yQBTqzqHu+kGzbuXY1IJ2A6S7Ae65Mgufawnbi9WOk68SIBjEsfnkhxwgBxbF/FYrwJFNev51Pd2SBxK/7M9qKBhYxjOCAqbkKbi9AsoZ2gdcbMDd3VvBOt4/vHNeleaBegrw0xu9rIS/GHtrfgC+9d3Z7DXA2b5LKXieUXYdh234UoUAsz2uEd4+z2zvAAJ7hJvD9rpF08w/1OvWgTt9Be/T3ZTJb46qaGyVY+kLc9irZu/dpj6RluGRt10oQM/R/Z2c/ZFD5gFF+HeNKyroHKSqygAAdWym+AWLnOyiT2b5pENTq0p9uYJbwEILFlxk=
*/
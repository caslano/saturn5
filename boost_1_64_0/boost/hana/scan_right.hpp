/*!
@file
Defines `boost::hana::scan_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SCAN_RIGHT_HPP
#define BOOST_HANA_SCAN_RIGHT_HPP

#include <boost/hana/fwd/scan_right.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/prepend.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr auto scan_right_t::operator()(Xs&& xs, F const& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using ScanRight = BOOST_HANA_DISPATCH_IF(scan_right_impl<S>,
            hana::Sequence<S>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::scan_right(xs, f) requires 'xs' to be a Sequence");
#endif

        return ScanRight::apply(static_cast<Xs&&>(xs), f);
    }

    template <typename Xs, typename State, typename F>
    constexpr auto scan_right_t::operator()(Xs&& xs, State&& state, F const& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using ScanRight = BOOST_HANA_DISPATCH_IF(scan_right_impl<S>,
            hana::Sequence<S>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::scan_right(xs, state, f) requires 'xs' to be a Sequence");
#endif

        return ScanRight::apply(static_cast<Xs&&>(xs),
                                static_cast<State&&>(state), f);
    }
    //! @endcond

    template <typename S, bool condition>
    struct scan_right_impl<S, when<condition>> : default_ {
        // Without initial state
        template <typename Xs, typename F, std::size_t n1, std::size_t n2, std::size_t ...ns>
        static constexpr auto
        apply1_impl(Xs&& xs, F const& f, std::index_sequence<n1, n2, ns...>) {
            auto rest = scan_right_impl::apply1_impl(static_cast<Xs&&>(xs),
                                                     f, std::index_sequence<n2, ns...>{});
            auto element = f(hana::at_c<n1>(static_cast<Xs&&>(xs)), hana::front(rest));
            return hana::prepend(std::move(rest), std::move(element));
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
            return scan_right_impl::apply1_impl(static_cast<Xs&&>(xs),
                                                f, std::make_index_sequence<Len>{});
        }


        // With initial state
        template <typename Xs, typename State, typename F,
                  std::size_t n1, std::size_t n2, std::size_t ...ns>
        static constexpr auto
        apply_impl(Xs&& xs, State&& state, F const& f,
                   std::index_sequence<n1, n2, ns...>)
        {
            auto rest = scan_right_impl::apply_impl(static_cast<Xs&&>(xs),
                                                    static_cast<State&&>(state),
                                                    f, std::index_sequence<n2, ns...>{});
            auto element = f(hana::at_c<n1>(static_cast<Xs&&>(xs)), hana::front(rest));
            return hana::prepend(std::move(rest), std::move(element));
        }

        template <typename Xs, typename State, typename F, std::size_t n>
        static constexpr auto
        apply_impl(Xs&& xs, State&& state, F const& f, std::index_sequence<n>) {
            auto element = f(hana::at_c<n>(static_cast<Xs&&>(xs)), state);
            return hana::make<S>(std::move(element), static_cast<State&&>(state));
        }

        template <typename Xs, typename State, typename F>
        static constexpr auto
        apply_impl(Xs&&, State&& state, F const&, std::index_sequence<>) {
            return hana::make<S>(static_cast<State&&>(state));
        }

        template <typename Xs, typename State, typename F>
        static constexpr auto apply(Xs&& xs, State&& state, F const& f) {
            constexpr std::size_t Len = decltype(hana::length(xs))::value;
            return scan_right_impl::apply_impl(static_cast<Xs&&>(xs),
                                               static_cast<State&&>(state),
                                               f, std::make_index_sequence<Len>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SCAN_RIGHT_HPP

/* scan_right.hpp
1S/eOsl5ltrst51oe+U9Be4y8h0+m9WjGG+bttG2xgESsrxPtdJJeD59QDx/Ux0X07KLRktju75hSf1g0C4y/wZKgFgimhKrUNqdiP1fRn9zKJNhyNV152zRMk8MZxTg90Z7JnT5pDGnd/D+T/ncTTnnlLINszD0ULX370Q/i/0kQ30o75fpXAejxygx2oF9bNTOqpAFVyBxzZrN6a3tFOEaWLks9vMUu3E0Vl3Be1NUbD1FLhy966O/ej7HWte2Vd2V0X0aljK8ZawRh+l7pvXx/kxG01Zz26ARARTofSGsFO9Rqd7r0fKGNXUnhGwbahpBC+K8uy0tVwrGrbW8dmAXdPzEATIYw9gftKyUIINVvQKNN5TtkuwixjJU+AKT9RBqGeYwYshTXsKAPARSZM09L07lkDGL8Emrf3F2HbC17EQ0VNF7ByGaACFE+RD4CATeddm1d9c2SahChJAEEghJyM2j99577733DgKEEEIIECDRexFNgBAgQAghxNhrzx3vvaHp67/37npmXNZrj8czZ6pgY4fMNPN9+XNU3qpsfIg2HT2XYak4P+sDW4gfS+nP8+3QyL6vofb5WFdoU6W0t2oaJ9qG1wym1e0WaL9BaW/dWdtb2zj24HNov59/xz+gtLfUuuKd6luWDecs0/2kqH8QzgrVsPs+PNtG1/IcpnTcM81N2yvVseRGhkMKY3h+nB/hL9FHdIDkYhpusOgaerXPFmeVznXa1IrZrQctzjLMB0J56ioACXMeFsHbVmAwmkW3tSkzsPUY513ElTSdc74fHJMPG51EUbdGO2sRO9NIbpSvDavP7R+AE+kEc7Romwp6eGVUV0HjNmAQiFNRNc0T8HDUg4sxEVoaw1sDEpwWS/q1n8fytIitaRrvBm8HNi5Rh7skVdwcx+VxRXtr5nRlfG091Bb8vFbH7CQLtVYYu1rwN6w1qmlVxQQqnUTTJflOc5vfR/kHZquwLuqatbJa26hltbGOPDO0z1GeW6tq0JpXIXryPKS9Da75BS3vXNUNTc/W+Ooi7Zcp7aqRWmkl2Drf8Iu03yho+8bIQVnNYO/BTiLtDwrauh6apoGhuif0E2lDTNhDr/lv/ARi+VI/gZXEe5afAPJSP4GybImfAMo9008AeRf9BJD3LD8B5KV+AmW9Z/kJIO+inwDynukngLzUT6Cs9yw/ASw/208Ayh92zaV+Asi73E8Ay5f7CWB56Scwrfvh11zqJxDLPn4N6icwHUvqJzAto34C0/6cGcOI5cvxEFD2Mux6LKM5K8oymrtu2qYzc3Fi+Rk5WVH244ZQHq8/sRTnnA1lJ7DJLda7F30bx6vQZX1lbix/8LLvYD2WLf0OrnOXVEabS8s3Q3m+K11s1+UeFMrz9eiSOfnIWB6vQ5fKf3QoT1egS9p+ucfE8gdRdlxzfhjK4pXoQtn7fjSWPXBre6HsDz+OZSfzKUe++5+GstPZsrY+71ehLAH+LSn/2m9T+QxKlsj+zO9C+cPgrIyF0U/1kVDGbhnKQj6TseAqwHOBy5V3oBkj5NHXzP6p3A1DZcU6tCE8R7wXoRu5Toux/MK0PKKe6o12WMfyGMOcbAzL+C9Kyin/NUI5xjX7jpRhmy+W6l4PEdJijF9+SdzF1MZm0CJC/9KzC4RnY96Hg0BxmfT8guH5g3aQ90LwO7vQXgZ8cf8I+0m11kSsm/Pg96vh7L/Jj052+ckpRFGs726DkWp9d+tke28dToAcktGAmUKN407yHV/4AgHjJZCow/rhQWWcl30uloWT++Zs79zpDniIYvz0TS8YysDwso2+rphz+aqFv+GN0D/4qvjeget4Xs8/yrLw6RMfYSgjPoU=
*/
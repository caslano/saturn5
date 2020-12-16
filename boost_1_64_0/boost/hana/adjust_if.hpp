/*!
@file
Defines `boost::hana::adjust_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ADJUST_IF_HPP
#define BOOST_HANA_ADJUST_IF_HPP

#include <boost/hana/fwd/adjust_if.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred, typename F>
    constexpr auto adjust_if_t::operator()(Xs&& xs, Pred const& pred, F const& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using AdjustIf = BOOST_HANA_DISPATCH_IF(adjust_if_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::adjust_if(xs, pred, f) requires 'xs' to be a Functor");
    #endif

        return AdjustIf::apply(static_cast<Xs&&>(xs), pred, f);
    }
    //! @endcond

    namespace detail {
        template <typename Pred, typename F>
        struct apply_if {
            Pred const& pred;
            F const& f;

            template <typename X>
            constexpr decltype(auto) helper(bool cond, X&& x) const
            { return cond ? f(static_cast<X&&>(x)) : static_cast<X&&>(x); }

            template <typename X>
            constexpr decltype(auto) helper(hana::true_, X&& x) const
            { return f(static_cast<X&&>(x)); }

            template <typename X>
            constexpr decltype(auto) helper(hana::false_, X&& x) const
            { return static_cast<X&&>(x); }


            template <typename X>
            constexpr decltype(auto) operator()(X&& x) const {
                auto cond = hana::if_(pred(x), hana::true_c, hana::false_c);
                return this->helper(cond, static_cast<X&&>(x));
            }
        };
    }

    template <typename Fun, bool condition>
    struct adjust_if_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Pred, typename F>
        static constexpr auto apply(Xs&& xs, Pred const& pred, F const& f) {
            return hana::transform(static_cast<Xs&&>(xs),
                                   detail::apply_if<Pred, F>{pred, f});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ADJUST_IF_HPP

/* adjust_if.hpp
2wwMRuTUBKvdLQnLqpBLttPC1p2Fv53KmpGkV5r5+P8JGOjTrj3ORUsWyLqA5bc1/bYAPZz0YnMu0vk4zDgzUdejDMOWjcMkjtnYZ/8ozFjcacA7N0T3rsIXVsPUOPZvLsHvpTDLbDuuWy1v4P4Kb3/AfKjXH/D7XP00ukr+VcKkwlxqvfsy0c5n+xU1+834y+B7JcwqmMthVjdgjc1ZvmPuijoM5v3dQGBHZHLfSXa88opfjDf4tHyFv7e2u7mkk82Nhhnz/T3KU/XXQ2XybNKp5loj2fftvRDsZpIvzbxK3q0v1bC6xnx3jzqC8nRSmTmddKZ5s8wbfECZWF5ZuXAJm3m2yMUN5DsIbWSEUQXbx4xMPef9Y7olRe9KaxHdr1pZVaLypITuceZio5meyaxF7tfBrIG5UurWVfL7atseBnwNqHeRMR/S4bpLMM/nDcBZPm8AFvi8AVjqsq//FuQHUofaSN1tBtML+RC+kHWImZHPmsQrAosrl1VEzvRa+UX90a5Llr82KgvXNaBOW2NQhId0MjzX/YUHvh1lvgImU74nFbybo2msqcIjlUiTJcpOJcvgx32H4TbSpZgVNZ1ySMv/e3SfboxEemQPCeXOejEXN0AfpZ5VT664z8BedXfUQw+YpjAdYB5FWtIu4jdCeswrr6wu0fMEONfjml/qQL7m8p2Wvwzt1zcglmsbkFarLBAH0oo4pI8ZzPBwh0kLd7qHb42d7lxNd2UYkym+6Z7qSXdujHRf90+ke4FPutffo+d89MxxG/CErXRzS079dOv7xOSrMWbYOjv82vu7Z6fTj95nPVHdW2rdu4b0UmOWLWfxZx2tsecu91jhkoZGRDpBx0qbENdmmBsEb4TZAHPTP5hvlv6Pb6BdteTl15KXbT15efDeaIBrJS9XSF6mTbbyktt1fPOyC/lKjQl2XsLvKfMS7u687E76UmOSf14y3IvJly00cp90gu7N9OblBphb/sX5eNNkzUeXHlHwnWiAzqWCc8CzNZqPkVfj8nGSPL+wekXFPBnvD6UM1nGS8AY4H4z1wwacLUsn39Co7GV6ToA+gkS8AUQv/cAdv3jvx3371v142vKy67Z9jHMzrSP22c+u2vhlx1k/XLd8wuNrn37sAL8J9sdGTW69pNv1G5/JGn5947e/+sgw7mkXsQ/8KL24aHHve25/5Lszv+pwYB7f8IL9+RfNyz4660SvxuHWb19x9skf4RviI/aXZdy2b9/i7G8cvOfS77/dfc4g3PUUF7H/5Q1HfzKqpOzuuk8vK/puh4cScNYjO2Lf5rV5KeWXTLzyrcZrw52656FOHsiK2D8xctKJL4cNeuWWD9/58Txz3s8x1iL//bfNn7or/g9v/vA7Xb6+/eb1yPtOCRH7VRtnhu8d8FbZjsfenfjIfZehw92ZGrF/Ppi5J3/gwOfOTeg5dHHbsUj7OuZD3773T//d4S+yph5Z2Xrqt1u/CBkWiNgvbtc9Z1eLmx//64on1798zfGp2OdmRuwnP/ngRb/5esf4Tx6+dUvyI53R/97FfIj7TlmHTqs/H5p9Mju9+feLXsddR+Svyb7ms7opt8++usfMb6cNbPwuzxvBfsyvEirHPJI75+SGP14zqrLDx8gH5v9XRdtK97fuOuzgjGeSnj74PYwXjjH8wytf+cnXn206seLadi2e2DgHYfyJ6b/k6ZX3pb0WemDCmg/mlp+chX4olekfmVPy+eUXL+gZWLogZdWHJa9gn3vLiH0oWDz+5SkfL+rR+bZrVq14+DPM2TWK2A//c7eu0z9ftW77BbOzPm507RWQA8znJzctvqnXxt3z32nxt+2fdWs/kFfBw/65w7M=
*/
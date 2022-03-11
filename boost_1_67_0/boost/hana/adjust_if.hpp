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
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
*/
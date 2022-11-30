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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_ADJUST_IF_HPP

/* adjust_if.hpp
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
*/
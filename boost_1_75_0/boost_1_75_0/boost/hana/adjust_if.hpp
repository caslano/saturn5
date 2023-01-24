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
wwrTU1fBuxsGLR79PpPPmpC4VUrGO/ZlYRhirg5HiNuN/+ejScT0AL8yzfk9YiFmC+I2JQzDcEZg/Q3jJzF6q5z/hvG8/7dt5/78n8PfWH9D+Veop+/PD8wzzWy69+kJzCqE9NeSiQmlGF54x1Y/E8RZkihU2nI8WZ03dtm7PBgTNNbZdAWt8VkjEj779aKwhyQlj6TqXEsk2ALEdpqtsOjEAnuZbXKt81CQs9TCc9sVT9PgFhYwT87sc60F0YCJWAfLA/CwCA/ipQHQcLNLtfByevuojlC0tmckmJG+2VdLGDBlCKlg2Iu7ij2AQtnvXy42LpKe2Y2CNzXSvNl+QNz+8aDMhlweUNTLLYhWiq5ln1IVCsokee163nD0KwzM3/vEGfr7hDe5++Oea4uqU9/B48tngy7Jyx7GxI7EG9LUnuZXmz3Giam5i5ROk+MS4uhAFHF3PB2nN+yzaIyyLH2/ya/JRlLqD/bmDiiNihR+APzAGwSnq3s2N/tbULOWkO9RaxgtP333Y1Fx6/cujlsPNncEL/QbX4Kee1AfZPMRHe4KnhI5w+4Gl991BojVOMX9Uaf1shh6diM9znb2eLrRrwSTa3zPNzlb9kD9DdU+iScV1Tc5GPoVHa9zG9++sdqH+XZTphB9QuBLRsDK6RH2MNMc1k0ZB+PZCBsirtfnxL0bmAD4Ty/6U8OOdSeIP80Qtr1u4a7/ld7P
*/
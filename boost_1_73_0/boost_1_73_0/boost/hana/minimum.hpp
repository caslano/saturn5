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
kUN4BWXtkSiMwgYaLmDDsxdAGIV7XjINAoNJnOCiADqBbSV153G0dNfp/KmziqM0Su9XvsMbG4kuCw+2AQ0ON7hEbUsT/5nNUWixLf1lFN/nFqy/nPmTNS15ZvLTaLn0w5T4Vef8fPAOGGi/+woEM0AFCBIeiFfewlHIgelC8evWC0nsga0wusUtFNAPBUP/KkoDj/ZCkFP8EPbQYJHCFpJem9vEMCsJewnIGogc6AkIBwAYYVGN1+Pxxf4hiUE1ED/8O+AsS39x74CQeeXH0TphVE2jhTP3vXQd+7WW89JHCaa1oyfUHFZb7dA2u7ApD+YUGZhTqyDMMErVjmotmtzeXk096yC/Bh5aAj8eHByc6xFhybddkL5O3f+47JzjJpOkAG+R+FVltl9x7QP+nGdL4nXnl67bHQ4BiW8H8HX8etjtwFY97oy7gFITtF5lVAfa+AVkjfNetz+W3oAa8xct18194F6c40ppt9qtg29B1kc6wXHdHBqChrGa4c8hVuAX8yBOmEhvomDmIHnBookdXJ5AdgnBkAHmgHwKsqSjij2J5KU6DewJxwrMqa4Qc957CTJKAR4B4LKOU1HG+QmaPER+aM8PlOx23ucLVxG3Oakklb3qjg8M0cxp40C82Yw1MRqJswcyfNtE
*/
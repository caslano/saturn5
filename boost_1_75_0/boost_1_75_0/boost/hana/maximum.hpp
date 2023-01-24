/*!
@file
Defines `boost::hana::maximum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MAXIMUM_HPP
#define BOOST_HANA_MAXIMUM_HPP

#include <boost/hana/fwd/maximum.hpp>

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
    constexpr decltype(auto) maximum_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Maximum = BOOST_HANA_DISPATCH_IF(maximum_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::maximum(xs) requires 'xs' to be Foldable");
    #endif

        return Maximum::apply(static_cast<Xs&&>(xs));
    }

    template <typename Xs, typename Predicate>
    constexpr decltype(auto) maximum_t::operator()(Xs&& xs, Predicate&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Maximum = BOOST_HANA_DISPATCH_IF(maximum_pred_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::maximum(xs, predicate) requires 'xs' to be Foldable");
    #endif

        return Maximum::apply(static_cast<Xs&&>(xs),
                              static_cast<Predicate&&>(pred));
    }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // maximum (with a custom predicate)
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename Pred>
        struct max_by {
            Pred pred;

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const {
                auto result = (*pred)(x, y);
                return hana::if_(result, static_cast<Y&&>(y),
                                         static_cast<X&&>(x));
            }
        };
    }

    template <typename T, bool condition>
    struct maximum_pred_impl<T, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr decltype(auto) apply(Xs&& xs, Pred&& pred) {
            // We use a pointer instead of a reference to avoid a Clang ICE.
            return hana::fold_left(static_cast<Xs&&>(xs),
                detail::max_by<decltype(&pred)>{&pred}
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // maximum (without a custom predicate)
    //////////////////////////////////////////////////////////////////////////
    template <typename T, bool condition>
    struct maximum_impl<T, when<condition>> : default_ {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs)
        { return hana::maximum(static_cast<Xs&&>(xs), hana::less); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MAXIMUM_HPP

/* maximum.hpp
nb62Cb2UxBOaG+aIrzRIsmOvIl0DP9/hna73rowQfnoA93PTtyVCRK7Syd2HTVdZYr04q4BnfLO51vE/S0fOOalWlK1Ozkc911wiN6X9JlXtQZFSl9y4DIFL4PI9KDI/vgdF5nbvQZH5pcn3paD6HwJFOW02g9mRotXla3MN8Xq+RwTDP2h/ir8IkxCVqLWm8T2EfNeK2x+3LxmStAWGdEtCVDzfRlBTPMNvx/ENTWkOyHOwU2vTmh1Au2sCvA/ALAazAsx44FEIG8L3YEzkrTOK6zvzeUsbyvebkH8632uC3O3RHrVwiMNQDQeYJjA+KZrzNN/dP/HJSYnYg11Ce3lVJbRnu0UJ7ekNLqE9vN1LaM9x/xLa4xpeQnt640poD3hKCe2xHVlCe2+zAHHvSV4J7fm1ltDe4GJAnBy7SmgP7swS2ns7H7Ax4OIS2stcVkJ7aFcB4p6X9YC452djCe3NrSihPcF7SmgP75ES2rt7poT2Nl8CfAzwegntYb5ZQnuH7wDifh5gHN9DfGIC7VUOmEh7j1UTae9xi4m051k9kS9NsGBAVFJ2n0h7jftPpL3J4YC4lzUOEPdJpQDinteRgPi9+CxAXGvMA+yPfAB8AvkAiHthXYAa5ANgOPIBEPcXLQbE/UVlgFhvqwCxXtcD4nczNgLi3sgKwCHIB8ChyAdAlJEzgMnIB0CUn+uAw5EPgCgrdwD5hTb/
*/
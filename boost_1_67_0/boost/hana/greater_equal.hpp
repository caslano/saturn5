/*!
@file
Defines `boost::hana::greater_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_GREATER_EQUAL_HPP
#define BOOST_HANA_GREATER_EQUAL_HPP

#include <boost/hana/fwd/greater_equal.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/concepts.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/if.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) greater_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using GreaterEqual = BOOST_HANA_DISPATCH_IF(
            decltype(greater_equal_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::greater_equal(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::greater_equal(x, y) requires 'y' to be Orderable");
    #endif

        return GreaterEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct greater_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X x, Y y) {
            return hana::not_(hana::less(static_cast<X&&>(x),
                                         static_cast<Y&&>(y)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct greater_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::greater_equal(hana::to<C>(static_cast<X&&>(x)),
                                       hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_GREATER_EQUAL_HPP

/* greater_equal.hpp
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
*/
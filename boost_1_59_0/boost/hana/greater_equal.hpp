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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_GREATER_EQUAL_HPP

/* greater_equal.hpp
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
*/
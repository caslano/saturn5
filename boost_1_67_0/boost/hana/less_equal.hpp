/*!
@file
Defines `boost::hana::less_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LESS_EQUAL_HPP
#define BOOST_HANA_LESS_EQUAL_HPP

#include <boost/hana/fwd/less_equal.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/less.hpp>
#include <boost/hana/not.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr auto less_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using LessEqual = BOOST_HANA_DISPATCH_IF(
            decltype(less_equal_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::less_equal(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::less_equal(x, y) requires 'y' to be Orderable");
    #endif

        return LessEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct less_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_(hana::less(static_cast<Y&&>(y),
                                         static_cast<X&&>(x)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct less_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::less_equal(hana::to<C>(static_cast<X&&>(x)),
                                    hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LESS_EQUAL_HPP

/* less_equal.hpp
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
*/
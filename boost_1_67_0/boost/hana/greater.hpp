/*!
@file
Defines `boost::hana::greater`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_GREATER_HPP
#define BOOST_HANA_GREATER_HPP

#include <boost/hana/fwd/greater.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/concepts.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) greater_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Greater = BOOST_HANA_DISPATCH_IF(decltype(greater_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::greater(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::greater(x, y) requires 'y' to be Orderable");
    #endif

        return Greater::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond
    template <typename T, typename U, bool condition>
    struct greater_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::less(static_cast<Y&&>(y),
                              static_cast<X&&>(x));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct greater_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::greater(hana::to<C>(static_cast<X&&>(x)),
                                 hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_GREATER_HPP

/* greater.hpp
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
*/
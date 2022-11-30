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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_LESS_EQUAL_HPP

/* less_equal.hpp
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
*/
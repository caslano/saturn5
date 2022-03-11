/*!
@file
Defines `boost::hana::less`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LESS_HPP
#define BOOST_HANA_LESS_HPP

#include <boost/hana/fwd/less.hpp>

#include <boost/hana/and.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/concept/product.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/concepts.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/equal.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/less_equal.hpp>
#include <boost/hana/lexicographical_compare.hpp>
#include <boost/hana/or.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/value.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr auto less_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Less = BOOST_HANA_DISPATCH_IF(decltype(less_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value &&
            !is_default<less_impl<T, U>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::less(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::less(x, y) requires 'y' to be Orderable");

        static_assert(!is_default<less_impl<T, U>>::value,
        "hana::less(x, y) requires 'x' and 'y' to be embeddable "
        "in a common Orderable");
    #endif

        return Less::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct less_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    // Cross-type overload
    template <typename T, typename U>
    struct less_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value &&
        !detail::LessThanComparable<T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::less(hana::to<C>(static_cast<X&&>(x)),
                              hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for LessThanComparable data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U>
    struct less_impl<T, U, when<detail::LessThanComparable<T, U>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) < static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants wrapping an Orderable
    //////////////////////////////////////////////////////////////////////////
    template <typename C>
    struct less_impl<C, C, when<
        hana::Constant<C>::value &&
        Orderable<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr auto apply(X const&, Y const&) {
            constexpr auto is_less = hana::less(hana::value<X>(), hana::value<Y>());
            constexpr bool truth_value = hana::if_(is_less, true, false);
            return hana::bool_c<truth_value>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Products
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U>
    struct less_impl<T, U, when<hana::Product<T>::value && hana::Product<U>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const& x, Y const& y) {
            return hana::or_(
                hana::less(hana::first(x), hana::first(y)),
                hana::and_(
                    hana::less_equal(hana::first(x), hana::first(y)),
                    hana::less(hana::second(x), hana::second(y))
                )
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Sequences
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U>
    struct less_impl<T, U, when<
        hana::Sequence<T>::value && hana::Sequence<U>::value
    >> {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs const& xs, Ys const& ys)
        { return hana::lexicographical_compare(xs, ys); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LESS_HPP

/* less.hpp
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
*/
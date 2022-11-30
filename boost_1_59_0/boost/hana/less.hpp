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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_LESS_HPP

/* less.hpp
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
*/
/*!
@file
Defines `boost::hana::div`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DIV_HPP
#define BOOST_HANA_DIV_HPP

#include <boost/hana/fwd/div.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/euclidean_ring.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/value.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) div_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Div = BOOST_HANA_DISPATCH_IF(decltype(div_impl<T, U>{}),
            hana::EuclideanRing<T>::value &&
            hana::EuclideanRing<U>::value &&
            !is_default<div_impl<T, U>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::EuclideanRing<T>::value,
        "hana::div(x, y) requires 'x' to be an EuclideanRing");

        static_assert(hana::EuclideanRing<U>::value,
        "hana::div(x, y) requires 'y' to be an EuclideanRing");

        static_assert(!is_default<div_impl<T, U>>::value,
        "hana::div(x, y) requires 'x' and 'y' to be embeddable "
        "in a common EuclideanRing");
    #endif

        return Div::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct div_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    // Cross-type overload
    template <typename T, typename U>
    struct div_impl<T, U, when<
        detail::has_nontrivial_common_embedding<EuclideanRing, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::div(hana::to<C>(static_cast<X&&>(x)),
                             hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for integral data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct div_impl<T, T, when<std::is_integral<T>::value &&
                               !std::is_same<T, bool>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) / static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over an EuclideanRing
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_div {
            static constexpr auto value = hana::div(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct div_impl<C, C, when<
        hana::Constant<C>::value &&
        EuclideanRing<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_div<C, X, Y>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DIV_HPP

/* div.hpp
+323DOWyOUG0/W2FcPZJmHi3h/YQtsyDyLm0DNeDB3S4ZCIjm5nw79DlLhIXp3wj5OHLW8R6ErDitjWGplbTIHaD9fDa6ILGP6lrAgYQmclFRdAG1R4sLou4RbdPdI91D8Hs4HYlJPOlArs8dGKcW8AXbzMy50oFC+InuQH8dB9jnMRMN4d436VtFAlM/VYe/eC5i2kcmb7QyEkgbSO1PDTqQC1VOqND1wI0guVcGe5Sb5PvjVuz5/ge/xSIz/m6Wzfrv3uRWbtd0/O15GSC4fmFKsETwzlHZUCp0tQQsfvs6CGnqVobu7iYVNGsw+RAJ+QvWQ6BuBo8AKMWD1uDMaoaR4c/WQs8mmqRMmGCGjNkIVPYdOgnW/UOZg/oUkzinqZjkpn7U3lyfranWpYhrFEhVeeAbljmbuZut3FrVNtfLIPSRCYCP70i71O128OInSr3FPDc7HttVt5lDtULHUrwRH+ucByElztjnsNrA7AdfkjgROx3OLejLf4K0/gRTn0n4UN6Wzv1i9YN33qIFTLFIrmb2zeP/BLDaPj+cteAsTQQHbVj4v/Et9idF2dUK6N5LrFwobUdO0hLRkzeXbpBUPfxMxG/7q8lhbdanV8hk88C6a3sHuyXOefq213Gfbev8z1tLuHzIPD7yX6/gj8BKDce5OpSznALlvBr5/jrUCBh9Y1EBG8ZGJ0UzlFlgPJl66b+rAwGg1sl
*/
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
9ql0qy5I1Z2FnlATjgANqayCQ+0XXlXkdu0dQ3jmoHEzQNON5wPUwqQlPM5msxQEd1+k5UUcFpV0CUCTpd7Yc1TE+JKzMrSjRCp3nyn5rzfkoSTz7ys8G+QlHnpi1buiXgGjDbVwKWLdABAP4vnJTVw/VdwsPOma5nKxeq7hkE9DANhGIdiQGyZfWkdGUmwrFVStqh1+XimJTWfVS87qoL5d1atNow1o+KxoQrlK4+WaT2zfrFnSUjzquL4qvoOrNu+KW99rBRv4lSapOQdB702j6dAfgCoVPEKZ+KlQUBKwanDsd/rJYyBEgvGkNwotxsyMuoepnWGs8TCg5W/1ikzKxEnClXtz4s/EhLdwL84tnE38rqOStTB1Bg8kiMdYiqmSmykrhoG2bRzFYnvg34vdXzdhaoFViRsBOUvekH6S4COllwFTV7KT9l4gSBoreaPNPrv33h4+5G+p2zZRnXDxMc9w5qdj+mslkm0rYE8SwvXYPzLODeF9y0/DPbeGryWjz637/0R0v5H8HmyHycaSLWQpfszLlHDbrMjH87pxWP5Vw2JWqB2pDA==
*/
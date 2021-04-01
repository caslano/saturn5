/*!
@file
Defines `boost::hana::product`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PRODUCT_HPP
#define BOOST_HANA_PRODUCT_HPP

#include <boost/hana/fwd/product.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/ring.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/integral_constant.hpp> // required by fwd decl
#include <boost/hana/mult.hpp>
#include <boost/hana/one.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename R>
    template <typename Xs>
    constexpr decltype(auto) product_t<R>::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Product = BOOST_HANA_DISPATCH_IF(product_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Ring<R>::value,
        "hana::product<R> requires 'R' to be a Ring");

        static_assert(hana::Foldable<S>::value,
        "hana::product<R>(xs) requires 'xs' to be Foldable");
    #endif

        return Product::template apply<R>(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename T, bool condition>
    struct product_impl<T, when<condition>> : default_ {
        template <typename R, typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            return hana::fold_left(static_cast<Xs&&>(xs), hana::one<R>(), hana::mult);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PRODUCT_HPP

/* product.hpp
Wnf9xbEtLKWEujFpUqjQW5VUcf+au5v8A+/JMgjG3/7jqOlbYTuOq/BWqP4Ws6odCw1U3aoNmcnYym/2kUH2z2ObtbiDpdyoGpGUSu/qrYoz3hUVo8/cGwELxu+sTIQayX0rUbjwpWXk+wYSW3DfUaaB6fs/KFzk84oKUH2SFzZiDp/ej/Jq9H51bNUrLBeDbc1XGSfEUtM+0WWAQzDiz6Y1NNgVifBpcILdBmC4Zw8Ph1QqZeaoR2Ti0LgyZoj1wjDmsO1upWKYWrp7XY0dOBUSIXblEP+KvInML9wtbuXi9UWECyC0N/Hj8Tdq3l4iijylBsHQjP1uDjd2oNZSBeogjFXVm07/TWDttxl2SX3f96p4l9yy9uJ2khCBywMWnACy2S0bcQOytP0ZO+lQWOzFCcYRE3SYCyfJ9My1IAxud7PIV3Gced24jmKZ+Km1w6ut6K2Gbd4ZGakpCigSaD6KIHPSYN27VMiOfcUEFvvvywLqOJurK6fVDhEtknkvTY+NkKxaq/IypeVmGAymZlBQFwIeT5w7IL6tUEEdVz9wCzgFYBwFoTZd/g==
*/
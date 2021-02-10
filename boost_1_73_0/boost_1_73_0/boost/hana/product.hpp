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
BZEj2L1qIza89GZ+mAbpfY0krB5mCssxVthNQBGlfMNzvh4464/oDSYLZMf4Jm93by9H5KeichzLPblA2mg5AzQO3AaJ5DGuLxFTycqf4mWXBtm8oR0EjmDmgb/Q4fJH3Ct5KF5p5j0ZbFy1jBskGjOvKL42ZSEEmpVKRis4BP8uSDhIECWtm0Lf2Iql/V1nyqc1i5aE6OisoYk4SAPcWGKfmOI69q54S1dRwTWyxAeO8Ew7mCRiy+KB87Uostuq9zF5VQqGyPkSq/+GM/rd9z/+0aIpIxsSTADGGM+wjcNVad9o2rLpEgtuHoN1v3XVaubAqf4zYXpySQkFivAeCyAgQSyeLKOQCzsRdAKlHm869VcpZfdrEMITqH9PN6k8mVeQbGZTLyb84gYBc4D2QIm9ZIOj2FDYPLaNyKJABUsEFQrNoJ8o9AoPSGLjxxzmBS+ytZwujXG35bXgrSxPPHCI5InYpNGiN/Hiln7Rcua7hSpSQZfGcryQQr6xgHJcwsSOcS0Ccy49co7qXeBtfkqcGHtk5ybUewhF8Z0WwpNA8mrtBBcdqZZbr8s1hQpQc71D7Kow1yi9Ukn/DjC+uDcun0GPpAJ0GYZT4nxxg6HC7rF7X++0Dz8cuYptwsSTG5mQojipcdZCmdW8
*/
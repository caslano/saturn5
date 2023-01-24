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
uUzsQPXfW193Bf5Maoe5zMK5+f3cfwF/n1rjHRzJfEn6c3SLWvBnXVo92R/BxJ6ecORMylBoL2/T8zlMWdh0w6b1AcDv794ec5iWmX+ktBkA4yX+5Z5yNrP7oeBT/5egD5UX15ybxTxNm3Qh+NwwkA+/reUspshj+7Ky2Jbgz4eeGjeTuTYg4K/9y0TA713p9nDm/TXfi0ebAf6Sp9dPhTE/rWj2SqTqA+WTK0bOYG6Xn9yhGwTtp1q53JnOnNNZHs45hMfno1fENCbhwdkf5/vR4E93GVMewji521gW9gH+pJunqqcwC78UeGtGw35CPDDCMZhpd2VCbfKhvkCvfdTByczek6N3L6gFeolD53lOYtYFL236sxL4ST40i5nIvGgZs5AdDPI0imXjAxk6ZtSFjDkwnuEDE85MYHxOXvcuKIPxUEVOKRjHHFq9qWDYQBjf5GbtK0YzS7w7d9VVgf6H973TYhSTN/hjk8xgoB+ere43gul72rKFvhOUi+91nTCUOX166IdBnaFclRl9T8Qoe74a0HlOrgG8u81OAxmLaJtRxY9wf37XT+jHnNg3ofsNXz+o37zEqRuj8Zn4oGA79Ifybe3civnSU9c/NK/VP+0P4HkE+AdGCZeKR3ApNZxLVUMJLCawH6k3hOD5EngwgX1IvYEEbwCBvQnsReB+BM+T4HkQuA+Be5F6PQleDwJ3I7A7qedG8LoQ
*/
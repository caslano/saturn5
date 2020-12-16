/*!
@file
Forward declares `boost::hana::adjust_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ADJUST_IF_HPP
#define BOOST_HANA_FWD_ADJUST_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Apply a function on all the elements of a structure satisfying a predicate.
    //! @ingroup group-Functor
    //!
    //! Given a Functor, a predicate `pred` and a function `f`, `adjust_if`
    //! will _adjust_ the elements of the Functor that satisfy the predicate
    //! with the function `f`. In other words, `adjust_if` will return a new
    //! Functor equal to the original one, except that the elements satisfying
    //! the predicate will be transformed with the given function. Elements
    //! for which the predicate is not satisfied are left untouched, and they
    //! are kept as-is in the resulting Functor.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Functor` `F` and a `Logical` `Bool`, the signature is
    //! \f$
    //!     \mathtt{adjust\_if} : F(T) \times (T \to Bool) \times (T \to T) \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to adjust with `f`.
    //!
    //! @param pred
    //! A function called as `pred(x)` for each element of the Functor,
    //! and returning whether `f` should be applied on that element.
    //!
    //! @param f
    //! A function called as `f(x)` on the element(s) of the Functor that
    //! satisfy the predicate.
    //!
    //!
    //! Example
    //! -------
    //! @include example/adjust_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto adjust_if = [](auto&& xs, auto const& pred, auto const& f) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct adjust_if_impl : adjust_if_impl<Xs, when<true>> { };

    struct adjust_if_t {
        template <typename Xs, typename Pred, typename F>
        constexpr auto operator()(Xs&& xs, Pred const& pred, F const& f) const;
    };

    constexpr adjust_if_t adjust_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ADJUST_IF_HPP

/* adjust_if.hpp
P+H5t4vnX2q0xzbx+yVnc71dBwDfeIHza0OV4TwyPlJJfwCN+POpWG94AqV7b2V8MS9i/WwYoCz6IdreXw4oa67i/vsh+eVnyMvjvrCQJ9xzj+F1ODln8X34NfO7tO/exP2N8cBbn0EfVz5N//RmIDnlXfqPKB7mNqLKG9cz3oxhVvs/5PzSd/yVL9G/+kf6z8k0X/36MMDjkjx/C+f3Vn7/NEB/aNFw3v/l914fYLxAFuo1UkCNokZ7PVWcawjeTXXm8vtRxXqpBHgH8XTrH3g/5cfUT4nLuyPRb+nXAP4Fgr8qE68/Z+zMWHpaB30fLS5jzPvxcSbDrlRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVRKpVT6f0rBGkeWwT+0rdCR9f0pBtuBm6/QNL7M5Mufv6Rpvep7WUvzO+wD/ah11ZoWfNweiTU46fbTtny69qWNH9W+KdNgMKjVt2taeYXboyx2TFaMym7F78hrabZM0gyaoeVJS92rBjxl7FbmSc5TQksdWcrufkstTrek7E0UPWVB3by610TxXmWeVdntrLL009Lptio7WlSbvK1dibSoFnlbs2IN2xePtCmYDqe1we7CY1uLKp5L8FzoyEMlvi3F2w5nqQ3NQosdBMGKNoLIDbOdM7eBkNiEAHIJAMURPLEx853XZbIJmxLMakdmNwbx3iNo3BLlq95+R8sbxIYgnKVZhILuJ+vIy9ue6tW6zWm9m+3CG+1JeH+hA8R3lmY/1xlUjaHFAFHosMv1Q00Ggzyx3sCkrMSMtPSkDWbHFqfPUkdmvI9WYNiNXhw3majpxMkGDNZCMUfHRqxFMDuS20a66XqxhOpomhVryu5b3rAo2aJ3soszW++9hfQ5gNY7mdM9R3wjHtUWIKVkoh1eMtkmPiV8Y/1WfWjZfGcLz0BM0XfABJWFCkmIE2syxYBjZhPlAECgYmYftmApW3UP27kmM9Y/GeRE2OLiLEJJsMVT/YwgxhYoSTTKDrbZg6sddsEQcsPxDzVNaQEbgEVZDzOeK2/bbF9GHDlCjLuWby37Lc52ZLEzztIr+I0CgGzHsJJfnTJmq8XS0m6pe4UrcZJYhS0hEwHqvcR7iPSFn9cXPnvtlQXO6b+T+RKBJvXBxn17sfXbS16fXizopd0igKM3dEXJErWwIwsh9+4qr0dXfUjDnvv0YRUjqU4MpSo2lsrQfOuK4OOZkV2p9K9KTTbuT481YBFgmWKP4vbU/9bkwWaR6xwdwgIZcH/y9NmfMpP2JwipflvG5A+5IxNiCTzFdVyQWLdzBGvlxsTRrIT8LYyJIrSOyVBCYqtY++7Gmd2NCYqAuwFw6cc2NxYmhCHbsloBVyoED2CE19h1MGzgIM0gUh3ytpaWAxbK5hkASsETQq5zYZbAA3ULUVdAThoSZRPHwv2ArSiblMe4ZT2nAXhu8KBRrrdhr2IPlJIkERdQ8hC5Q2UJgBzKQIN0LjEwg3QCxgTTOgCdbH2JzOZSDPv4LrcjvlXZuFWxKcjHrYgYcd/gM2HECcN3QqqMb1PsNTN5avlGxLlN8bmQRHdWWBPjzv74qe3BF0t68MUATJXd3ZigWNYNIIkvWNiDL8AOCdYgjB5Mkf0RTFHUiykyP4YplmQHn7DH+aGhg9tVNw+sxB67FBpMDGdArHvFwMWloyoJpChODZC9xJNZBcxCLWSRSyi+kcvO28koA+5dDr3T7s4=
*/
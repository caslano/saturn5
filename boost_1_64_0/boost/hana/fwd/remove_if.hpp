/*!
@file
Forward declares `boost::hana::remove_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REMOVE_IF_HPP
#define BOOST_HANA_FWD_REMOVE_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Remove all the elements of a monadic structure that satisfy some
    //! predicate.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a unary predicate, `remove_if`
    //! returns a new monadic structure equal to `xs` without all its elements
    //! that satisfy the predicate. This is equivalent to `filter` with a
    //! negated predicate, i.e.
    //! @code
    //!     remove_if(xs, predicate) == filter(xs, negated predicated)
    //! @endcode
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M` and a predicate of type \f$ T \to Bool \f$ for
    //! some compile-time Logical `Bool`, the signature is
    //! \f$
    //!     \mathrm{remove\_if} : M(T) \times (T \to Bool) \to M(T)
    //! \f$
    //!
    //! @param xs
    //! A monadic structure to remove some elements from.
    //!
    //! @param predicate
    //! A unary predicate called as `predicate(x)`, where `x` is an element
    //! of the structure, and returning whether `x` should be removed from
    //! the structure. In the current version of the library, `predicate`
    //! must return a compile-time Logical.
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto remove_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct remove_if_impl : remove_if_impl<M, when<true>> { };

    struct remove_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr remove_if_t remove_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REMOVE_IF_HPP

/* remove_if.hpp
ySyLdi+6nXf1chsYvnY/1vYpxwr/Jq7tDoDvz4EZa9TxUqrz7rivFerrtmhc7HkcezZ7k/b8eDzQdnFrl/jxcIMDQmNno7G8e5nvwQDrLQ9PzEC/wpxFuOoIHZGylhmrZodotxXcbp4e7f4AY0NWcHsUvT6pLhz+HElhxaRqy+OUHlEumd0FyNcAcuMEOumdYw3tiFcwgNJd2HKhuIqUHY9hQer4tB+9zE7NPLDowZxx98XITjxk4XbUtAvs6c63bbaY59dYppWVPL/kk8IXEe0JX+Emfnx+cIx3cKAcijzhjGnQ57M9Zg5ueSV45OLlI2yb1j06FkpNOVX34DEeyiaRffNrekV61C7lU/facnqk1F5Nygo15vElryz5o+wLr94TUUJdqGYn9ESt7InCLfNrJjaJG0DuwCdO0G5FO6jyYzbqXVzhM0kwNVXUV2H+SwhsplbSEz1lQWo8THhEevhwSwVQ9H4kYPvRE+H7BYKQskr0+ayrRB+0dftFqfZ38e8l/NuDf7vw7yP8M6XAWiz+V78U9TOnJP6SWoSTW4QtO//rf7V3LUvQJyM6Js1uqX9i0uCTMXk7sbKMyS3mocqVACH1TCDQ75T1qc1JxKczr8+yM4GQ8FP+P8AHu+m8VJ2fSl9Q72Amk8hDmlfsL01DHCTETgPrcr542ayOBJCCrC73175nJFnESR5JSCJv57CHTD5kxdrWO5P2KCqXB9rcnSBpkBbmBmh3twB3tQIH/CeA0lriVYMkd5pMFzK94h5mVi1GIv0c4WvxHy37a1wGG+G6HCKMwibcPkCr8C+DbiD4KmR9y3xrUd8/mYz6Uum2TfLe/vI+amdQ6HPJ9Es5fVCm962UvSHMEBx5xeP7qEfsCgof+vLZ3li0i+Gs7OPzSDjLGE6JSfnuyow8Qp3uQnX/mKNMZ/6MQCg/qqzmLA6ZFCiLb17kTxQJkdMubL1otBrwT6UdIxo4bSanvS5yC8NHKjv6wI7WHWaOnj3VFkaxKizSG1P0eXOU9nSFTfLa+KCjHC7yCi+PGLu8NSMHMbZfx2C14yf9d/C+n/WnjM1/ID1ELSqQHju2eutEki+HGxK2lMI5X6fYkVe6b4g+5pHeHjeuqdO3bfRt+8p8X778tsC3CuNyL5gpGt9ijvSKAYe4q8AR0LFZuDyavHVd8UWBDuHS6MV48R9mTYjiUN3ZGtqKXrAOPKS4740Yf0kRLpGKLteu7MD85dHup71/naUN7WKyQzDgwHrjW6o5fkQjetVn3ByDtUzwjxQVwq7kJjcgQtxmk2pNIUG7FwxwuBKSSOkM1SydodYhgpyhnjjmL4czVDOcoZ447i8mZ6hl5Az1xAl/HjlDLSNnqCfgnICcoZYl+3tECyvESruSuXzvrGUu2swfqfMQsDIaAraJ29j+vHj77zxWidDAR5VwZ/gy0OA9nWJnIN19Y/GBKcG3MPK/OcZdhfHEOQKEZR+/1GyYCfcvkUuCS8z9SJ86a9P42mdkovYmwTCRDOKSZv7I8oSX6WOuR/v55FQ7OIh8bDUPcAGAljFqjXV52tMsYHZoe/BARXi/eRMqki0rQgB/3wjWfqI+lj88yETmLM7QEvrDN1cWZhHPZ8Q6I8v3Db0z2MsBqnH3l81KPCv2dCGHaXxL73q9NtaDze26pafwM1+zmmU7CUmf+wSUZVmOuB0YoXVUH3BQjXgsi23DU/q5hIk1VhqsBhPZIzvNeVOOEeHRDhj9nSt2pMd1gXYQXxRKBNAFPzxqdIFX+1x95JV3Tbq6KUwztqlFxjkyY6QH3dMly/Ve4ZfkG/5z/OcldMXTH8uuuMWW2BW/RjyzrRjumjVneAqnfmp/PSI=
*/
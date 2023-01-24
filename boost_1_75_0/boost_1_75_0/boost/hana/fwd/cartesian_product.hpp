/*!
@file
Forward declares `boost::hana::cartesian_product`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CARTESIAN_PRODUCT_HPP
#define BOOST_HANA_FWD_CARTESIAN_PRODUCT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Computes the cartesian product of a sequence of sequences.
    //! @ingroup group-Sequence
    //!
    //! Given a sequence of sequences, `cartesian_product` returns a new
    //! sequence of sequences containing the cartesian product of the
    //! original sequences. For this method to finish, a finite number
    //! of finite sequences must be provided.
    //!
    //! @note
    //! All the sequences must have the same tag, and that tag must also match
    //! that of the top-level sequence.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Sequence` `S(T)`, the signature is
    //! \f[
    //!     \mathtt{cartesian\_product} : S(S(T)) \to S(S(T))
    //! \f]
    //!
    //! @param xs
    //! A sequence of sequences of which the cartesian product is computed.
    //!
    //!
    //! Example
    //! -------
    //! @include example/cartesian_product.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto cartesian_product = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct cartesian_product_impl : cartesian_product_impl<S, when<true>> { };

    struct cartesian_product_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr cartesian_product_t cartesian_product{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CARTESIAN_PRODUCT_HPP

/* cartesian_product.hpp
Hp1WmCnmKOuz0VBJI0jIrdbyTF1iGguUkOD+QRzLdNNs4lbK++TyvuUSCw4ZJEqaruD3qmlHCsBj//ZDgP0Z/uEfTIAXNyzZeFlntzAaGBw/LU3IUKjW5cIyLwEBaaYqsvEEtUSvshxy/U2dF+ntqjUck7p8unQeTUmPRya4oGxmZujPI5XsQMnADQihCRo8UeKLVyyROVv9Nv9wEKS2dKgojhUoBh51IYjL0ZukoHejWt18KuwD1w8StAf1mz5AhK6eWA62RvIa+ckumMZOapI8MUZk3vqDJSFOidZz8b1n/3+EGHOeANzUFrO40IHLIPQj1xNI1w+WiAp2qMtCh4o9xFmpsEFd/1srxuGtisID4ePBu/CsPq+V/+MAHuDBGx26XXtMlmfDB1DjqIs/0YjjJ0Wl8fQPYULJO8rbD6CSYKsI1vMv8dPJIwUNisSmJ0zUBbu1Aj1p2uVa59bJZo1mXq2zEndX3FLJO7XOHSj0yh9LhXsjBVsX2Y8rKtCSMwoQoZM1CB7Gic65I1JwFN1GOg8skpyYHpIswjRS4VEAfgp9fxW+I5VUUp6xM7R1lrLg6N0Tc9CAzseQXirZS+l7FEITzkh4gQgx+aC5DjXCxegsUkc+UQq5mFrsx+eSQkJvHFBoMiB3wHmoGKAR5l9PKLsCND8UNMLkkEEKCTQ1bK7mD6fD1ADNjjqVotVt1Ooj0Z7HK/6RlZ/j
*/
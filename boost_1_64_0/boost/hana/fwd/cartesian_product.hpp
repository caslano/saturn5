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
C7KEV1+H7su1LUfdTOXzg8/bhH+PzTg0Y1cSlZwxCTT4r4zcTZz6PN29ADwjhW+XrzW0QVRQ9TUv+CyQm53K1ZAMMd7XK0QFs+O5qX4SwWdEf3ESsHHKNn+clscakjUPl9Q2OabJv0Hhh+OCjplOR6GUC7K9EaaDc2s6pUmAl4E8GWYe19uHkn/noSac0XllwRN5AvndZFefvsD8dkxwXUhuCfGVa6cEOmzCuSd3wrYZXz5wu1FdCS7VlujIhAD404ML/zy9RBobIUxmxGkMUp6dmmcPdQ53+eLD7BW471xsD7Kxa+YYxo8upV8xvZ4IfGe2KUQr8sV41PrTDbz6eew7vBnYal8omNBCbsjTqftFYfb+KMw9AFrtbmhR8FaUhJ8K9rxj6HoiaQYRt0LbO9sj/ave+sI1OW7QlWywKyWkZ/09t+ZB3nJtx81HsN0Dz4dbO31MyhDXJsmoaQDduWPbLc1Yi7NgoyR8WAtn7t7BrM4FqaFhE1AeszHq9+5of9DXa4cxznO4w3/BNgk5dG7QOzKZbMi/oamKG4GQf+cHn4aSA36+IY74dA==
*/
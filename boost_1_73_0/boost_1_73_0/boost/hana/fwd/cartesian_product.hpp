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
bPjjBDm/OPgrjAAbcl6E0Vrw2VyR2kWdnH3//XfkmLw8fXnWJJc04MwnI8WCCROzJnnr6ZF/zulq1ZLspyZhilC/ZaHGcy6JDKdqSQUj8LvPXRZI5hEqicekK/gE/uABUXNGptxn5GIw/NTtXzXJcs7dOYKsw5jIeRj7HpnTe0YEcxm/NxgRFYqEU2AHcI9LBYCx4mHQgrkZUUwsJGLg9NSXIaH3lPt0AhNRReZKRfKHkxM3Fj5If+KFrjxxk+W35mqRruQTCLGgaxJGiqiQxJI1CVI2ySL0+BS/YUNgMIonPpfzZiYNTBV4J6Egkvk+YgEfZ9KIzcjIbk8TyUgEEnOFXzIMJE61nIeLAiHsI6JMYxHARLAPQOSFsM1NEoMbCU2sV55MYfdUb3ClajJ5PRIGIAx51h6R7ugZmVDJZZN87I6vB7dj8rF9c9Pujz+RwTvS7n9CsPfd/iWonsNkgrBVJJiEyQXhi8jnzLNzPt3n5Og5D1w/9hh5hspzJFNx1Jo/OzqCRcTgkW4YBOCZHlX0TTImpe/Yccc8SMPLaNQb3Q6HzkXbGbbH18ZNamdv357WyUmDyDiKQqEkuWjrxyjAJmfnZtztvxuknGcbnBC5BsNxRleCMez2+53L4e35+84njfGyHCOl63Uv
*/
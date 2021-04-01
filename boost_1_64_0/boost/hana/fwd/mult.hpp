/*!
@file
Forward declares `boost::hana::mult`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MULT_HPP
#define BOOST_HANA_FWD_MULT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Associative operation of a `Ring`.
    //! @ingroup group-Ring
    //!
    //! @param x, y
    //! Two `Ring` elements to combine with the `Ring` binary operation.
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `mult` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `mult` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Ring`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Ring`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! The definition of `mult` for data types satisfying the above
    //! properties is obtained by setting
    //! @code
    //!     mult(x, y) = mult(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/mult.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto mult = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct mult_impl : mult_impl<T, U, when<true>> { };

    struct mult_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr mult_t mult{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MULT_HPP

/* mult.hpp
pM7TZPFCDhdJBLQxqrtgOaVH/+1y0DIaAG6An8kGbzyeo9WfO4qCegsqqVhX3LlPrZriMmU1YBJiW+6Ls+cKyjzL5D48VgBK1hZ1FoHuxp59hwzYmN9f+DZ7FnjOxGbQdHZr6Mgsu7Ha/ORjL/y7ZoGhq9LlTKDDw95nqWMIxe/l3YMQP9rztJpT3zrfmxBwvNv/OkQPcVijSKttGljnvQdGwG3vuwUPcfRqbraKmzsskfBpoHl21XxDuYMnKPrXfo8R0LYGu4dIsfjYIcVVE4TF31b8mQIL3xLg4w1W9qgtSvMpLKE0QGI2jlHuHYl6OVWSzekFMnN6lBfgfm2GaYJ2oDLFQHE70EwdHKGZ8ImAfHYa22epZ0r3Lob1Og12s7yLgP5opQM7ujofl4L2EAaaY23iMyelpChdgAn9LdJZSZCQRXHHjxE8Ao0/bdwkO27O5BtEuYNFeh5nQdynuhf+i0Niq4MDNOqa0CRrFjHeEiJid9iB48r807BbsIspbmmbglwPTpCuwlvyIOguQd+Rcvt9d2c/f1vYTLn0tGPOU2TeCme+VrSHhQ==
*/
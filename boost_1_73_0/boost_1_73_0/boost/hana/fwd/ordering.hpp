/*!
@file
Forward declares `boost::hana::ordering`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ORDERING_HPP
#define BOOST_HANA_FWD_ORDERING_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a function performing `less` after applying a transformation
    //! to both arguments.
    //! @ingroup group-Orderable
    //!
    //! `ordering` creates a total order based on the result of applying a
    //! function to some objects, which is especially useful in conjunction
    //! with algorithms that accept a custom predicate that must represent
    //! a total order.
    //!
    //! Specifically, `ordering` is such that
    //! @code
    //!     ordering(f) == less ^on^ f
    //! @endcode
    //! or, equivalently,
    //! @code
    //!     ordering(f)(x, y) == less(f(x), f(y))
    //! @endcode
    //!
    //! @note
    //! This is not a tag-dispatched method (hence it can't be customized),
    //! but just a convenience function provided with the `Orderable` concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and an Orderable `B`, the signature is
    //! @f$ \mathrm{ordering} : (A \to B) \to (A \times A \to Bool) @f$.
    //!
    //!
    //! Example
    //! -------
    //! @include example/ordering.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto ordering = [](auto&& f) {
        return [perfect-capture](auto&& x, auto&& y) -> decltype(auto) {
            return less(f(forwarded(x)), f(forwarded(y)));
        };
    };
#else
    struct ordering_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    constexpr ordering_t ordering{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ORDERING_HPP

/* ordering.hpp
OjPFsajcDddK+k+wDaURVAtDXQemSLSVisJp6JJSiJXnr42UyGZYB6skyYGTS7Hco6H5xCuyQbe0tnPVvs40WvBTAbwSEDlNyW7lTh05E0eFaaNk0qgzZaQHKJkjimeIWvNDdvwrTAhVpoPyyUCTuvI5ANXkm95P3b/ENJDstFSZCVKoV5oMVI2/54OS+WDqw6LWVEMhYWrbm6I5HL3eOJ2SFbOYYuclN5ObCLeTh5x7uECXLgIWL7ObMSgnotJUEix4ShCugvKkRlVQ0ast5QZgkV8PQzYUJBETmH2vbWQoOJRRaux4VGzIU4t5QmmsssT6QRKOaLnotbxluNLQgBJ/q4BESp8dxoBEFIpXCakZpW0XRBMjofqWO4HGyQNwGhBQTTxJo47CsJWl6028CcKqC2nEZSrdZBWiLIU3sIp7HevvPBNDBrzqJnoBJyY76JXaWTJMNmopMyls5daMSyfDlVsuf/auNMo5tRhLlc5Ew2mbLtWYaBX0hDga8HQuzizP1iBCFatUDeQSF5TapdlaZdTIoXIlGzCRk0LjNN8QlPHdjTQ5y5FcHquaOBbbqsVIxtZqLpI1bNV61mqJvZrJOrvCZq1qtWrd++s6PbLDdid+jmXe+Au7NrBLwPmf16otNmbVeQLdmI13
*/
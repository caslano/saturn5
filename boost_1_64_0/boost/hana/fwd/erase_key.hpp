/*!
@file
Forward declares `boost::hana::erase_key`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ERASE_KEY_HPP
#define BOOST_HANA_FWD_ERASE_KEY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct erase_key_impl : erase_key_impl<T, when<true>> { };
    //! @endcond

    struct erase_key_t {
        template <typename Set, typename ...Args>
        constexpr decltype(auto) operator()(Set&& set, Args&& ...args) const;
    };

    constexpr erase_key_t erase_key{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ERASE_KEY_HPP

/* erase_key.hpp
eaREZWIsFyMaCfxmyyDVnSB83TPMJwvWWi0cwdV98yoCuklpg5La7+OZs11xaNqleitJ81JpbZUocvr1DUYs3ZG+gPYlLJt+qu5AdLGVvJFn9fWzjyqGaIAdjEVoXxxZuOduD+x0h1AATHYRgzv3RpnMllVSwuVvPrabfFKtP0OEEuLVAmLEvVLFy3A2yiJ1vFlobDudFCLaqeHI/JE3kAUWwfag2nC3Z4MlTpp4FhL7/U0u2I9iPSYePzEIEZt6w/SkahNNyKU7Grj7U+te8IGzEmQs5izOplDaGpnb+dFHEBm66aU99UBkbibmsuJOjolGdMXLFXFp0JruPkxtdbjRibav3uHQKMW2eXtIbdYegac5aBAkJy+HbhXr6U2R/FtYTLmIM2VaXOw4Gshr/bE18BXYBO8LmbGedtaKFmE/eecmtF3Hpd5dCCuXRk1BQarqMJ3HGLZd9Vi0zNzNvhVTYzRgbiUvdukfTGMi3xghZfkGjfSb96mrcsOkL1wczkVwP1OTh7jLTDhSUOLN9Z4HqMAglocbE/6Y2Gegh3t9RK+AD2GOCnGByQ==
*/
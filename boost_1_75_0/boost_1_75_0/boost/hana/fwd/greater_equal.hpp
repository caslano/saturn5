/*!
@file
Forward declares `boost::hana::greater_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_GREATER_EQUAL_HPP
#define BOOST_HANA_FWD_GREATER_EQUAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is greater than or
    //! equal to `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{greater\_equal} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/greater_equal.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto greater_equal = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct greater_equal_impl : greater_equal_impl<T, U, when<true>> { };

    struct greater_equal_t : detail::nested_than<greater_equal_t> {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr greater_equal_t greater_equal{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_GREATER_EQUAL_HPP

/* greater_equal.hpp
AuIBRsDdgDCAADgHeRwH7AdsBWwArAHkA3IBaYDP0e405NJmtkzoDVADEgAzAPMAzwG2AEoBPwDOAdrMkQldAIMAZsADgBmARwFPAtYC3gBsBnwOOAD4CVAPkIF2BaAnYBDACHgAMAGQmsnnB2tBPnL58JH5bQEvAF4EmCRCPmKUfMQh+e0A3SR0YKMg9AT97cW5NYupK10mLAesB2wGnAOcAnwLqEjnbeYBB+K//GcBswDvA6IBKsACwAMADSARcB8ghF7vALwG2ADoTGdOAhYCFgucFhlwdwcMAlgBiYDpNP4sPqbzA4kifab/bQfEO5gDYTroDCj7Fm21KLM6m8pOoexICmQYUDYbeNfMwHwGlF1HWTjKMgPK7oVMZChbEFD2AMoUKNsYUDYBZdYZTdf/187+r53972pnSUFjnbOGZWbnOR90LhQeoau4LPdcXMQIhXQ1OseZhau4BTHCs3Q9xu3MXTghJdPtpCIhJnZCTOIIjZo9VhB+DJ6Ym+FyDs/IdApLBIY2PiUrFVeJQfc7XQkpea44il8Q88rGOXl+ZHaqUxDaUf0wd26uM4seB8x05uUJUVQWtyDDNQxN/IXYbfDnEWLBROxdqN24hXku59zYjFznTFd2Lqh/VTI81+lMyJiRm5K7UEilNhjKnSlSBNpfoTJCE5Oamstwvy1NyE5JFfsw/t4KLMH1QelId6YrY+hClzMpe2JG
*/
/*!
@file
Forward declares `boost::hana::greater`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_GREATER_HPP
#define BOOST_HANA_FWD_GREATER_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is greater than `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{greater} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/greater.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto greater = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct greater_impl : greater_impl<T, U, when<true>> { };

    struct greater_t : detail::nested_than<greater_t> {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr greater_t greater{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_GREATER_HPP

/* greater.hpp
gf6uP17oXI3WgMWUVtAWEeIMP/aB9V/rlqFh25nfZ4H8j7Inpaz3ucSa0nY6SNltEGbO7XINbdG0GkYBLPdQ20LY5HnoW1PaadQ7imGgJZzbK2np98ZbM4cE76HKocO87EhGrt5Ywwb9tpE16BRHAh9QhK7iYOC5TGlkPLc8q4zRm/Euh8vDegnY5LXOY5+3Qi8wTfX1NcfufgfhlUq1ddivkEuZb0TVxBX/6vlpqqq43p1sSJC9kY9wxM2BWsTQc2RyMvFHoUpGAuFBlfYsbI7Lx6FNu/Tk+CSu8rwkEvW205xCqL4TY2i6ZwDJSmMeQHm920JLMudb4yUq02qstnfY1w4NkFRinIrK3gbWzLR8Fld6yMFbbndgTbYC3GWn4gcJyO1A3uLsP2AhS2zJjiOBxYbpxruL9Q+7cF6+6uXPg/6TAu6SVe7axgk2rWZzH0N0lFced0lfKGAC1L9cRUAwGHMB/elsxmBsbSqACxfbkwnyKr7R737PJ2rEtYdRN6Y6Lwfkm1iF1OmwaAr3Kd99CxfwS+HlVDqh+9uJiGAJMluUJ4ObhnHX3Q==
*/
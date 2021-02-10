/*!
@file
Forward declares `boost::hana::negate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NEGATE_HPP
#define BOOST_HANA_FWD_NEGATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the inverse of an element of a group.
    //! @ingroup group-Group
    //!
    //!
    //! Example
    //! -------
    //! @include example/negate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto negate = [](auto&& x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename G, typename = void>
    struct negate_impl : negate_impl<G, when<true>> { };

    struct negate_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    constexpr negate_t negate{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NEGATE_HPP

/* negate.hpp
RzQTBQsvAdUbU8euQWMjzlPuzqk7OO0ARGE5wIshtIQNLuZzH2Y1qBPEpCFACGUE6jngVIBawnkDgcVUwY6iGseHrjOkRmzoievPZ4A6AZrBJIg6Ceaq6GkyDfq+25Kz+C4WmVneLhZBkDRJGgAwsILbXeob8gNKtHPv406xRpWS9Dn0aoFGHbmWN1mlUQUaUq9Cyefdl/3z7vbl1t7HZm55EvKPO4CBqPBm8EoUgdl0+1LHRqEAVEgJHiCzfWma9M40sWn8hFDHi6isJoFAXHN0ZaKgmDYfm3E1EkhQsYkwxticdwfvTi+2L+EtgVuN5o2bIJqHqjOc3bi5qK5AVlaMkWUatozhKIImfgDc6s78MDIQJ5BBlFVCSM3nsnxh/zKz4Q+nNKgNesfdkOfX9/z86lpl4GH6tXAFhQCf45+3Oh1mXLH2N1/sg109AalTeP5MpZOSfDT12ZZeW1VogAklzKrT0+/fsAY8b2wNui8a7EG423q4nX79Yfvbr59+u2ccffv0m28ffmil/tppPdzZ/bC/++Dn1HgYn3BIZLONFN2hSAlmJ/M50J/aVeZUg32zC7pi14PyKUhiDAcRWNsoeddg8LEfOr7N2RNYrogxPGg9aTIBVDy49r0HoKXA7gV7LGSLOZiZ3Jpl
*/
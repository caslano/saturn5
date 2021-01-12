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
FbsoN3o1o1fHVL6ggNPNuWQFrgJjE2D4603hvICzmREvD/rtLjJsdpF/pBtKaaAf/d5Dzssk5pEFbpN9w0qh8/TkBYb/hIZKofe5UugMmxkaIZ2h0x45l7QBBeoeKfSgSqGrQ0WZRkOqEk0fg2hgJlMPp/up5ETACHuzqBZCL37mIdXVHU4VcS0D5sIHuvkW7I0V5A5p3V87q6TW3/mdpx3WS8zu+XbobeQKTm1bjtHZ+gW6
*/
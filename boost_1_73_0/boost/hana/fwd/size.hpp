/*!
@file
Forward declares `boost::hana::size`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SIZE_HPP
#define BOOST_HANA_FWD_SIZE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/length.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Equivalent to `length`; provided for consistency with the
    //! standard library.
    //! @ingroup group-Foldable
    //!
    //! This method is an alias to `length` provided for convenience and
    //! consistency with the standard library. As an alias, `size` is not
    //! tag-dispatched on its own and `length` should be customized instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/size.cpp
    constexpr auto size = hana::length;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SIZE_HPP

/* size.hpp
/lDgo8rlD93gcvlDtU4Isen1PzfFP2Xg5zszEe98XB1QYT4O07p+P8HoVLfb49Ve9pxQ5KU7+8xcZ7sk/ZQmtQ7xr/EkPXmGpBLn9EvCz9r5JV+TwAqAO7u8WHYy/jwE2ZABuuk41VQfOCd/FAYcv4InKDnkR4Om60cqlfhJEgt9dm7quxyzz7xfm7lpEUbAE7/Kzk0D+GrnpvC07NwUmqZz02tu27jmmtm+IfYs6CaBP5p7
*/
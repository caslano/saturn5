/*!
@file
Defines `boost::hana::Foldable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_FOLDABLE_HPP
#define BOOST_HANA_CONCEPT_FOLDABLE_HPP

#include <boost/hana/fwd/concept/foldable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Foldable
        : hana::integral_constant<bool,
            !is_default<fold_left_impl<typename tag_of<T>::type>>::value ||
            !is_default<unpack_impl<typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_FOLDABLE_HPP

/* foldable.hpp
UZ517rs7raLkXLf98HXrCpSnnOM75N1iD3u3crIVii0qiSjl+L73bo4j3s3+A31XqNjx/re8x+1H9qFinx3eeyOv66Oe9ZzQYeEvvD5/pO/ZFMsU667n9iv3NNuGjtM5PrKXFZu9I7kPf95PnnX5/ueXedt0HLOKdYq99ciuIF6fx63iLcUGf9+iDe8jT3i34kp2QcLdXXkf8rNVrFZsve3hyfx5J2l7t7jtlUmN5vJ6+YW+j1eW++Od08/zeqmwigj18xZumMDLkeUqFlFa+i73M7KpinW5cFZz970G1D8Vy96yrhXX85SnnRtR9znu1795ft7ITBvvr/Mr2VPn927Hfek0Hf8Uu3T3R+9zXwLm+N2q5xjgz2tQ+2puhzOe9s7d74VxPWnveY1iib/P+IiPHRbK3RXottt+mHgrf15tm9im1KXgonaHeV0H2QTtYtg6BI0/zm1UV8/ryDai5bQD/HlkOfFu+3a5dR/O3e89vz2v6zSb9l0k2/KE/bFcl3SbuF+xA1v7bOF9AdnjijkL5t3M8WXYxHDl89o2H3wZL+ewifxgt0V8fTCcl7vHJt5Slosv3vYatwPlqy9TPu/xQU+/gXLZcwz32cQUxZauj/uMY59qEzSAYMu47MYwtvttgoaLbKsG772X+9kDNtFYsfsCx+7husywiTeVz3ti+rMPc+wPkimf1/OJF37mNqJByJXKchu+ycrh5R62iTsUu/X2WtfzennEJr5SyrzSHrWW60K2X1nu1Nph0dxfHrWJp5TlxrUq78P7nlzqZ4rN3TPiXN6fPUbtV1uJLyj5A15nc/X7jtgS7ztyOcdAdr1Sl0Uzlz6NcvPzcewZmxhgddujB7pwvy571iaKA9x22dHOl+O8997zwvO+gOxZq9seeH9JHm9/i23iPmW5423u5P1gOdlCm9u2vVo/BOVh5zJftYmvFYve+0Uw13Mp5Q+1uC0ocgRb7ms27VnAbO+NnFTEfWI51VNZLjh5ZgzX5Q2baN3EbaU/2K9DudN5v7vJRtc5sunXOXI9gTmA5QJbRtZFsYV3v5HF65rsAsXuXNpxEsdOedCbKhY9a+wjHAOZutx9OW8Eo/zpLhvEptyrJW0osOHAEoGNBeYAlg0sB9hUYDOBzQaWB2wesHxgi4AVAlsObBWwNcBKgG0AthnYdmB7gO0DdhDYUWAngJ3ybhSgdwsEFgysAbAwYC2AtQYWAcwOLAZYT2C9gPUFNhDYYGDDgCUAGw0sFVgmsAnAJgObBuwhYLnAngQ2H9gCYIuBLQW2AthqYMXA1gHbCGwLsB3ASoHtB3YYWDmwk8BOA7N+7t2CgIUAawisKbBwYG2BdQAWDawbsCuA9QbWD1gcsCHA4oGNBJYMLB1YFrCJwKYAmw5sFrA5wOYCew5YAbAlwJYBWwmsCNhaYOuBbQK2FdguYGXADgA7AuwYsApgZ4AFbPFudYCFAmsErBmwVsDaAYsE1hlYD2CxwPoA6w9sELChwIYDSwQ2FpgDWDawHGBTgc0ENhtYHrB5wPKBLQJWCGw5sFXA1gArAbYB2GZg24HtAbYP2EFgR4GdAHYKmPjCuwUCCwbWAFgYsBbAWgOLUCylktmBxQDrCawXsL7ABgIbDGwYsARgo4GlAssENgHYZGDTgD0ELBfYk8DmA1sAbDGwpcBWAFsNrBjYOmAbgW0BtgNYKbD9wA4DKwd2EthpYNat3i0IWAiwhsCaAgsH1hZYB2DRwLoBuwJYb2D9gMUBGwIsHthIYMnA0oFlAZsIbAqw6cBmAZsDbC6w54AVAFsCbBmwlcCKgK0Fth7YJmBbge0CVgbsALAjwI4BqwB2BljANu9WB1gosEY=
*/
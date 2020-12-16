// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_LEXICAL_CAST_HPP
#define BOOST_CONVERT_LEXICAL_CAST_HPP

#include <boost/lexical_cast.hpp>

namespace boost { namespace cnv
{
    struct lexical_cast;
}}

/// @brief boost::lexical_cast-based converter
/// @details The purpose of the converter is to
/// * Make use of the boost::lexical_cast functionality and performance that many people have become
/// accustomed to and comfortable with;
/// * Demonstrate how existing independent conversion/transformation-related facilities might be
//  incorporated in to the Boost.Convert framework.
///
/// The converter can easily replace boost::lexical_cast, adding flexibility and convenience.

struct boost::cnv::lexical_cast
{
    template<typename TypeOut, typename TypeIn>
    void
    operator()(TypeIn const& value_in, boost::optional<TypeOut>& result_out) const
    {
        try
        {
            result_out = boost::lexical_cast<TypeOut>(value_in);
        }
        catch (boost::bad_lexical_cast const&)
        {
        }
    }
};

#endif // BOOST_CONVERT_LEXICAL_CAST_HPP

/* lexical_cast.hpp
zXv3vRlYs7t/wmezkNvvuef8zu+ce2ckvhpTBRvAfwx9nRwA/DAqC18Nh8tir2PxySM+xG8fwI+BU3dcR6f2kH+Yhh3gByZ35u2AA64wBb2hfQ/qKwXwPt0PHwX/bhZLTIC89xI71PkJjKxF/gPbnyHem78Cf2a+25PhavAtv+748o7oHPFAMbG9fR7yfoG4ljN54SKYsAK/thc82OrPWwL0DHn7oRsn0K3zofjYM8Iu0fWPwS14b7909tKR8q7ED8jL2RX5foff6s6e4Etjwfi0NSLvxvrgJi3RpW5fcs+/Fl0iFl9MfPfP9bwZ2UEu5Rkwk/2dJq/0zWBwaTh6B2ZNQC9XEMudAj83RRNLr4UP/At/kYQP/I24kdzxNTjk89hg91Ocx1F49Hj8Mp/Xsk/gzm45XBMZ1ef+Opy1XRb/zdYN4A2Y1Yk8mn0nsdBTfsQg5Dl+huengAVCn+eRp+gJ5o5Av57Af1fl7F9lXY/CrUVeaj65UrjLsyuxg2zweSk4Tr8tyKQRenhqIn4Cv3plLpzjSgD7Qj7IcQFncid8cBicdToc/Bh689Tv4DVr3+xmXHzdWXjV4JfpQw5r3zCwA/yfOpy8twP8/474HNlcJ2fRmnO8BK4F8ff2y8hzGnzBn5wlMhL36/Mqic/bwoc5lz0n0BVw4w5s+zhxuQPuM2cxfpi7uPfwD190git3grufQyf28W/OZrgTvTxLHAo2Xswg3obnpUaQG2pMrPgyvO8L9Hw1ukQ81DUBfsF+cuE9eeng0tNgRgB3yX3xbQ3ZzwUbOsnZgKv+gay9DvoG7pU7T17Yyb3IZnjLUHj8JuIffPgx4u47N6jvdCqDia5zYApntLoi9z7kqKYyxz0H8K/EgEC8rVsq8QJjrewC/wXXvzkJrx+BXZODOl6TfeHXOi/kXm8hY+CDm+J/F+xgfchvG3m6gors+T7i6kH44XHwvFeYowfxTQi+Bp7QAbuIqkns9jm5lgXYV3fmK2J9rOezODi4eAc/Fu7fHfv8F/y3CbwL/uD8Gr3DvzesgL8lV/kSP4EX4XPI2HbEDy5DrNwIPoXvuYaeTeyEHjZjre1ZJ7nu0ZzzHnzP9tnY8YPwqv7wh2vEaoz/B/n4F8HyY7ORPTY+eCO2kw/2waFefw/8Q6/c04k5Oa8j6/CXb4n/Lj64cQdxLzpTvho+ZDbjoTtrd+MnDhErYYsVX8On7Yav/E7s15lcDzn/4Er8cAdSRM4kG+xaA2f/AZ9/4U2wzY7+VIJHTxHv4uk/nXccYOfeIXD/XsgXrLXDB8Lxo+8hw52MUdqB+P9+ctCNOYehrDEW+0Fuk/b7o+Mi1oDTXSAOgzf/NQediGGMMbTBz24kjhb84RQ4tKQVvgTevnaxP/E22DsVP3QvuoVcav2JnpLT6/09ujAaPwce9W+PXqH/Oxdh1xXIy+M3fl2PTR/CPq4J/cS3Eau+5uD9VSH+LQe/GsnnvzLISaaDk3HYE/HkE8ie78Yjhw23i2JO7tQeQI7pxK4f9yGHC7dLuUgZ+fHtV4iZ+GnnQM5Cj68EsCfiM87nUiT3si2RH5zFH9tNAgOeJv6yoZOH38MvjyZWuQB3ehC+2BC/xT4TyH1VrErMBI4+C9+r3x+9Rk/Sf4JPR7Fv+r62kRxCEjo1Fo6+kBwXOPSeA0zYQNwENrZYxZtH+OYB5NC9A3a0Ap3CB25Fh79agly2ECdPhxu9T54O39e4Khg3Al3Dr477EZ6BLtX7hnvbj1kD5//OPcQcBXD5efgIJ74S/HuiHznoJbwn4IzsgcQQ7NONjiaFETPBfTZOQLf2givDiEvhjsvAxvBX4a3d8Rdwy1mruVN+Fi4=
*/
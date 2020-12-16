//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_UTF8_CHECKER_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_UTF8_CHECKER_HPP

#include <boost/beast/core/buffers_range.hpp>
#include <boost/asio/buffer.hpp>

#include <cstdint>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

/** A UTF8 validator.

    This validator can be used to check if a buffer containing UTF8 text is
    valid. The write function may be called incrementally with segmented UTF8
    sequences. The finish function determines if all processed text is valid.
*/
class utf8_checker
{
    std::size_t need_ = 0;  // chars we need to finish the code point
    std::uint8_t* p_ = cp_; // current position in temp buffer
    std::uint8_t cp_[4];    // a temp buffer for the code point

public:
    /** Prepare to process text as valid utf8
    */
    BOOST_BEAST_DECL
    void
    reset();

    /** Check that all processed text is valid utf8
    */
    BOOST_BEAST_DECL
    bool
    finish();

    /** Check if text is valid UTF8

        @return `true` if the text is valid utf8 or false otherwise.
    */
    BOOST_BEAST_DECL
    bool
    write(std::uint8_t const* in, std::size_t size);

    /** Check if text is valid UTF8

        @return `true` if the text is valid utf8 or false otherwise.
    */
    template<class ConstBufferSequence>
    bool
    write(ConstBufferSequence const& bs);
};


template<class ConstBufferSequence>
bool
utf8_checker::
write(ConstBufferSequence const& buffers)
{
    static_assert(
        net::is_const_buffer_sequence<ConstBufferSequence>::value,
        "ConstBufferSequence type requirements not met");
    for(auto b : beast::buffers_range_ref(buffers))
        if(! write(static_cast<
            std::uint8_t const*>(b.data()),
                b.size()))
            return false;
    return true;
}


BOOST_BEAST_DECL
bool
check_utf8(char const* p, std::size_t n);

} // detail
} // websocket
} // beast
} // boost

#if BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/detail/utf8_checker.ipp>
#endif

#endif

/* utf8_checker.hpp
XA6bwhtgM3gbbA7vgK3gWtga/g22gc/DtvBl2AG+DTvDH2EX/X7XHVaEp8LWsAfsBHvBPrA3HAL7wNHwdJgF+8OZcABcCAfCi+FgXX85FD4A0+Ar8Ez4FhwO34Ej4PdwNPwBjoFV7fUFsCEcD1vCs2E7mA47wAzYC2bCAXACHAKnwWlwFpwLz4Xnw1x4CcyDa+Ec/S6/yYzH6Se0PO31AGu0PG/XdbBr4FC4CY6G98Oz4QNwKnwQLoWb4RXwYXgVfATeCLfD+3Rd3RO6TvI5XSf5qp4d/5Gul/wcPgt/gPiR9SXPwzj4IqwMX4I14cuwDXwFdoWvwQnwTTgLvgXnwnfgfPg+XAk/gKvhh/AJWEHXx36M/RP4OTwCv4Ax5MuXsAI8CGvA72AneAieAr+HfeBh2B8egRnwKJwNf4G50LLXC8MAvBiWhVfAWHgtLAdvhBvx/yg8CftOWBHugglabkeccYuO7wjP2g7Sq+VWQ9fPJmv5nQxbw7qwO6yn6y3r6zrIW+BY2BjOgE11/WkzeCVsruXYAq6BLeH9sBXcCrvo+tNucB/sDn+GPWBV0pQKq8FesBXsAwfD/nAYHACnwTMsbT/wejgUroBp8GZ4JnwcDoOvwRFwHxwFD8JxMNZuHzAOZsLWcCJsByfDAXCals90OAXOghfA2XAJzIFrYS7cAPPgHjgXvgTnwwNwAfwCLoK/wfNhLOVxEWwLl8K+8DLYD14OR8ArYSa8Ci6BV8NL4LVwHbwJboI3w51wJXwZ3gIXudYHPLiW7/6Y8J2xpWsFStcK/NvWCjShfqVh5t9Z+h2/9Ff6K/2V/kp//2LvPOCrqMEAfm8wREYpWpBRK6tMKVNEQSwiGwoIVAFboIXWQls6WFZAHKCiVkEFRAUH4saFuHHj3nvvvXBv/+/rd+l7r3elaMV1+RH+zeVLXi7J5ZIv4zzjmX+XCWJz//L5fw4iLcovLsqeGVoF8KfWAIS+zx+oiX6ZAVDAyiieNWu+rAtIiy+7l01ef8wznvGMZzzjGc94xjOe8YxnPOOZv3P837Nb19Dw/8/tAbDH/02ixv+Tdfx/rzf+94xnPOMZz3jGM57xjGc84xnPeObvHP9369mr+sb/taPG/xN1/P+CN/73jGc84xnPeMYznvGMZzzjGc945m8d/3frUX3j/+9HRY7/D9fx/yfe+N8znvGMZzzjGc94xjOe8YxnPOMZMbv+/P/Q+P/Pj/1D4/yx8cSh5/m21rPd7BF/LWwNzvhMKDv/f+AAzvMt++20WZlFWXkZVtkZpyrudMap6Bfe4uzS/nzs3C9nYUeeWc5308W8g03E3oN9AnnrEvsMYfObZYdLzyqeia/bNwc0XE9zNm1PcV9pn2nL3wXiN8zIdjPn4XYT96XI2mcGTxG/FCPbxZyH20XcN4TJThW/0Ua2kzmDupO4r3c8Y3wI/iniP0TdPutWcdeLOPuXOM354vmWw3cCCNsEniNyfnXbce0RdkY2v53G+bxW+TnB+4nMeVYc5+ZSf+XM3GuizqJO0kJ1O8eW34k4xzYl6hzb+lxL5RplwLUCcaebM2yniDvLuKdKHPkOZ9culd/hO76JkfVoUg1LzMPYfbCbsE/z+wkbXOpR4eyCSuqRhutiynCUuFc51SOV7WTq0XBxn+VUj1S2vamfQ8S9zrVuHCr+p2vdssO3dS3/izdElv82cbestPxHi8wpEeV/1U6W/7YNf678Q2GyHMp75Qbn8u5RU8+xx9bDNsMex+/FXFShvCUBHDieP1/Lu0TKOyOzkIzT8tZwrcPqQ2HBNOS1jI1/HfIIpzUsvixf2rnni9xTEiyRfJDfk2u9Td7wG9oeJut9lWo=
*/
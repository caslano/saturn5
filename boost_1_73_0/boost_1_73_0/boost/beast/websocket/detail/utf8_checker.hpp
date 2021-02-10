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
FcdpZRW5jzOTujhttz8s/ObjTu7IxEbswZQevIHKYQS8MoKNyWTOIwVCk2W1VtIV0cENSeksNhYcKsVchJPoatsIyyaeiJdBSY6l58EZ7VhqV5jNJwspR2bJK6tJiHKgRZmhmCOodIY2LA47byWaTEPAz5bm4DcDo8kMdEdLmCy7sBZOughuJ6vfZjcruB0tFqPp6g5mb2A0vWOyt5PpFZVekpgFfCwtOhK3IDelkpg1ml/uijudeAAXV9fL8SXrT96P5qQrSA45DqqAr1vKKErEwY6sUZcJqqFUa/PIoIu4xRPd11KnqsoQLpzPpBkWl0dT3B91k9A0K4fw6FeAk0Gz1aY+3Un9ADT8pw8dLLOLxlBblqmhfvGF8HVLt7wW/6okpUqMazYCPw5/OBueccZibbahqrQLqT0T6t7WyKzf+bsDML5ZvIMBY86bb6nJmNDB6/D1Opm9Pe/Qs8D7OgwJCrdPpJa+12eYzHs83QdmpINqAEt6z+klsFpssG5c4dzO2Ix98JoDjUNPb00giILibL5KbpbXi+no/XUEXabpBpmTqPloubydLajXug5Ti55xraVQlJ1U6tnYeYrVvnUfY4dJHg6YndD8YgcuKsPzDeRKTGUu0+ZJRKM9tB4hpCbeiG91y1Zj9keE
*/
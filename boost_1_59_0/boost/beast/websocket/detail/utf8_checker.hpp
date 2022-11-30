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
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
*/
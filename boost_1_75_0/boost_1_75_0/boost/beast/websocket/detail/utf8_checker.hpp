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
EThF9OG52ocJ/MNzwz/cqux6yQZalsBNLp+E1uEDeBdLYj3BPjZvKOmdjpK0NlVC97RNcKVd9pJNRMOKGj84CkzN6GiEqbKOOkwVst9Kv3hcr2Ed/zKYajqFwZRkaRdMfXhKBEwtZQnKy3bs4+pTBEy9dkr791TPU4zjd5+ijz8F6u5HdZ95yl82/iUdYPyx7Rr/vA4R4x/TAcZvwz6WdhDjv6dD+8cf08E4/tgO+vh3psD4qe5PUv6y8d+ZAuM3t2v8g1Mixn8x9PFlK/YxO0WM/9KU9o//XYdx/Jsc+vgrHTB+qvsZx182/gsdMP6Ydo3f6YgY//fJMP447GNLshj/D8ntH/+M5LD9n2zY/1B3P6p7WPJft/+TYPym9u3/pMj9nwTjt9D+T9L2f9If2P9JYfs/ybD/oe5+VPeZSX/d/k+E8Uvt2/+Jkfs/EcYfS/s/Udv/iX9g/yeG7f9Ew/5PgPFT3Z8k/HX7PwHGr5rbtf8TIvc/9PFlM+3/BG3/J/yB/R8ftv/jDfs/HsZPdT8T/9ft/3gY//F2jd8ZH7n/7TD+GNr/dm3/2//A/reH7X+7Yf9D3f2o7mH2v27/22D8x9o1/g9tkfvfBuM30f63afvf9gf2vy1s/9sM+x/q7kd1n2n76/a/Fcb/e7vGP88auf+tMH6J9r9V2//WP7D/rWH732rY/3Ewfqr7k7i/bv/HwfiPtm//x0Xu
*/
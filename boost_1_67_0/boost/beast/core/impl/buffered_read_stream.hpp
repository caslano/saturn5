//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_BUFFERED_READ_STREAM_HPP
#define BOOST_BEAST_IMPL_BUFFERED_READ_STREAM_HPP

#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/read_size.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>
#include <boost/asio/post.hpp>
#include <boost/throw_exception.hpp>

namespace boost {
namespace beast {


template<class Stream, class DynamicBuffer>
struct buffered_read_stream<Stream, DynamicBuffer>::ops
{

template<class MutableBufferSequence, class Handler>
class read_op
    : public async_base<Handler,
    beast::executor_type<buffered_read_stream>>
{
    buffered_read_stream& s_;
    MutableBufferSequence b_;
    int step_ = 0;

public:
    read_op(read_op&&) = default;
    read_op(read_op const&) = delete;

    template<class Handler_>
    read_op(
        Handler_&& h,
        buffered_read_stream& s,
        MutableBufferSequence const& b)
        : async_base<
            Handler, beast::executor_type<buffered_read_stream>>(
                std::forward<Handler_>(h), s.get_executor())
        , s_(s)
        , b_(b)
    {
        (*this)({}, 0);
    }

    void
    operator()(
        error_code ec,
        std::size_t bytes_transferred)
    {
        // VFALCO TODO Rewrite this using reenter/yield
        switch(step_)
        {
        case 0:
            if(s_.buffer_.size() == 0)
            {
                if(s_.capacity_ == 0)
                {
                    // read (unbuffered)
                    step_ = 1;
                    return s_.next_layer_.async_read_some(
                        b_, std::move(*this));
                }
                // read
                step_ = 2;
                return s_.next_layer_.async_read_some(
                    s_.buffer_.prepare(read_size(
                        s_.buffer_, s_.capacity_)),
                            std::move(*this));
            }
            step_ = 3;
            return net::post(
                s_.get_executor(),
                beast::bind_front_handler(
                    std::move(*this), ec, 0));

        case 1:
            // upcall
            break;

        case 2:
            s_.buffer_.commit(bytes_transferred);
            BOOST_FALLTHROUGH;

        case 3:
            bytes_transferred =
                net::buffer_copy(b_, s_.buffer_.data());
            s_.buffer_.consume(bytes_transferred);
            break;
        }
        this->complete_now(ec, bytes_transferred);
    }
};

struct run_read_op
{
    template<class ReadHandler, class Buffers>
    void
    operator()(
        ReadHandler&& h,
        buffered_read_stream* s,
        Buffers const& b)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<ReadHandler,
            void(error_code, std::size_t)>::value,
            "ReadHandler type requirements not met");

        read_op<
            Buffers,
            typename std::decay<ReadHandler>::type>(
                std::forward<ReadHandler>(h), *s, b);
    }
};

};

//------------------------------------------------------------------------------

template<class Stream, class DynamicBuffer>
template<class... Args>
buffered_read_stream<Stream, DynamicBuffer>::
buffered_read_stream(Args&&... args)
    : next_layer_(std::forward<Args>(args)...)
{
}

template<class Stream, class DynamicBuffer>
template<class ConstBufferSequence, class WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
buffered_read_stream<Stream, DynamicBuffer>::
async_write_some(
    ConstBufferSequence const& buffers,
    WriteHandler&& handler)
{
    static_assert(is_async_write_stream<next_layer_type>::value,
        "AsyncWriteStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    static_assert(detail::is_invocable<WriteHandler,
        void(error_code, std::size_t)>::value,
            "WriteHandler type requirements not met");
    return next_layer_.async_write_some(buffers,
        std::forward<WriteHandler>(handler));
}

template<class Stream, class DynamicBuffer>
template<class MutableBufferSequence>
std::size_t
buffered_read_stream<Stream, DynamicBuffer>::
read_some(
    MutableBufferSequence const& buffers)
{
    static_assert(is_sync_read_stream<next_layer_type>::value,
        "SyncReadStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
        MutableBufferSequence>::value,
            "MutableBufferSequence type requirements not met");
    error_code ec;
    auto n = read_some(buffers, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return n;
}

template<class Stream, class DynamicBuffer>
template<class MutableBufferSequence>
std::size_t
buffered_read_stream<Stream, DynamicBuffer>::
read_some(MutableBufferSequence const& buffers,
    error_code& ec)
{
    static_assert(is_sync_read_stream<next_layer_type>::value,
        "SyncReadStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
        MutableBufferSequence>::value,
            "MutableBufferSequence type requirements not met");
    if(buffer_.size() == 0)
    {
        if(capacity_ == 0)
            return next_layer_.read_some(buffers, ec);
        buffer_.commit(next_layer_.read_some(
            buffer_.prepare(read_size(buffer_,
                capacity_)), ec));
        if(ec)
            return 0;
    }
    else
    {
        ec = {};
    }
    auto bytes_transferred =
        net::buffer_copy(buffers, buffer_.data());
    buffer_.consume(bytes_transferred);
    return bytes_transferred;
}

template<class Stream, class DynamicBuffer>
template<class MutableBufferSequence, class ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
buffered_read_stream<Stream, DynamicBuffer>::
async_read_some(
    MutableBufferSequence const& buffers,
    ReadHandler&& handler)
{
    static_assert(is_async_read_stream<next_layer_type>::value,
        "AsyncReadStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
        MutableBufferSequence>::value,
            "MutableBufferSequence type requirements not met");
    if(buffer_.size() == 0 && capacity_ == 0)
        return next_layer_.async_read_some(buffers,
            std::forward<ReadHandler>(handler));
    return net::async_initiate<
        ReadHandler,
        void(error_code, std::size_t)>(
            typename ops::run_read_op{},
            handler,
            this,
            buffers);
}

} // beast
} // boost

#endif

/* buffered_read_stream.hpp
Km0ev27jvi78sQUXjkY+Pc3mNY/lbSw/JnY82JRxWsArtVb14oB2kDTcXebWc2hCT+4vPq1Bj464OhAQpbRXqq6xduqiKU0XwKvSCJ0/YZD5Lto+netXjwek/rX4SRZzN9dlX6HVrQtP96mg0gIB+858u1+QiIQCizSuW78r+yxdWYw62cOHMBnpuj7I/Fjbw3jEEKP/47zx9MpWa1zHm7LqzSdgyzLzdUp7Gfm9OKjzGG+miKL7NTO6uTkuZc6KfTpysQB7PEW4EQrK7NiGCj7dvLsvfTvOM5ZOcDsHS2Ib1WjxEzWP+h7txit8tDv+0F+/Ai5t3dtUZQArroxtUwkybpT5m4uL1w9XMqTo8J/78pkzo4kBNtRnjHHGIfNM8r8LA3ykYljh1ymh1+ixq1+PbdUEVCu4CGXuyzaSj0i5SZog5Gpe334F6/908H9akMnoKrG70IzibsMpdm57p1XpEWPjhgV4KtjLHodN2yAWDng2MvlBXbPLJR6zqzLrxIe6f266XcIYDDy2RQmt210r24ITxiCAcRN8MiN9w0EmkRkBeu//Jmyt9Yyrj697ZtiN2nzZzXPzp9F0WvpQ127ISmFjUKs5GaK9m/a7xh1buHckSVxibslHgAxcmNCeJ+FOF3CXRAaJ/6D+BlR4uG1+8lzMSwl9vm0NKEGxpLwkwWCrxeOhZguqTP9ZZkx2egec3U50XwYZtXQjJrPvbggiK8zPyT8e1xxGqknw4xOz+b6AN0Pf7OeGoQnvqiujDI3xtYWSkHzph+x0Qq8D+gJCucZe1UslfXm+EmN93H0yNGVnA9i+Yqpi0x4ihoNdTpoQqnALcuMry0VWt0Kq9nqGTWhGDquSWnAF7aozQakC79QJFMuk2P0HpI0dKMcYWS+Fzm13/3tcEw/elsHLJcVMCVUwJMkZGNGjRBb4vYLvskbrTxY0TXV1pQhY3jDvYVgB1625Urz6LqvnPTwZZTol2AuX3w9E8zx0v68tJBcNvHk35n6aKIIVxlMs38debQoHZ/wRPIOswkz2wbkFFRkEt520kFTqZzXRiZGvPbaFCxpkt14eZNpq2t/rRLSRckc8EbFoe4PlSGjGtY+Ch6Y2frwyYVrYbCmqO63fFPbem0oyPhOadH2OFm9fp25gCAzf0sRZ/0mNp5N9IV/dwkA6IhqatB1m1BsmCJgTuuW77r5zjxnRDsW77sIM/b5+/qiXfapqXz0587dWFQzmisqbucjfAjO3gEGgerHqh4tx5fPlvZGxMRLcr92sB52JKAHzsKnez/kTH5NyZ3QKDCBs78bPGkFnkXznVBsri6L6d62X99JNU2xr2Z58mMyMQqKaOKr5Fb3SLiFZA+ukAD1GCnqnTnZ7EJp4o2Iz7uJw0jXn/ZzoSxtHATsxtaTmh+J4J8FAUG0mNXJTMxXyURbXjJhBKO08aHj+cFSWqIpMSnXjbFzVJAVzZk3hwWWwXwSz4vK9jv/8Q3+M+ecBkwuNbGXYevhyDedxiGK4w3+VGsRlZ7kSpCoDhOLgqmj6Gu0bZFJbapB4hcSIhhm1PUO1vuA17g2wdizD0+xGtyBSyZp0NM7Xvy2ApdBS5Y3UuPmvvDcVtQhBovnoIXf99ESyvJVdbD7mpzdVkR5e6voHOu2T/n3pUXXGdRIlok6wQOCChIBvjrm159QWfr+N2imtaIXRD2YtO49h1dxFvPL9bJBI6zKHyoXIpMhs76+9UgN9IYLh8m/b/kpSSViSEiB/GBswFKEQILmSmi5YNisLn0hh6q8QQpcL9Ttf/movuhWP1kJmttpn/SiP92zu+XtJDNwocehWL2sG23i18hRGY/L5ntAzXVSc1uaWVUCc5a2HQulw6tJ21Wa8PFnk5aQJHZnwidMb2EHz9ZMkbBJRtPxj2jjn66YftRcom3+qL88an4uYBRcW064zSxprMJkusxKGOdTt9k7m0jWSAcYHpnzbO4ThQR35dcOTqcWSLR3Ihuq4OZEwKXbGrD5G3B36vkKZohYyZO3Y4yKCejMa8VJSUJhf1ZfN7cglw+DqMBQMnyvI9S4FU+FNs0JHpQgmrQYG8yzDBJ78iTnKO0CjRevuCJbDc3/GbwqAmoPXlSK5WzCqtAOm8xUct38/Y6CQ39vxiX1unFzsFwNvtMjIayqX69gaLfv2gNPh3Oaj4qJpSqPgjmxrWOjwFQ1DB+oyVFEKsJe7Gvq4rJz5UV88Lf8apKm89dy4x02XF2+j8RzRSnDRZv0ifVU7bXSMvyvH1k/QkTNrHMXqj9M7fvCNG49160l2DsV2Bkwe7poVT/4GZAuizSSGTDUaUsTQyWPE4hPK5F4kiK3wAmxHsaVVZLPQZN2/RogmkCerYdYk1MA1kUh6m2ioYz+c4lJ03tCeS8TyU6Juu95hec50AMux8pEW9IdLkM+xhGkZ5fvtIGv89JfiBiK5X0B6vX+J2v7oNP8pIxDYWlTUmkiZ/WG/OGMY0SBhRJXLUexaRH7EE2OoMXDGOCtf/A8Rvz01k5X9ZY5bhCF91TF1QF9+yXAH5MXz7HdmztDB/xYLLpC8ImfiUnY+dv/Qxh92ukXn8nuMezw6L3KWpnF2yBhQ6YLfx4Betw6JdVc0fshgAlRmzrBz9v7Evqf77GvnKfdmCRrBgxbhc2n/KMjia8pBSeU0Pkxz6AKmNc4dAqvR8cA3Ovxtn3HmkHAWbdM5oIA/LOH3chKN4VFKS9v/+gIhvSJhxj4PpmfKXaeJLGXJBEW09pGCeKfMsArQwSntB3jbBUpOijutn4dRaI2YbH/mxiGe+VU6IjA0dMU5zM8781vW72nhFvZwgJy+tAG1yNkP8EJRKeC8xHBUgj22H9NrZK2qI7DXP4bqJt2Y9cX7zNlrPDEb7W0rfjGxcGd47tU2mK3r7SkgEG6msASeQqXqOz0/jsTG9fZgS5ASX/fbmx0zhsFm1adoxA6Es8ziDR9EY1NUy5zRCeoIJw89bpYo6vZ+CnwcWxKgyGlw+Yi5PGX8thoFIDjLrn705tO4m3go1yz91e0LK7cnquLUB8y+YT6xBPT5tdHhPQbK7mrYRijC8TknxelIsOVwNa2QQDduhJBqF+1RQZRa7MWusDkHd7+jt5t/pq1FJopYwKnJTVYuQNMgHXHkFQJy+Gl+c3dR5FH2Or8WTbyaxMGvDCQGQ1hQ2g28EDTNYPO5whHqvWNWiy/OgjgXEWWKZJ9qD+HRVgzKFpmtI8r2ot/wvz2Tu3BGgRTiYkhwhCkyKKzNV4pUD91j8+k+kSt7LtOOglpnPDWP2cll9bi11OFUtZpXFga99b1Mh0YGMROGUnLSrqzdVMG2EQKBxsoVLhfChYMY4qfy3DmssrD3pz6ZlLzo4WFGi8B3RIXF6zfgpQg5dl5HPZ7rdERx0wpa1QaOA7cMojitro/JtPwiMSEBuHCsqA9gr4TWpPsXzvoDARmodOqfMMAG+V53/vojarMQkM4Y0KTZeGrJFkJHfQjFqCVBWFWyRQZv+Ts0CE9fK0IhOCzpNkKgSZJ1MmX7uw7u3zDIbApOPd3ecLbza/YQECoJgCII1qDw9TLHvnFAbLjPZvUJm0F673Ic6RppZmsSF0WXXi/+GSUqUBrIgvLxwzVL14gEYdNDaZZwlgJdLfAmVGeLtyDYGuYAMO/9c64+TGdgPTkBEnuEWhhFZBHo0TBFDnVR0Pt5B0EpuN+UMwI2HIVXA6Qvxho+PUZCm3k/GB8kIFzzDZ/J9f4Lc5CLNQKg7MPCeyz8Aj4Xs1iX16MC7Kh6Exc5YUOT36E8AJQaOnlgRSp4MDfU64WxoLAkoIaA2M5NZxYxx49ra9+t9x1hoSUi3W5U6dthxE5+dyOGotnXlsMrveOxgzEgbAHdIhVFRSSghVU+ZyrRUWvOlMCuQUXJNXWSikb9gGvCOcbae+nj3FKfU1BkTGmeDQX1acIa0UqxUUdaZFt72oNL7Th/C0B2xDaD0HnsJfbLJycMQMZKg2HxRxjOYIkpNcpDMfznbBnJOFyTwrpZ2US036alG0peWrkO5rElZY1I/bOIwVJeGZUQZ3NEN4HV4IbmeomU4X4L5/AhcTvxuqumZm1j2zWl/rS9O0XbxiR8jMGTayg8c3Ol2A6zytYXN3xsoXAUFRYckKA7w92cU6/FfiYRptjdlxW0K/BxliBSWK2slbPHl++JbvsDLBN2VkPlBNKX5Dhtn7it+len6KxxoyA0ZVwm9ErrFBmjOaaRLW0YqagyK4xWqUxrjfm61fxk6pHKMW7X3IJ0v1HGRyvySjG5mFrgHLi0hHCbp88zBnwt+xHN5Uw0hLNLHSeKDYe599Hr/8JSNSeugCnj1gu584UczrsjHpTVZIh6VZlUlXvDo8xDM08KSRb48vL7y+mvREztYX/AwVJzm9axpLN/rKrj1lUvMqRy8vDJqdaezz8tfLfFzUiU7Wp+/WbMKNbHevyCPgz9Q0dIGEJASgTmdBX2Xp+67TSH725BA+rJazr7kr9gYR9dsVWhU5RVpl/WJHLYutTV1BqZrE73rieGa6KzM7m7nw/oFnO/+vgtAnFYApg3Bc7TtZb/w3VJi32lMKz2Zc9jQpVfwEtkg4t+VTRJMxukUVCYLWXCDMt6nuX3kTWGK5qrMbWJLJcnzRjPlMMS66sVRLVxhL4yBXZdQ3ZlsGi5UD70iRWsw0wV8NZfXLtjUGqzprQWO0Y4qtkCWb8sAI19bmqN/+0WRJ4YMiEsbCi9rGoV0NRZJKrhs0EfrUXDvktdqGSIxfD9hfTaQHpzYzfP79d7GbKAFeZt21QJpzEf34i+RrPXsI3fsn6nwJDlWcs5u4hPYNXDnbAz1YQGUzMLdr53Br8nGp2Y+8chZcAcF8Qfp+jJrsoYOs4Qltcqao9JduydxOL1ArSCS6aRw/rmsfjhb6jAiuFtOgdnY3OGnHVjydYmPsIUJ1FSs7god6ySbLeX5poWMDWDzbAC23/F0WWRuyvV+eaM8QAmok6SXP920vtWCM2O3EzQyBV2Asi5IEg2e/T4dnrW9LYfs00pcnPxXAQQZBHQdLU8pt95Qex9olPhOnI0er/es65qlL+ykgm0E+mzsq1mFONF8sJ8JffbSsfXM9WkISNFXWNJDkz6Nh+3oEEi1WkjkgifFWEzoUOXod3xs+jQAHdXei6e44tw5+lgg8Bt8Jcql6hlusdeuz+RbKOl3wlycxJkjb62fr/Zryc0Mjq7M37vfWjje9WF1SHTeAQTb+kHNUeN5+Pg119RIwvUEmbPzZva5s2xvxMAe0slIGyEvlA2rFm/V1Ve7r+gef5bFHTt4/8E1ClzEiAKc4FIHgFGM2/Sh/e6nR5lYDGXJBzPVpeicP7MWtbD1g/m34lBzFkg5/Wh0L83Dh9ykdLw4Z+PeGja13NbdVMtbVlvTC9jpIYMtjGlIt4q23YzCGKNdZLplBGrOJEebxN4/28uKdl46T2Jlre9IL2AwCIYExATCsZ0dxsMP7hzh7rOtVkGU+9GqzkUa0AmIT0E2EPGrtxXA0FA3idTgXSRq6YiF349x3Qt8dQtM4KJP03PPF+2dcTbtZRe7O2K9hLtGiXY6EhoULVVP0oCpwe7Zb7mmYPqBTuYXFFhx/GtbFX+YQI1CyeCiEgXDxXUiLHfPMgDZ4dYlTNjp0u112p5yXaD8I0xRimsIDTA3RpS75/ZdlYIPCN9uvfhLY/V2JWP738qRAW2nPUrXpFiuOsht6++5ip21xOqJ560M3lG5vHw/LI6YndaODVaVC/zfOO/rzY7FbASZfUH0TlgCpf2QQB5T4+ROHzR4Py+qbEhpmTc0aas+DoGqjYSKGYjWFSDi2nW1npX5cnQhf0ak2oxoRAyyNsmwnPzhkmfTYfTa+rDh3SCqdbqOUmf4pSoHFtWdZVglLoTw8TLleCe78hz+DacsYepRJCtKOrvPGplScD7i/Hv7TOZWxbpo78eClXTJjiarZRzbngTdUkO3RROVpFi7EGVWl7g+Dk9bg8FDFafXNgbENnJDMgoxY3ZztvPwhZG7non8GV7ewALUNNgoGgQRN87W3P27wGuG5bypU8UKNgDmBU5x3vtl9/RRA7oOw+cqKHajqZ7M4oqnv926aOMus/2z0rDhWir/b3CiIvm5oJiI7CUsseQrsIroS72EBoxKLAUXG/uqhKr45tmzW8xpG6lVkt+qp30mUvSmGcWWicAEBRrwV5x0tGc+fnFug66KB5Rv+UsRRRXYPlxPnudhnGQIPxLcQdyprSLhNg7j4+nwvtNxBkKYU238dDnhTcVlYTQpZubFX2qnYtywqICYLpkJdfo5wTi+GhLy7lS4GH6ZDReE9Pr3svKZTe/vcMYRY47Aq88jG47kx2RMpOCf807nUdyvWdnSSY+sVLeF+RW5IazI8zgSFyXGJ94ieIO70mcJdmycWaMEiUXrix/AYgyhy1WUv/tzFTRRyeRv91aMrT8kxY8COlvb/7lltRneL6aWrPZKrQ6bnv/yp8nSIdW2XIUgJ0jYsYv2kvV4IOyeGtFWX5bjG+RwSuLCA5dxIqx7Hlf/x1rYlOGkJQR8Un9IH/AtZPtrvPRFbRYtIqy8LN8Ijx0GRuY3mVdWrdlDWwNbL0O2NvZugMcOcPTQzfFLBDnM5QyMqCb1Bu5awpQvLMgeA5kscjVnhUnk/GueAUcUHz6Fj7d9hevegt9g6o7LqAmyC4S0UCGeo8MpuPi5XDUmPpPyzlci6XlwuLjafrHgPQ/pwiII1jYr0hMLKtgRqekbzolGUrJSvU0GDu+849W6Mb9pEUnCpkmn4EM3lb0clNudhItVuzHjyTRMtgTWiWDTUIO0fYEJlC0KQdrCOwWdjhYL22zfwA3HrZWrTOXMXQTmrcoZ4yfk0sz+fpWUCnY/82h/9wiiv52unimT4/+wySgaLiNd96v3fj1Vcu/XjFcPG5zMYwMM/1RhAuL9X5/Xxwx2dMdkQSKp6Le+Gk6s1xrEZvkBelkqxoud7yQSU0RBKeEawGPUBYEhf0O+PEVqzzPUOcIiWQVmURgXJVNNyFNCt/ZrUSvbuRlAh0AF/Tdaprpz85T2lhKVhfCQpG0dy+8UJV5fXy+7cq/BzsVdqCxRlJkg30sSqlzwxkcRDiejLW5C/LHJprX3duLef02Iusg/wBv53X2kRHnCmXkyft4lXD1Pljl4tWJKelUHsmeOqA0ruNKugpgQYIo1DrEHPDeHrcBI7qWEwCpG/N1qQZ0ZAAA4B9929Xwj0yu7Z91xBHJq3Bw3+ammjy/WMNHOFLzB6tGjcoiQ+6U+ESpVNjJEPAEG/vnM9txeGPxtmTqO0M6XSUf2B9t6N5ZehrPgfci0B2AIvbM4O21duqHD+CVLe4qcJB23MU4+ysC3eg7D4abBEOHCHrtnekKmueLneeEBqGZ8l20XjinmEqZjRtjWjhQ+X36GVCzLJoVAXhm1AdQOaLw31ydXCaEaNRgnOaeyqI8PZ124yxpjuB8VCsXqd+nywc1qLQdBxET9UF+H7Pa4Io99UiVGbC3K9/cN8wJSDcpwe4+hwgdPfrNrYpPr663NQiddH7L0dZoc3tfWo6kfapOqG/qsC8AvrDS7/IGck4dE8DVWhytmK8JWNsG86gIPQVfnrHObi3+qFMkGkgGSVcNWrPWP+aK7aox9nbB6vqdOn+favLxGDhC57zp+IT4rXQzGlY3Mr6NtRuHFiw7JxbqBaO6nMtTyPiBntBnGtPu+/jWjhIl66Ue3FEDJWvJginypLu14C0PbFVvwjNkoQTPWWmGlz0LF0zHsMnXhsIuJmayp/6QvvhBQr33tH4fAHoQ67o7aH/XQf8dr8jXX9qTk+8EOCpAAdxLb9wLnvfV1fVbR/fBYyKJRtPmczE5HlAvV6KiHiSiIr4tIWKFoC7ob3JnCOy3zTtOB//p1Ao4TmjlyYh0Vt9lx6FJGKAbW3wz/3ABjO7I8lNeE0BwGM2+thQn/QBEY2xeCkfPzrh/VHFQVLBBWaR8w32PnHW6+SG3HoFLVSBxy8/e6BfTdEO/W7ElCHN95Hc0Xpc17HN07PMye0586p1ktEzA4R5BgqbAqKYvO5h0WTPHfSVIHgBksZ3mlOrpmEcaFRTuMkqVGpQLsxzbU0ZVOtTh/hDiWdeMINaarcVue83Ouv/Z7CC1hpfJEE0uD2K3NuwmGFpMSgyCQmkoR+O4gxj9A8dDUQ/CO7hlooizjMUaNZPvvWbvn8BgHLMqWc1mQ3c8KkZcgwZ3K2EEN1J5fWxhnzqW5Og12zgjsoeyBJlbm3Y2CnwHU0/quvbYTfjcSqYywwUKYycFDunqtk13vXrTY2Cp3sUETrRl4xZUFFu05IRG3YRbe5npc6heEF1d0EKjwPAB0gtzsFKfwLR4vA7CiaGJqOA1KjqXfGeUJxvzI0370cQ2HAHU+qfajsmPfZBpF2zpQjTKgzBUhAka9GGxCrZR0Dp8/vZ1YVPXCfCSLwe2T+rgLj2nIXtQxr81+/L1+23MNB+9Xv3w/ViXi1XSW66d6IIq3giSawYe2HTlTf0ZqsAOsbqycNFx+dkR00yQxS8yaXSVE3zyMi++5RGD27Pr1aUDFc0Jo16nc7SyQPusZKtTXwkIr96WgQAKLPXTFJohIYVRAdfwOs70ZokBj3slt0uvZ+sTZOT8sdBamnxquzXNsLoDoVKmIVEHLb7ycphN1HSagKqxvvUJjeI9F68CU6r1rC/ttFGGwzZyTk7Kqo9Qfmnvt3Hts2kR2zCyLSIc1Lerf2cql/KZ9jU1dr0y1LzZGc3MQjNNxwJBAKim++LA8MOn4l6vjh1DQrqioV+3TGTGOnooPeM3Ui6y60JsmaRDx4vj2X5K9LpfTB/zIupnYZDVwzwszbJ0Yt/yX443t9XTnUEfDKVn8cMhjcSVRYZIHCvCGyPeGDOwQQwmq9WCZ/ggmmsmPFpBlAmc4QIaUfp0utPp2Z5XlXRd5dqrQsfmX6wKVjylLNK1ArUr44LDU8pyO3HAG9unjcfrJE7fZpLZlcly3THmtHm6HHh9abQ+pRidD3Mi69s7qIh1+PSQ89siZWIO73OKxkxJFSf0DfUf3SZ0lxbhUG4Nm5NBimXgwc2zWx5ZGpTpI2oln6XtUaPnQVDp2bsQDmXIPUepgq9VNYzIYCunC7vj0DU=
*/
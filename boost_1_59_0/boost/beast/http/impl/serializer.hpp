//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_SERIALIZER_HPP
#define BOOST_BEAST_HTTP_IMPL_SERIALIZER_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/detail/buffers_ref.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/status.hpp>
#include <boost/beast/core/detail/config.hpp>
#include <boost/assert.hpp>
#include <ostream>

namespace boost {
namespace beast {
namespace http {

template<
    bool isRequest, class Body, class Fields>
void
serializer<isRequest, Body, Fields>::
fwrinit(std::true_type)
{
    fwr_.emplace(m_, m_.version(), m_.method());
}

template<
    bool isRequest, class Body, class Fields>
void
serializer<isRequest, Body, Fields>::
fwrinit(std::false_type)
{
    fwr_.emplace(m_, m_.version(), m_.result_int());
}

template<
    bool isRequest, class Body, class Fields>
template<std::size_t I, class Visit>
inline
void
serializer<isRequest, Body, Fields>::
do_visit(error_code& ec, Visit& visit)
{
    pv_.template emplace<I>(limit_, v_.template get<I>());
    visit(ec, beast::detail::make_buffers_ref(
        pv_.template get<I>()));
}

//------------------------------------------------------------------------------

template<
    bool isRequest, class Body, class Fields>
serializer<isRequest, Body, Fields>::
serializer(value_type& m)
    : m_(m)
    , wr_(m_.base(), m_.body())
{
}

template<
    bool isRequest, class Body, class Fields>
template<class Visit>
void
serializer<isRequest, Body, Fields>::
next(error_code& ec, Visit&& visit)
{
    switch(s_)
    {
    case do_construct:
    {
        fwrinit(std::integral_constant<bool,
            isRequest>{});
        if(m_.chunked())
            goto go_init_c;
        s_ = do_init;
        BOOST_FALLTHROUGH;
    }

    case do_init:
    {
        wr_.init(ec);
        if(ec)
            return;
        if(split_)
            goto go_header_only;
        auto result = wr_.get(ec);
        if(ec == error::need_more)
            goto go_header_only;
        if(ec)
            return;
        if(! result)
            goto go_header_only;
        more_ = result->second;
        v_.template emplace<2>(
            boost::in_place_init,
            fwr_->get(),
            result->first);
        s_ = do_header;
        BOOST_FALLTHROUGH;
    }

    case do_header:
        do_visit<2>(ec, visit);
        break;

    go_header_only:
        v_.template emplace<1>(fwr_->get());
        s_ = do_header_only;
        BOOST_FALLTHROUGH;
    case do_header_only:
        do_visit<1>(ec, visit);
        break;

    case do_body:
        s_ = do_body + 1;
        BOOST_FALLTHROUGH;

    case do_body + 1:
    {
        auto result = wr_.get(ec);
        if(ec)
            return;
        if(! result)
            goto go_complete;
        more_ = result->second;
        v_.template emplace<3>(result->first);
        s_ = do_body + 2;
        BOOST_FALLTHROUGH;
    }

    case do_body + 2:
        do_visit<3>(ec, visit);
        break;

    //----------------------------------------------------------------------

        go_init_c:
        s_ = do_init_c;
        BOOST_FALLTHROUGH;
    case do_init_c:
    {
        wr_.init(ec);
        if(ec)
            return;
        if(split_)
            goto go_header_only_c;
        auto result = wr_.get(ec);
        if(ec == error::need_more)
            goto go_header_only_c;
        if(ec)
            return;
        if(! result)
            goto go_header_only_c;
        more_ = result->second;
        if(! more_)
        {
            // do it all in one buffer
            v_.template emplace<7>(
                boost::in_place_init,
                fwr_->get(),
                buffer_bytes(result->first),
                net::const_buffer{nullptr, 0},
                chunk_crlf{},
                result->first,
                chunk_crlf{},
                detail::chunk_last(),
                net::const_buffer{nullptr, 0},
                chunk_crlf{});
            goto go_all_c;
        }
        v_.template emplace<4>(
            boost::in_place_init,
            fwr_->get(),
            buffer_bytes(result->first),
            net::const_buffer{nullptr, 0},
            chunk_crlf{},
            result->first,
            chunk_crlf{});
        s_ = do_header_c;
        BOOST_FALLTHROUGH;
    }

    case do_header_c:
        do_visit<4>(ec, visit);
        break;

    go_header_only_c:
        v_.template emplace<1>(fwr_->get());
        s_ = do_header_only_c;
        BOOST_FALLTHROUGH;

    case do_header_only_c:
        do_visit<1>(ec, visit);
        break;

    case do_body_c:
        s_ = do_body_c + 1;
        BOOST_FALLTHROUGH;

    case do_body_c + 1:
    {
        auto result = wr_.get(ec);
        if(ec)
            return;
        if(! result)
            goto go_final_c;
        more_ = result->second;
        if(! more_)
        {
            // do it all in one buffer
            v_.template emplace<6>(
                boost::in_place_init,
                buffer_bytes(result->first),
                net::const_buffer{nullptr, 0},
                chunk_crlf{},
                result->first,
                chunk_crlf{},
                detail::chunk_last(),
                net::const_buffer{nullptr, 0},
                chunk_crlf{});
            goto go_body_final_c;
        }
        v_.template emplace<5>(
            boost::in_place_init,
            buffer_bytes(result->first),
            net::const_buffer{nullptr, 0},
            chunk_crlf{},
            result->first,
            chunk_crlf{});
        s_ = do_body_c + 2;
        BOOST_FALLTHROUGH;
    }

    case do_body_c + 2:
        do_visit<5>(ec, visit);
        break;

    go_body_final_c:
        s_ = do_body_final_c;
        BOOST_FALLTHROUGH;
    case do_body_final_c:
        do_visit<6>(ec, visit);
        break;

    go_all_c:
        s_ = do_all_c;
        BOOST_FALLTHROUGH;
    case do_all_c:
        do_visit<7>(ec, visit);
        break;

    go_final_c:
    case do_final_c:
        v_.template emplace<8>(
            boost::in_place_init,
            detail::chunk_last(),
            net::const_buffer{nullptr, 0},
            chunk_crlf{});
        s_ = do_final_c + 1;
        BOOST_FALLTHROUGH;

    case do_final_c + 1:
        do_visit<8>(ec, visit);
        break;

    //----------------------------------------------------------------------

    default:
    case do_complete:
        BOOST_ASSERT(false);
        break;

    go_complete:
        s_ = do_complete;
        break;
    }
}

template<
    bool isRequest, class Body, class Fields>
void
serializer<isRequest, Body, Fields>::
consume(std::size_t n)
{
    switch(s_)
    {
    case do_header:
        BOOST_ASSERT(
            n <= buffer_bytes(v_.template get<2>()));
        v_.template get<2>().consume(n);
        if(buffer_bytes(v_.template get<2>()) > 0)
            break;
        header_done_ = true;
        v_.reset();
        if(! more_)
            goto go_complete;
        s_ = do_body + 1;
        break;

    case do_header_only:
        BOOST_ASSERT(
            n <= buffer_bytes(v_.template get<1>()));
        v_.template get<1>().consume(n);
        if(buffer_bytes(v_.template get<1>()) > 0)
            break;
        fwr_ = boost::none;
        header_done_ = true;
        if(! split_)
            goto go_complete;
        s_ = do_body;
        break;

    case do_body + 2:
    {
        BOOST_ASSERT(
            n <= buffer_bytes(v_.template get<3>()));
        v_.template get<3>().consume(n);
        if(buffer_bytes(v_.template get<3>()) > 0)
            break;
        v_.reset();
        if(! more_)
            goto go_complete;
        s_ = do_body + 1;
        break;
    }

    //----------------------------------------------------------------------

    case do_header_c:
        BOOST_ASSERT(
            n <= buffer_bytes(v_.template get<4>()));
        v_.template get<4>().consume(n);
        if(buffer_bytes(v_.template get<4>()) > 0)
            break;
        header_done_ = true;
        v_.reset();
        if(more_)
            s_ = do_body_c + 1;
        else
            s_ = do_final_c;
        break;

    case do_header_only_c:
    {
        BOOST_ASSERT(
            n <= buffer_bytes(v_.template get<1>()));
        v_.template get<1>().consume(n);
        if(buffer_bytes(v_.template get<1>()) > 0)
            break;
        fwr_ = boost::none;
        header_done_ = true;
        if(! split_)
        {
            s_ = do_final_c;
            break;
        }
        s_ = do_body_c;
        break;
    }

    case do_body_c + 2:
        BOOST_ASSERT(
            n <= buffer_bytes(v_.template get<5>()));
        v_.template get<5>().consume(n);
        if(buffer_bytes(v_.template get<5>()) > 0)
            break;
        v_.reset();
        if(more_)
            s_ = do_body_c + 1;
        else
            s_ = do_final_c;
        break;

    case do_body_final_c:
    {
        BOOST_ASSERT(
            n <= buffer_bytes(v_.template get<6>()));
        v_.template get<6>().consume(n);
        if(buffer_bytes(v_.template get<6>()) > 0)
            break;
        v_.reset();
        s_ = do_complete;
        break;
    }

    case do_all_c:
    {
        BOOST_ASSERT(
            n <= buffer_bytes(v_.template get<7>()));
        v_.template get<7>().consume(n);
        if(buffer_bytes(v_.template get<7>()) > 0)
            break;
        header_done_ = true;
        v_.reset();
        s_ = do_complete;
        break;
    }

    case do_final_c + 1:
        BOOST_ASSERT(buffer_bytes(v_.template get<8>()));
        v_.template get<8>().consume(n);
        if(buffer_bytes(v_.template get<8>()) > 0)
            break;
        v_.reset();
        goto go_complete;

    //----------------------------------------------------------------------

    default:
        BOOST_ASSERT(false);
    case do_complete:
        break;

    go_complete:
        s_ = do_complete;
        break;
    }
}

} // http
} // beast
} // boost

#endif

/* serializer.hpp
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
*/
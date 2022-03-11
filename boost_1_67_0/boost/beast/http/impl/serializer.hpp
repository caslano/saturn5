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
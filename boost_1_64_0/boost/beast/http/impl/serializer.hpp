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
mt9Kze9azW+15rdGv5ezDtyufOYdymO+XXnMd4HrwcfBDcp/jmh+d5r5B3URSvyOzybN7xbN71blbV4JXgi+E6zU76jUgleBxBH+8y7wGrXXdeDd4PXKw74B/D54I/gj/e5Rf+69w/2dpYXB36/J1vYyQNtnDtgbHOiK36Hx+/rEz9X4Q7S9DQXD4LBYfBpHcPzRGj9P4+dr/DHgvp7CQ0xxEI+Tg9hZ/uHJ/FZKd3mHKc7hm5tzWLsWviCyH3kNKaiCK4hsQfYgz1SluASpI3WkjtSROlJH6kgdqePkHm8c/1/jCAWgexyA0VZY3u91XGiv50Rv4SRvv9Iaq9eP+l1v4Pvz3D8XnTtYK94l3xFomlFeVRepJe3hen63c35GkV6KxrmTa3vlGuU+rXwDayLCSRiTh++6rku/pO/YL0FGIUuQ+4hXfLqsS5dvWscafUPLuvL66Ludj8s+KuUrW9iNkLUSXYN29CeZd1l1Ep4gccZlS5xzGps2VLZonKUmzgTzfmudhKdJnDFjJU5pI69EsIF5p1UlOjMlXGbSGCdxIhkSZ0HTZaVsdxjb17BCdCbru00nTr7ZB2XGcPN+MnAflFx9P0n5WQc35TfvKSkj500ZzXtKysF5LYeeXw2SV8678sq7nqskX/hA616Z0539bnrqOwNde8oAi1nzbYvW0do6vERqa+oj1Lv7/YDZJ/M7ovcn67dmn0wn7jDW8y6R9f0nWLD5PpJO2yhAxiNZI1nXBH9Fw5gIXsXaeiE4CZmMTEGmIqfkJd9r0dnbkrwlcCl2x33DoFR9Yqwz4n1iTM+gSXJPdrBpxza1xD/Vzm//rMKsJRk9wr0yw+nh2B6SByjXOK7H78ecq/YZIveZizXSrSJE9pokrm32bxP3oQHE6MReru49fWYoyWeBlmke8vNx1LunTFocrgXtFf3uM6L9Kp9/NU9anmi+kuwpqvvJKp9G+QzLkDzkHORrtLX2aJ60pwf0c83P30V3nLYjJ+7k4H5udMaaPvwnLRPvc+kL7n2ry1fUNG+sd+JKv5upe65S17Ox6UjKMJbMh0dOdvdfqbNj9GHqR/tkQB9endiHpU9mz/T2Sa1fQ0qq0fotR3qiUyz6rVqxOhw3e/vlcLUdutEwV0/lbiWI7K+vNglJHeiIzjFc62CFxFth9aWtTuavRYjaWtPMkfb004nm2wXS1stc99T7xe9zLnp1iXqm7U3H9qcjM46jzzv72VIuwqZcZt9J8mv2k9dvVLj20PbaP1vff6/R9eeLEXtM3Ou1f3VNc0tT41bfd8KqO8ixuXybII16vRGZKd/cKAqn5zCeZPUxbW1WXrStOboPI7NFd5jqhhN0c1X3IDJHvgXQ11Yc6OjNVT3Zi6sL9nTbY5u+My9F+mvffhV7Fs/y2qPuMiwS1x5zxR6Obqm2R29bfEXaUjS65Ro7V0icOaYtmnY4y78d5mg7dO51amIbFJ06r44Zy8/EVvO70fYoB+FoObra9py97qr1mwTbkIHI5coL2+2xtYd44dpjjqHfzJucOLnG1j58MPNb8Kjollkz0FY7a/xhgZywMqOTJ/egrMfkgl0Qp1+iv023kyf7uwKSHx3HXxS92bS3kIsnRr5dvxe9ZwvvwPDCiqi7F+inZ4MbOvGbmuOpR7Gd1qU/N6zYn2NDOYI5NlG78m5thHeMOapkjTat548jj9tjvJSptYUmpAO8fOwisa2rDapF/wYrQtpa75pGgTXB+e1Lq4hPb+LcuRXT+SfSSFrDdQ+/6yRePSmNpr9lWhfxV462havk2iR6Yp60hyekFLFxNle5e+tFbxm1MoT3yIMMh2+7nE/XuoqO88XIDBs70ec=
*/
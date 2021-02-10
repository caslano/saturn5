//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_SERVICE_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_SERVICE_HPP

#include <boost/beast/core/detail/service_base.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <mutex>
#include <vector>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

class service
    : public beast::detail::service_base<service>
{
public:
    class impl_type
        : public boost::enable_shared_from_this<impl_type>
    {
        service& svc_;
        std::size_t index_;

        friend class service;

    public:
        virtual ~impl_type() = default;

        BOOST_BEAST_DECL
        explicit
        impl_type(net::execution_context& ctx);

        BOOST_BEAST_DECL
        void
        remove();

        virtual
        void
        shutdown() = 0;
    };

private:
    std::mutex m_;
    std::vector<impl_type*> v_;

    BOOST_BEAST_DECL
    void
    shutdown() override;

public:
    BOOST_BEAST_DECL
    explicit
    service(net::execution_context& ctx)
        : beast::detail::service_base<service>(ctx)
    {
    }
};

} // detail
} // websocket
} // beast
} // boost

#if BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/detail/service.ipp>
#endif

#endif

/* service.hpp
uIV/Xb47VbHimjzpqBJMGs8b8gnH9FuqpstHwqqJaJp5BJrmPPkTVeIZoLXSpgvHthPCN0ejDLzmlyirNHot6+NGwxBU+SnHADJMn6cv4TtzL3u+9/Fv2UkVrHa0xDU4UTUp9uxgICk4k3X1afXaF10yAB8oFE2BByz0Ud4AAS+9D94/UEsDBAoAAAAIAC1nSlIb7WyliQMAANEHAAAmAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9pbWFwLWZldGNoLmNVVAUAAbZIJGCtVG1v2zYQ/u5fcXMxzDZUK2k/bG2cYJ6TtUZb27AdZAECCLR0irhRokZSdoym/313lDRnawv3Q5UXShSfFz53VDj4flcHBnD0ivxfRBeNHrEw+k+M3ZdXR9Ej1D+EuqPxmEgIB8hj1IfjkEfoeUjUqIz4PoqOCd2xN/4XMvIu4luaIRgjJ7rcG3mfOehN+nD66tUv8BxenLw4CeBSFBIVrBwWGzT3AYwSP/NrJh4ehhYvAkAHQg0bqnUmLVidup0wCHSvZIyFxQSEhQRtbOSGHmQBLkNIpUKYzBe309mbAHaZjDMm2esKbKYrlUAmtggGY5TbmqMUxoFOCU7kibSOCCsndTEkbQSHJrfMwfJCWQ1iK6QSGxISDjLn
*/
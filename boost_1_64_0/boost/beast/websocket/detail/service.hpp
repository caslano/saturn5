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
1de6rvyH+80KgwtGCxfFrbr8PdhydNpUY/PVNLTEZAs3yw2cFFKPn6gsUl5OL56j/G9v5evL3XjX/3zJGvUCIw9cUZr5TCM+MDVFjdI8NOnWuYubMirJ76G4g6Vf09GruovyRZ+26OWnrd9kSt3c1bQF6DOt9UW2TFwSvvTtUIQOFKwxL4GDVAL72OCvPYKjP2hRFXQ3q+MU2seDskeErL3FMkVpjaRzPc8laU146oQaEDBtGNHq5IREI5OuTibhm+HY0Zlx1DqoJWPoGVHDmsY3ZDtMp118gtShFZESakT5WqFGdAQRd6BJKUenqPfulG3Tt4i9r8frXZrn18aux1kH3AGFVoAdq9MozD4hdGSmvqx+alQmLz+I9B6oQZ4kdwr5qOgS+0g/bnUSh3BBsNP9IzCVALii5FKMojwS364P1mnLQowAtAfaYccdnteOWk0WCZjTopl4sWf5abAEdqryIQfPBu1IEVmTL1ZBumFH5BduG5yZ4GphaZizH3AYOqVTLvT4IofaJKZ6u0u+cnrUhY2VCxP2bLB8hAPRauasj+QY9gxB1M0dEA==
*/
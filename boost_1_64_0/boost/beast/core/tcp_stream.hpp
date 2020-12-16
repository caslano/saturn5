//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_TCP_STREAM_HPP
#define BOOST_BEAST_CORE_TCP_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/basic_stream.hpp>
#include <boost/beast/core/rate_policy.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace boost {
namespace beast {

/** A TCP/IP stream socket with timeouts and a polymorphic executor.

    @see basic_stream
*/
using tcp_stream = basic_stream<
    net::ip::tcp,
    net::executor,
    unlimited_rate_policy>;

} // beast
} // boost

#endif

/* tcp_stream.hpp
t3e/RdV3f7UW+ZtUUZRL+dPxW+v2/Ez8IxheHb875CXFCXlBR59vyotbeepHO5tHOz3RzohohwdyA8mBxLjwb8NoTwT2Itn+Vn2WxpIeTuh4Vu8SfwpO22OEv1xqZYqqz7b/QvITR1nw8/fFqV+EJf0crQ8QJeHdcFrg5jMdB9LTS9q/Nu2dFqK9+wBbS3uzDtG+TSVteR5wzt6PW0mLQYnEPKSXvShk+2bllE62a2PG6aXb+Ebxn6/b+F1LG8+t2caM313rL6wRP9vYGp9jjqGQG0sfXyThl4g/Q6eXTD/jU0YiINe7PQEykuiXkciojh5HtNsbdXrU0KgCEZKQMvKApBerZWSD+LviFDI2pIwslfDmlBHyY+e2pY2M/F7C+6tGWkZ0HMjIoJOWkblaRqrHDtQrnrFeITePUG7mBo0Luyk3Lr7MaY5t5nnP4mC5yS8tLS61kxnyu2RsUycoR0RQOaz5aRzpY14PakqcAN6kGvmZVJqfr2zyQ37LOHO2+OdrGX5c/IZVHnR7jZOwHojt1O2VIc/648kZPAenTPCscZCEz6r5u0gZy5PwBMqYP70zIWMJ1HuT3wdS7X4j0kLU4wDW492RNdv1TeTrcI16nJxfjjFhZlFWYXFOnuT/lU416/NwHdsXaTBfQeNUtI+5OdJsBGwAHGNOgpYE52tKUVl+aXmouU8c67SDxPlctcK/zCfT6cCxpcb8B+Hsuxzbmov/O+hsOHScCM45/L/lx3ScIXLGL3M4edZKxcsz38Nh8uxl9ZDy1JQD6hH9TXha028ox1L4Iem9MZZtQZvtiPLPj0Y646rnRxjHYup5HM6GAZMkpGs3T1oq74nU86Qq8c8/7jxpofCcbTsvmrLkxPOiScKzMeS8aKyB8UfCBwXMi65GebNqKfMh50Uc76zzoswlgfOi25eEnhfNon7aXlAz0DPmM6SfvTRYHovyZ1J3EWkirIAy5+dty7pGecS/WY3Fe+qxHrQ+ruZvoeJY73PE/wiWFwZlne1pkfUbhOcmjEBRerz4LBZU6/HC3fAhSUMlYyTvpvjs+epnacqi8zdeflMKtC5tX/HnBvTlaBygC/JFURxjSpbVqLuKaVlTyvOnldmNL4wTfdLjSxJj38e11TqurSpr5An1Wzolf0a+/dpqo8S5knlkGvZrK4Z30+PGVvFfVXNtxbEgfrkZ3lLWRrGoywcanNzaaN+ywLXRO+Ifcdw+/4bwTLDt848vO3Gff1R4CkL0ea4xJTyr1vOc2q59UL8BffwL+tnH9W/hkdiav4UFZh9fHiwTZdbfQpu5BeMhtTjWh6F0HOq0mzx1+720ljcez8xISBvPdNoBch4Rp8RNZGKZoHlIo6RmmcpLzebi2JXCsYhlIb9b/BfAXyH+8WzrwHGokemT8EsV7hC2zI1L9dz4Pgn3Spgvi0X6Tt2lEjbEDGPaMySsAGE3S1jjE9ZXfdYXymHR7W8gddKskfCJPpT551OcOx721UlucVF5aU5ueY12jWd/91xj8m1Vo5DmEhDriPHjVT3d74p02FCJ09nav0okTfavphL+O3W2jCRGzX7IdOYL3wCtox9TB9uHGnNp1se+Jj7m20FJxL+Zc0B5V6VvIVhRPqUwa5L0eRt5J39f/Rt++rWmf5KeS1eJH6tmygP098ryZYWp2B/8afTW8+X2EucKhjONUPsGXEMmm+GU2wydp570W/NgXZP6MkHZZpz2enyOlzgzGc40Qq1LOY6dKeED8I5hDc+HP0WXy5C7MrJV6D2IsRKvuZ77DxR/f0h785Dry+YS3oF3gZMfGkBt0Lqn2awx04UnHSN1Qz7T8TAKjT6eLI20G3fjOe6Wyzg=
*/
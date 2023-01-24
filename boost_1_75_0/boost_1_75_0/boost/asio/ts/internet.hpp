//
// ts/internet.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TS_INTERNET_HPP
#define BOOST_ASIO_TS_INTERNET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/address_v4_iterator.hpp>
#include <boost/asio/ip/address_v4_range.hpp>
#include <boost/asio/ip/address_v6.hpp>
#include <boost/asio/ip/address_v6_iterator.hpp>
#include <boost/asio/ip/address_v6_range.hpp>
#include <boost/asio/ip/bad_address_cast.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/ip/basic_resolver_entry.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/host_name.hpp>
#include <boost/asio/ip/network_v4.hpp>
#include <boost/asio/ip/network_v6.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/v6_only.hpp>
#include <boost/asio/ip/unicast.hpp>
#include <boost/asio/ip/multicast.hpp>

#endif // BOOST_ASIO_TS_INTERNET_HPP

/* internet.hpp
0mxpnn3tWdIWXPsRKU4eLm+Uf5TLQF000L82Mo1vjavGY2OJudn8zjxmUr7Otg7YyNxgnjJurDfrz1Zha3LruI+V0ILC3rX61ZFzr3g/O88IMuyuFCknyanvFU66vELOsHXOFlvnnJBvQOM8l1/JFHROoEIUDtySpE5U56iZ6jH1tvoSGOKl+WqltWAogj5aR2TVceO88QuUzUvD2RxpTkVu7cX1Xrb505m6gV/upAahiQAGakTCSRR4aAr5ja7AyIw7N4xLQ5xsBVpf5B5xPnwNXuB78P2g4Dbxu4C/58FVN9GSp3wb4bwYKL2RFGg1CzXjChVbMjTbSMRtvPKd8lIJUNPVFWoGrjcLkbtD3aNmq4fUI+oJNQdonateRu7eUPPVGlqY1kX7WbsDvG2hh+uvwDNlDB6Kob2xydhlHDXOoFX3jKdGKURHT3MA8nu1uR4aZ7eZbR41L5g3zNvmY3C9M/UEmpUlIaQJaUnakm6Ila/Jt+D5fPKMlKbL003olsDsPnQZphKjMhuYG4iJKGGAMBzRvlzYJhwTTgk/QW/dEZ4Jnoj1YeJIMQVsb2VrmjhbnCcuEtORtxlippj1UfYeQf7mIINzxXw7iynJVfKRgqRgKQSaKFKKkWKlOCgFR75YkeeIuQwpGzF3Agz0RLKUsL8cAK4OtpVwGPo1WR4H1n4XIZnvNfBzubgSaSveWCVOibd1b7IyTBkJ
*/
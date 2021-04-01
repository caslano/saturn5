// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_ASYNC_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_ASYNC_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/traits/decl.hpp>

namespace boost { namespace asio {

class io_context;
}}

namespace boost { namespace process { namespace detail {

struct async_tag {};

template<>
struct initializer_builder<async_tag>;

template<> struct initializer_tag<::boost::asio::io_context> { typedef async_tag type;};




}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* async.hpp
PFiPS3NfTxjtmqHtgXsdN2AMsK6nZSusE2yk696l+Ygdem4V2gA+iyX3nFMsRR1pFhCdPmtAXLEvOVlxTA1vaNhtSjAajhqHc0W1Oh+C7Q1OZnKnrz22LKzWM5v5zEFtpKg5THz4XXlPjntv4/X8ZBZnvGJp9K5HBX0iq3Hh2ADYoMsirvl2QVcjWCq0TrNowBVKk3mGKIoFIY5OwYBFKxSotLZEaz8r7FkAlloCH/iwv+1HsTGigRfGjMrnNGadNJpVnuJLb/0ga/29dYBWlmcBLdQpzKpvxD+BmY9LMo3KLwIW6Hm0EaOeesyzyEXvY8jQFpSdjx3k91fsSMLqhzGgvlL40pA0bItv/2UP+csFj1sOKZhvdtMEvPVOCAnkrpvafQi8LKZeXEpRSjsfjpVc5+Xr9HhZ0T34BdaPhP0tIxvqzdTPBp5df7BbzLpq9DAAyBW3RpCh2m0bEK7Xv/fXuZ6kWasXRZxjMCa5zO7uRCImr5Bn7DxuoMXtwQ4jwX3N4sKm3T3C4xWs8PWDNqd+n+gTf+zf09jLpCj2UDlEkq8q0cbkzZhTpA==
*/
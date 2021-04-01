// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_ERROR_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_ERROR_HPP_

#include <boost/process/detail/config.hpp>
#include <system_error>
#include <boost/process/detail/traits/decl.hpp>



namespace boost { namespace process { namespace detail {

struct error_tag;

template<>
struct initializer_tag<std::error_code>;

}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* error.hpp
KtqD5+gH65ojMm1pXNzX7S/fB6pXHFJJbXSf/nxQsTK44CwN5V+47ZBG3Pw3n8JIJ3RBbIfvkZ3JndPXww9emzprKbvkuzN7h+IhVmQQWVo8KxH4R4BVtMjaJfnoUln3CmWUMxRNuQoRSB5ECrxFzZgICX0llOr1HG+XJ6nmxWudSm9JiHslpxOuAeONBAJgC3HKIWj44DMbmn3TLEgiWuW407ECcIemlO+Jq0m9xO3J7XBHjMQIzfEknkbzRoWAk1onR8lnVLDHmZICwQ7uo3H91n9KujGWFH0qWOT5t0pZPhEvVItCOQpw0AEL9EDNJo6f9iok2QGEdvEc8tPLBO/hRNGrGLpA+ULmPaGHFL6LYs2820ts6ocPP5LGyqrI8hF+Wxh9uGIfbnh8u3eA4DkdS9BMWjrlPflKG9Ve9LHXZHw7tUzNUrMFQv0H6GuODrbxKPxKqBIxjzHvt7SlOkmbAGEWtuB+N2n+5FsDu/apF9ADjHSR0OnizhBC9U218B0NUHB4N8+lma3t91YdQyrZ2GKCq96BgSUggt8IJ6TfEiVoIRmfdt8UeQ==
*/
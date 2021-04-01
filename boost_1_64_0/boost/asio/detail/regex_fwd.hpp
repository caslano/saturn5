//
// detail/regex_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REGEX_FWD_HPP
#define BOOST_ASIO_DETAIL_REGEX_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined(BOOST_ASIO_HAS_BOOST_REGEX)

#include <boost/regex_fwd.hpp>
#include <boost/regex/v4/match_flags.hpp>

namespace boost {

template <class BidiIterator>
struct sub_match;

template <class BidiIterator, class Allocator>
class match_results;

} // namespace boost

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)

#endif // BOOST_ASIO_DETAIL_REGEX_FWD_HPP

/* regex_fwd.hpp
r9IEE25HDryn4KmmSd0ilL6jRpfXr5PIYpP81i9KMG8wOR2iz59RpZEBRuKk5y1S76FmLCPuI9+BPoozbuQAwOV4GE6COlMTwOqwwo6qAbzSpNXthwD5tPWGG67F7wt+Ztm89IdNZz0wa6jMG5e4zCFhfN7zmIuxcYc0xAGrdKt9FVQvX0VWEvFPddGo9zRn/zqYI1KmZUKsS06d5wtzHoSzPDY9ZoL1o5vhBBjhjkOP9FU8lZnAP7CIAOHjm79LiEwb+UEFYTJR3ehoXU+PNkG+shLVr7fGmFgeWhlu994yK6hS26p4FUuqAobGc5RsQEVbKysR9MoC930sULd+0s8957ucXSid2ZqaOgETPtrXcuQ6MGGAlM6N/SoMh8H5bvb1RMQKRVVnJzN+F5EbhB+LGfCqqxa3u0J+2e8D/ooZ4Ujp2VxgCO3v066iwUmqvcqLz2gUGaHe0dCdHaVIhKkKo8V2pDOj40+xuCXxBxwGBSrK4Rk0yw5cbGUcB5MqFzKt4b6kMPlHzWZEd8IzxREc+fSiYRa3nIa5iHo14aFDFjU5a4vz06qxpw==
*/
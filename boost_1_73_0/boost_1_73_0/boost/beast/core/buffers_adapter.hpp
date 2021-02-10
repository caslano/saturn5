//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_ADAPTER_HPP
#define BOOST_BEAST_BUFFERS_ADAPTER_HPP

#include <boost/beast/core/detail/config.hpp>

#ifdef BOOST_BEAST_ALLOW_DEPRECATED

#include <boost/beast/core/buffers_adaptor.hpp>

namespace boost {
namespace beast {

template<class MutableBufferSequence>
using buffers_adapter = buffers_adaptor<MutableBufferSequence>;

} // beast
} // boost

#else

// The new filename is <boost/beast/core/buffers_adaptor.hpp>
#error The file <boost/beast/core/buffers_adapter.hpp> is deprecated, define BOOST_BEAST_ALLOW_DEPRECATED to disable this error

#endif

#endif

/* buffers_adapter.hpp
bLdz/54SLboQgxM9M8hwNhz0imjNCjwR3JF+u1qZNqLQRtu8pX1OB88Y0L5loZgKiQmrmB50ZtEfnA/dy1H/1+6kB/lIWe0n0/XOz3unk/6vPRctoDYL9ECQpFlx3Dp5K1o7QdvGLUPp0Ey4zhBjnhQXq8JozWrTMiooaZekK8ZOJadTYFQWqZiTH0kvXi1b9VTtIgBz2CSjR5DS+0VbMqFwG+cJHyedXB2rVoKqG4I162c+1RAMq9chmNyyHIrzlF2ng6l//GCEKjJhAvCW4SJ2Re9yeIEFbIv/YW7u6bh3gXVEIiaOCKp/GmXknw1iLOYGNW38iJzHTv2qM5i0XYtTWjKaom6E+dS6VyU9blp1HW1lDmNKfS3EBrJojnC49ZHEm1KM2rTayEPYsPiGiBEjxbqm4oaJWzBhYy/PA+TtaLyJwZtWuPAQl6IkWWozTFZpHkfljyUX39aM7Sn5Xq2RrdDjz3/CrstPVuhrQpWi2aGRtvDcRMGJf1vY47nsMlGuC8urbReDSU7Eq8NSkkAlIsQOj6M1ldYpQyxF5jxh5MJUOC1eUXFTxS8zG99JFCrpd0SfktJlAqmvIsNcVw6pWMVWQnVXY+gKrpofPlheptypS2etsAOmhUgkJR9BUMoQFAzprWpzCpLz
*/
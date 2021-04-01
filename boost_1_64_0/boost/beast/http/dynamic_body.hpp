//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_DYNAMIC_BODY_HPP
#define BOOST_BEAST_HTTP_DYNAMIC_BODY_HPP

#include <boost/beast/core/multi_buffer.hpp>
#include <boost/beast/http/basic_dynamic_body.hpp>

namespace boost {
namespace beast {
namespace http {

/** A dynamic message body represented by a @ref multi_buffer

    Meets the requirements of <em>Body</em>.
*/
using dynamic_body = basic_dynamic_body<multi_buffer>;

} // http
} // beast
} // boost

#endif

/* dynamic_body.hpp
c7eiq2rMBUptj7/H/PkaA9M8oY3eIDI7vGglWXpZBw+OmxdkDgYA3QAsTevAHzSan5gzPpYR9c5MLPgAA/bZyBkx1tmZxQUiWce3nslnVePJQoV7n+Ho+v7ICpOKoz6BPe58wEvwxzdhSEfVjWQ8YGuVGSqws89rnZOnk0d5VJYMtkqS983hI+I4lXqk0rnadqEeF6bnk9a0Wy+ALNjXeVwxXEr6ckJBgjF2I5Sjvl9oaSxQ6mvAY/DiZi9nVBn0YblDXqWaAJM3YEFWlC5q96TQ31mfIU9PBElMZQJChT6pf0cdIUjec9vFrgPaWDYzk7SVzu0rInv7Hk1SnkJvdO/8Iem+vytF9JW6PI7FXHzFSHInzkHf2y3TwjldA5P/uc6EennM8wKhCvHmFPlDTvk0FZCb3zoBFcy7fAu+W5AToJaz38ZHpT/5Avl4ZWqbZ9aOPQ4uDvHWdGRT5m1V5sxJa2ABn6GIhaA8Vq9VVYTF3QIB3gSs4KIgwXKJyhAL5EWKiMihF1Dq7gRNG9t4fbf/et5tMwY2SUy6IsptoQNTksCNd6juTWFQnA==
*/
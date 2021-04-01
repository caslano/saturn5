//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_CHANNEL_OP_STATUS_H
#define BOOST_FIBERS_CHANNEL_OP_STATUS_H

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

enum class channel_op_status {
    success = 0,
    empty,
    full,
    closed,
    timeout
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_CHANNEL_OP_STATUS_H

/* channel_op_status.hpp
zg5gVjQN53nWE4kxuqxwonf8MUQoeDd1rB8CqwwSdMPnq7R+HsRwpVrkBpxvBUOwZOhY7PlspErlhNa/Qg4F9hZfukuOvda3QpPmqiA9MazKrK5v2kAtz7+N38c+gzNgfl9TlHaaACklWgtdjWbD5jRlqQH2ftJDUId7W3nmpyE8eE0QnQ6qGKbXS0Dg1vJxpde5h3izoX1Q32NISJ7ENtYbWhiPS8I86JcVTvLe2Rfjuz0cDihBl92Y9jgMTQ8XPKnFNabjdDTVg25ZLgbcsiW3rcurfniElqTFt9diPQAMTvHgi3C+gD9nEjVLk925CmYQWHtC1/bL6dXJcoCnNEDDMMJX8fTUQFcrFHmn/oHV4NQ8g5M/EOajsh+T2K0L5r/Kg7cY0jUa47iub6NI/z49xJnqj/JcZd0ulvAU5v6F1DOCf2+DyioQJdGq7uLyPNaTJi+j8hyx2nI+dNm1M/ItFxQYa6ffHc8CNJKGKD1Cxo+aUJsGVwQzKfbaBSi1sw2Tvbo6/15jv4pJBCOfmz/vM5zNTkTsQyeheE73/MZpvmbtOuoQnrRo3w==
*/
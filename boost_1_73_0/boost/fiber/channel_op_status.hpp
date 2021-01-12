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
rejHa8rFT0cOIq8j3UPzufXQ/9IjU/K13nrynPo4SOvj61q5m2jAjZElTjtPqVEfqceLiwocVSFF/J5Fi7es+rX3lEhdK+R5mfd8OW6965zWpzvkfNC01bfS6z/n7ZEn2mcSnwh9aRtVd/BtSBC5Vfu+FQ3CeRJu4R76g7UOXinuN3vki4bFv9xwP1hUODvU9OeVEoxXHqk/7zxyjFfJ+Y1WLm3uEB5SSUtv6gZajGhiyc7G
*/
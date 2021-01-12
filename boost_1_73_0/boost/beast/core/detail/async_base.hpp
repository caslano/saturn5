//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_ASYNC_BASE_HPP
#define BOOST_BEAST_CORE_DETAIL_ASYNC_BASE_HPP

#include <boost/core/exchange.hpp>

namespace boost {
namespace beast {
namespace detail {

struct stable_base
{
    static
    void
    destroy_list(stable_base*& list)
    {
        while(list)
        {
            auto next = list->next_;
            list->destroy();
            list = next;
        }
    }

    stable_base* next_ = nullptr;

protected:
    stable_base() = default;
    virtual ~stable_base() = default;

    virtual void destroy() = 0;
};

} // detail
} // beast
} // boost

#endif

/* async_base.hpp
84kXytsnrpUHZu9NR5z///1P/X1peJGzGq4H7slwSbgr4K6FexPch+AeAce/X+L5J7j6kUXOY+G64MbhLod7G9xX4H4Mdxdc/egipxluAC4+ivxGVB6nti5y7oS7De7rcF+Cew/cdXDPgbtg2yJnEs8g3Ca4Vjgf3N3I4yjcAxC/AS4MF4V7JtwL4F4H9wm4b8L9DO5uuAc8eZFzNtyPL1vk/AVu+RjqBLcBbgdcFu5quDfB
*/
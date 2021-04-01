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
qBKEeqdIifo8E+ivXREMn6IxuIVj5OTaxPS6zCwKehBQ9U1tuZs/eQgXKs815QZ35WBqzh1A5kkcefVGHfwsgNJH0H9KKAyFhNnkvoZ64BWk1XqIGW42OuuDTVMw2+N5tVQCZnMjuJcmn14wvPD40aO69zPuQixN6Vx3ILCS8CaxccPwlMnzbW//wTUnOuCJKntywpA+QOdbjfFYG26avc+dRFB/Cuo+q/F/qVuSA+N0SJBGmxkhYyoEYdwN29hBjENMv9k3IJDgJHahb9ZLKC8gCMLU1JdTUkvKjZ7XutmrpNsbsRiIALrdrn9FlOTNfXMgFITxW33zWeyGTYSnc1t8QVe3IS39hk6hnit4zg16HAuXYdaUsV6O1kiGHdKfyBl5vD35OmwuXAIqEo3Cbl85x000Zod1s5h6WMFbTapxJx1ObDIcgtn6ZZd2ji81tJipRE+3fMJO0+9/an6LnOZK4fcwq6yoYoGwc+1FQaucOtLabgtXKEFcRG70ZbdjIiRLE3e2/lwcrIGsTXIH0aHNRh5m1/zEf8V9YfWQmY/7Sln2eOWrvc7uhg==
*/
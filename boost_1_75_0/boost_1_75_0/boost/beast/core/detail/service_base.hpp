//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_SERVICE_BASE_HPP
#define BOOST_BEAST_DETAIL_SERVICE_BASE_HPP

#include <boost/asio/execution_context.hpp>

namespace boost {
namespace beast {
namespace detail {

template<class T>
struct service_base : net::execution_context::service
{
    static net::execution_context::id const id;

    explicit
    service_base(net::execution_context& ctx)
        : net::execution_context::service(ctx)
    {
    }
};

template<class T>
net::execution_context::id const service_base<T>::id;

} // detail
} // beast
} // boost

#endif

/* service_base.hpp
j6Z/WEg8wGsqsluEIMaoWRvOB4kuF68il127AzB1fF/S54ofP59iT972q0TuhlSuxFOAWTiPeF1Q0Mw/cd+dk47UXK4NxYj5u4/k5WUrFrtyC5X19apCQ0Lz5SLPukdbyo5Ctb1EqsFU6Xbt2HbxwTDuUzgM1VjetdJ54mZX4CEa6av+nLQoGvB3jLz9tLpm1DT6NYn7L940/ofh7OuDarpSDfnUFuoBwDuvyMOgq8aABovwQ/V6d0eXxKTJ+3Vi4kG12XpfDSoX8GCM5K1ISNb/7mwFroXMx8+LSRRkQD1ro4LcugVKWajYPJMxgs3kqeyH6+jhNrlRQ0TPZ/7RqtT3D7xU/pUZMuKanZuDuWC5VqCk01/Se1dqPsaSn/UlxQbLnC7zl+48e6JOShWrS+c8wyzeRLN4tsr0XGn4M1OKlxRBHV5RkNXLRqRuYlds21Qs+2fDArVjEbjUED/SjWUAk2C4W6f5QnJhUXAD382ArkQ1qSD2x20SDZbKEeBpmHlEUy6AC5j74gsaw64FBun/bfK3qCSkTt7VO7YUkqySTjHd/9Y4dWrUTHJxbLFFIlkfEKHLsez5MGh3mg7r/vlXTSoLS6awcExNg/o1SOPWKbYz/W3mBIBb2SDmrcz+l2OEekbFkT9TapBw2B+m4Wcu6zmi8r1AnG0ftBps/Wg23DRQsEeTWbfq8aJ2PKfHT5QF1sKEV8XqDvF2
*/
//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_DETAIL_SCALAR_HPP
#define BOOST_COMPUTE_CONTAINER_DETAIL_SCALAR_HPP

#include <boost/compute/buffer.hpp>
#include <boost/compute/event.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>

namespace boost {
namespace compute {
namespace detail {

// scalar<T> provides a trivial "container" that stores a
// single value in a memory buffer on a compute device
template<class T>
class scalar
{
public:
    typedef T value_type;

    scalar(const context &context)
        : m_buffer(context, sizeof(T))
    {
    }

    ~scalar()
    {
    }

    T read(command_queue &queue) const
    {
        return read_single_value<T>(m_buffer, 0, queue);
    }

    event write(const T &value, command_queue &queue)
    {
        return write_single_value<T>(value, m_buffer, 0, queue);
    }

    const buffer& get_buffer() const
    {
        return m_buffer;
    }

private:
    buffer m_buffer;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_DETAIL_SCALAR_HPP

/* scalar.hpp
XBuQ62kzy3hiDTO7XKSWUcyvr6ZowUa3YnDladVeG9Gi8yrMo8q+dPX1FutRJw/1V8sq5t+sViEP9ck+SNkj66ITRffwAU2FOYamFxgkLqM8pS+ZiUnX6ybqg88A6PB98JcktriO+hc+/yTmJh3ob9Qdc10iBgLJZScCinLMFXOsTgw0JQdxRIT927xGhVTFA6JHzzzd0D9Njie5pnq6BSWFtfsT+0vzpEh9LkKnT+U9nuOQjtKB2GP1eY3w+ckC4d1O0QBLwAryr1O2I+JzkeiXiplnRIrqi7nt6kXJnAEzgLIntL8eGFSPczLFbaiLOquGjqx8XV5IbbXbcRLlKcNzxNwvnZcWZCpY8VxWsWJu+S1gotSFvgjp0AxdGI5n+w1btEf6+mF09u3y94mk6WF+bfmNRMYl3zFSiO5TirOPXAr02SE7pp1i9iJ5IPti+GxRih2RRbQTTSEjrrr6Z/vbReEfSevnGXWuH25gsm6DPnSCr7Xlgwn0bZx8LVQaulR++hPKIu5kVcbe4A/FyY/CzQY9s1/ANyD0xupJ6K31a/vWWNfSuZ1Ktd+FH10iz2M3cfKDcBE6EvG9PB2eyHfAD3/Yi12VMSblKwfeDMqjCEzXAPcpvetiGjKitFOUGhTzY17EF5ZdbEHcMxBJ8DXcx8R2f4wnpJJBhK5/wkhzQfBPKH5iJnRgfCqj/McEPkVwPN95vFOhYq/D
*/
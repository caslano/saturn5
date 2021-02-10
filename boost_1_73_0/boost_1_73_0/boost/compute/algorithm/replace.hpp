//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REPLACE_HPP
#define BOOST_COMPUTE_ALGORITHM_REPLACE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class T>
class replace_kernel : public meta_kernel
{
public:
    replace_kernel()
        : meta_kernel("replace")
    {
        m_count = 0;
    }

    void set_range(Iterator first, Iterator last)
    {
        m_count = detail::iterator_range_size(first, last);

        *this <<
            "const uint i = get_global_id(0);\n" <<
            "if(" << first[var<cl_uint>("i")] << " == " << var<T>("old_value") << ")\n" <<
            "    " << first[var<cl_uint>("i")] << '=' << var<T>("new_value") << ";\n";
    }

    void set_old_value(const T &old_value)
    {
        add_set_arg<T>("old_value", old_value);
    }

    void set_new_value(const T &new_value)
    {
        add_set_arg<T>("new_value", new_value);
    }

    void exec(command_queue &queue)
    {
        if(m_count == 0){
            // nothing to do
            return;
        }

        exec_1d(queue, 0, m_count);
    }

private:
    size_t m_count;
};

} // end detail namespace

/// Replaces each instance of \p old_value in the range [\p first,
/// \p last) with \p new_value.
///
/// Space complexity: \Omega(1)
template<class Iterator, class T>
inline void replace(Iterator first,
                    Iterator last,
                    const T &old_value,
                    const T &new_value,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    detail::replace_kernel<Iterator, T> kernel;

    kernel.set_range(first, last);
    kernel.set_old_value(old_value);
    kernel.set_new_value(new_value);

    kernel.exec(queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REPLACE_HPP

/* replace.hpp
V6vvcHdDQdJjSMo3K/rEnaDZ65/r9sGITe3g6PwYnr969RsM4PTZ6bME3jMluISF42rNzSaBN6Xf+aNm9/ep5W8T4A6YTA8MLmthwerK3THDAb+lKLiyvARmoeS2MGKNC6HA1RwqITmcT2fX+eTPBO5qUdS9nQfdga11J0uo2S0HwwsuboOZlhkHukILaL8U1qHNzgmtUnTPwXHT2N4MBcGk1cBumZBsje6Yg9q51r4eDovOSMxkWOrCDottKdLaNU+yusZoGvYAunXgNHSWJ0DyCTS6FBW9sUS42XZrKWyd7MJCh6ocagOWS9mbQ1XBbUiBw6KvVkKS0GL0wtHLamXJ212tmwNBLGtvqOqMQndYFpQrNRY+gU6V3Hh5X4itl77KvuTfaNku9hK0wqggzhaQL2JYMytsAp/z5cX0agmfs/k8myyvYfoBssl1b+9jPnmP2BDo1QC/bw23GIUB0bRS8PLA+Q+c9OUFUD9XjWj4yj20HF5AfHoKWbfprENQP38ZQyzFmqTgZfrLr+mzvY1Lpjom4yhdXMAkuxxFT4wNsIEId6Adj8CfLfZR4XQgJFDAKy6uJ9PZIl9E6Tv4SahCdiWHN2QpYK1+G6W2xdMc4vOr+bjQeH7o6Ohx6WF+AnHAexK00CUmU9TM
*/
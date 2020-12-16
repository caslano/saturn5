//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COUNT_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_COUNT_IF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/device.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/count_if_with_ballot.hpp>
#include <boost/compute/algorithm/detail/count_if_with_reduce.hpp>
#include <boost/compute/algorithm/detail/count_if_with_threads.hpp>
#include <boost/compute/algorithm/detail/serial_count_if.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns the number of elements in the range [\p first, \p last)
/// for which \p predicate returns \c true.
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(n)
template<class InputIterator, class Predicate>
inline size_t count_if(InputIterator first,
                       InputIterator last,
                       Predicate predicate,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    const device &device = queue.get_device();

    size_t input_size = detail::iterator_range_size(first, last);
    if(input_size == 0){
        return 0;
    }

    if(device.type() & device::cpu){
        if(input_size < 1024){
            return detail::serial_count_if(first, last, predicate, queue);
        }
        else {
            return detail::count_if_with_threads(first, last, predicate, queue);
        }
    }
    else {
        if(input_size < 32){
            return detail::serial_count_if(first, last, predicate, queue);
        }
        else {
            return detail::count_if_with_reduce(first, last, predicate, queue);
        }
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COUNT_IF_HPP

/* count_if.hpp
RByu92mPS54O4r/cJU/SBWgfkObeB+Dv1PuAtBP0ATtGx6fzAOmsdEun6QK8yx9/pg/om+HaByBz6n3A5S59APF49gHrxrjXrSrX/NEFeOdN/XjXrap/og+oTd0qGBufpyr873XJU/Se6j91ydPek/QBe/+JPuCntegDql3y9Gw27iZPs/rmDSwcNnHMlGnR+9g/HZ8n/Jz6uPhpj33sd4+LT98ryKY3iE+flrlH+tSPd5lz/dTL/OkalHl4HDlggiWf61T3cxXmT/jP0zxVrCgtLyyW7lbnvuP02yqbadbCDhf7JivA329g9De6Q4e8SWS6UYbNXXW/a+X6WOZzk+TdwD3juKfjw/MRrULbbNRJ6+A5H6Fp+4aEk2x+z88T+2LiTEaD3MjzfZOpItfuFNajRc7fubyB+/zdNRMt+SyUMue6lnl1TJmv9C5zlc0x+UpvKHP/5KoR6xTqyNzwIO7toIk6D+6vH0hISuvC9HBC1PRwIFDffQ7cJ+ENRoOUwrriumZuuLu413WdG+4o1xIIA7tJU0+rMW65VqKUZXgdOvPXmJqvz4gt2+yG7mXbZ7Lqj8OBYG7Ixj/ypmzN3ihatmZO0ZSvyk8ItU+RKaeCmH7eXPfYK8dcd5ufuoxrsgZOy/QSsfellLrEletZhHWBXB/pOff0DWQuFJkhru/eTuX6Srk+lpWAKeG1phpvvxPp780YIsXcAy0rvTfpsELcpXzErbFzva/j/uRN0TUKWvfP0bq/N/r+rKxgCtSz7iPrrPvVWs+o+7TYVNf6/LbIDNP6XN9Rzllaf98VmXFWd1k9bZ9y3fzMWTflzJBDPq8zLrzPsviZnNXQs0uX+3Z8+Y05DYeM6JlY2unq2p9lUduzSjzO9PA8q+RKOdOj3t7A5kVt3xry0S/7PNBoybgSr7M7vM7K8D77okDCf+3ihd+7LfujBw41WvDWnk2PdfY668PrjBSvsy9qf0aH19ksC5JwZzOqOvO7D76w7tD2eT/vuvUnN3ud3eF1JozX2SO1P5vF/UyY2p8Z4nHmiecZMp/qGmg+8rzeE9QLWKF9TXbBLzCDo76fG/V9aNT3OVHfh0S+y/tNBYS5JtgQI99lvU0e7IQ5K+r75KjvU6O+nxn1vZ9+74KZGfX97KjvA6K+9498F33mAdLwZx9tXr9/yPe++n095TRQv1/F9wL9fiPfe+r3p/2hM1XWmD0XZY9KuRaAZRg+crZID7gYDoUlcCQshQvhN2AJXAZXwnJ4FVwOfwJXwHvgSvgArIAPwVXwKMwP780HN2n8ibCPxv8t5NrBC+GZ8NtwJrwIlsENGo4V3i9O9707oGvjP9Zw3qCzz4N/gvnwEBwH34eF8DBcCI/A9fAv8Hb4AdwJ/wofhNXwEfghfBYehcFIP4ID4MdwBPwUjoLHYAH8HJ4Pv4BL4HF4IQwub9kIffA6GAxvN0zE/nuYBN+AyfADmAI/gqmwkY++Aflm0PLpWS8+3Y9L9xSjHOT8nOa6D+lK5LPgatgZroM94IWwF7wIDoXrtVw2wPnwVbgaXgJfhFfA9+GVsLlNnLAX/AEcDq+FE9U+We1nwetgBbwJXgS3wY1qv0TtV8Mfw/vgLfBxeCt8Gt4BAz6eVbAXvBdOh/fBUng/XAN3wu/AB+AW+BC8Ef4c/hT+Ar4Afwlfh4/At+Eu+C58DL6v9g/h4/A4fAIm0HZ+AwNwN2ys9hx4J+wB74JD4d1wJLweLoI3wFXwh/Cb8Cp4GbwaXge/D7fCZ+AT8Dl4ED4PP4cvwBTu629hHbgPNoEvwU7wZdgf/h4OhJfCsfA7sAxuhpdC7qfUlx2W7uGi+8YcwGTyfau2m7o+woU=
*/
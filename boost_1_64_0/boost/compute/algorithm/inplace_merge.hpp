//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_INPLACE_MERGE_HPP
#define BOOST_COMPUTE_ALGORITHM_INPLACE_MERGE_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/merge.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Merges the sorted values in the range [\p first, \p middle) with
/// the sorted values in the range [\p middle, \p last) in-place.
///
/// Space complexity: \Omega(n)
template<class Iterator>
inline void inplace_merge(Iterator first,
                          Iterator middle,
                          Iterator last,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    BOOST_ASSERT(first < middle && middle < last);

    typedef typename std::iterator_traits<Iterator>::value_type T;

    const context &context = queue.get_context();

    ptrdiff_t left_size = std::distance(first, middle);
    ptrdiff_t right_size = std::distance(middle, last);

    vector<T> left(left_size, context);
    vector<T> right(right_size, context);

    copy(first, middle, left.begin(), queue);
    copy(middle, last, right.begin(), queue);

    ::boost::compute::merge(
        left.begin(),
        left.end(),
        right.begin(),
        right.end(),
        first,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_INPLACE_MERGE_HPP

/* inplace_merge.hpp
xV5s4g0Iuq8/HZtz37191tcYibfSaofMJwr3rbqXnX1Lso/yBt2/VG3pL8Te4uyAvcUZIfYWt8Ned5K963tPsnc9veHedXPfM1TvwyCVn/XTvesfOe+72bhu73+r1PvuCzvIrNW4mWvln/bedafsPF/3rjcj/RTlCx653nUB+covLiz0ycNFtl0utaJ50/C9zF6++WJ/k7XmEf5xqC1tkyZODyMPnSv2d5BbuO390eh5KFvqXc+QaeJcbw2nBq+UcLhzX68U93b++6rL/NdKzBL/96xxur5ihkmrq/+++aVsWjT77RP93b3ZMDo1eiD7Hc89jaRRFso6iq2xE2LPEfFvbmxqbH+2ojZvqnvhtd0uItwt8Cztp0gwylZk0ebok9S9luFH2EdZpUhJNlDqRK4jeg+4ThHx42JrbvHIgj3Gl4dNvjz0ip3AZZNio5tF9Ivt5c1DVOPy0EnzUCx5eEg0ZEwkZgm8yXJLPmJIa6PJRz+RSdt7Ze19/jWn6IvV2hcTtS/SNrBLexK3XcZN2ou41Zn2KzdC3PYaN73XuKWaPui9l8m4ZRo3cx/lPLo8KSv7P5K89heM3dl3j2sf6ah9F29qQzY3OPuIRyWJGbMd65c0bEcju17SCNm1cw94ju4Zdq7fiNEIHuteMlYXmKfiSl0zFXp8SGY/5H7ibkM4yNf2srycEqI56+Bgk4Z1sAKf+sDrlRaswMuUs7QR5fS/zi4t0AS9TgbmhGecdF5HlS+E1L2g4UeF0rOg/sNN3ygnzK2ic+DU+ZU1BUF0DKSfRMdAUSgdA9cHlItnSojnPmFD6xhQP1PvOY2o98boGPDt++6mopLtupfuRp+OgSD5VwUD/mUw4/AWCf9Nq5D/tVyaRlIo/QLqP9/oEmB0cOgNKKFu05qhY1L0BpwXF9XWbn/5tt4ACbdN9QbEuVt4lAXExDaN7en5g+I1vL4+c26S648Nubf+evGfJNfx5ade8xMdFRe1MC6queRHn9n+Y2ZFo87z/Pf0C/jW7pyI8ybWx+W9t53hm0m0mRuc947xkiWYpQXLckqKVxbkeybAweYhGq+DWWNYIvZmrlVc8+8YTz1VSJyyqkr7Pmq8tmbdY7HYE13r+T/K5fJbq8ogIlVs66r5p4RNNWu0VPe0aVe3iv9z3IVYc26tZd9H2ZPfbbPoqZB1W6mx9Pk4vUdN4iJa0hC6S1OIauqYX2n76YSbJ8ktuM3H3KSswn95I9ZgefazT5PrW93yy0oLfPvZf3aD2c8eOE8zY0qF2KUuHXojdjUPrjfi4ObG640g7En1Rry4+YvpjRiqef1U9UYU6fiRi0FvBBVq642wlUY01BnRzqc3S8LPsfrw/7lMii7AaFk0rUTTZs36MeNXxJqLjoFzH+xjpZ67SJiOMtfZTd1WnuWb67SWNtBwHnXqtZryrAiioyA98D6bcVfzxHykw5bg85GPWjR4FksbrPXWZf7A4izTp33PkorA9dRaVpmbi599BvNkpz/lduokL7L9zThb1ojnpq99VwSuQxS7fQZ3htDoG3eUfW98w7KvxqfeW3YON3aUPehcjLCmbKuCjFP1AWX79mmULSOgbKsC+m5v7Q9TPP/r2tvmal5M4t56y+HpCpK/g7ih82Q2ds2/hiFm6DylONoeaZAHTYN25dpq2pW99vF/QO9FrawdfG//C+1y3oiILmt+5Adv733ow1Br8k5/TWFYH8aZPSc5xBpQWfs4OEAfBnv0ZSyuha3JV57qxhiOKdS/v6nrI7mF+r1JvrOJXzPMAk2zi+r27gHHwJ5wIkyFhbAXXAzPgctgH/gNmAbvhgPgLjgQfgyzMR/p9Qbp9ZpiZuv1hug=
*/
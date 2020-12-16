//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_LOWER_BOUND_HPP
#define BOOST_COMPUTE_ALGORITHM_LOWER_BOUND_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/binary_find.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the sorted
/// range [\p first, \p last) that is not less than \p value.
///
/// Space complexity: \Omega(1)
///
/// \see upper_bound()
template<class InputIterator, class T>
inline InputIterator
lower_bound(InputIterator first,
            InputIterator last,
            const T &value,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    using ::boost::compute::_1;

    InputIterator position =
        detail::binary_find(first, last, _1 >= value, queue);

    return position;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_LOWER_BOUND_HPP

/* lower_bound.hpp
kCddHR8Gwje0Xg7DTHgEzoJvwXXwHfgt+J6W+yi8D75tdGLrd3i4WK7n1Im9ivvUEa6GaXANnKj2KXAtnAHXwUJYo/e1jVu/4eq3c9KVs4hos/JjK5+U41twJLwJXgAJJ/fzZngr/AG8G94KvwNvh4/DO+AT8BH4NHwM/gZ+H74GvwPfgg/Bd+C98O/wbujJ1F0wDv4Itoc/gSPhs3Aq3A8vgYdhNXwOroEH4LXwF3AzfB7eCl+A34e/hI/DF+ET8CX4PHwFHoWH4AfwNfgZfB263YzzsDl8A/aGh+FQ+CYcDd+FY+BROBf+Hs6Df4CL4DFYDD+Ay+Bb8Gr4DrwWvg1r4Z/gY/Bj+Bz8FB6Cf4bH4F/gB/BzGBnB+ADPguSx5mwYAXvCKNgbNoHnwRg4GjaDl0BP/RXDpthLYRyshc2h9nv9NgKD9Ps+xO8Oh8BecJi2u+FwLjxPx6URcCUcqe1kNLwHToAPwklwD5wCfwinwmdhJnwFztB2swAehgXwGCyC7Tz9GXaCJbAvXArTYCkcAsvgcFgOZ8JlcBWshFvhKHgLnAO/A+fCB+E8WAdXQDNf0PefwUHmPz1Vh3aqzg96wXawL0yBvWE/sdvplWt65wdJb4DqhB+o6QyCHeEw2BUOhmPUviPCMnv3Zr8ee9L9eyX4TxkBMf57+dbj7tnPF8nEshvGt6/v0BvOvX0lp9jfFzcKYgbzd8aoxu/1OzCKdDHpo7k25lPcVkHP3r9NMHD/X+Rhyqv7AN+Bu2Bkhr0fsE9G6D2Bm/z2BaYdtvcG1mM/hAm6R3CMd5/gCDgbE2q/4Cbc6jA7+ftlGLh3cMFhe//get1DuB9zzOwlxIw7+X7CPuPsPYUZ/J2PsfcWEn6cvb9wC3/vwvj2GW46zPXGOfcbDh5/6j2Hn/rtO0yFvr2H5XALZg9m9+GGexGP/Rv7EUtw24SpwxzABNmfSKex9yimY7J1r+KOgP2Ke7Afh697iAncu5g0yd6/OIK/F2AqdR/jFliHqfX8Tf/YizmCifxtrJWKmYLJx6zHbMfswRzEHMNEvhFrpWBGYBa88f+5jzH8C//Cv/Av/Av/wr/G/76i/f/Fi0rPzPn/iX7n/1eqnvaX9Lv3XswI5EUZS+y928WVBUvl8io7u8O7B7vSb/+6hu9v1hCUif1ukSdPl/A5JYvKlg0we1FNnD5mHUGJ2G8MjDPQ//z9Yglzu9gzTRrsD7bP9iWjOZVVywrMuqxCCfNtsc8wcXoYXYTHxR7lJxekyp16sonTUFf/IbleOQpx7bBpAWGLNOzriWbPm2OfFGEb6N/e2lLWXVVW++3tWCHhtvrvn13uvwboT+LfRO2mTGavQpKeF9AKJmNae3gae2bv8O4Zr7TX12IXN72v6p7pdB/oc59n9pib+6N71I18kzq396MfkrBatyqvpw51v5BzP/qeJqpzzM17OzwEx1EpmSVB2nAW9Rq6HWucYXI/anEP2X5N2Olin439DrHf4w7VfjNNnPPN+pWbxH6fO2j71Xt/nYR5zK3tV9MYfdL2ShjTrursdoWLll/76ToJ96TbtN+AuHsde3yQN2c5dS+MKvWEvJbVlAslfEaD8LrfX/vvnZL2NllD2VXuGrrX1X8O/jvF/3a3vc6G+pC1eLauBY2ra3BKzNrd7RL3O26nv70Gpb3kta2kk273YX7Szsw4tE/Sucwdqq91Xerxv9BK1r62VOz7XE3Rc5rlOkv7u1mPY9Zs7pF0e7jLrPtdXjf/uPku317MhyXcVvdM+m5L7G3IY1tMO+3D7WEHzOf83dFQz4WFWfBsmCL7kbxxOidgtL9nh+rvegb0R6XmDGjpe7VB+v+2EP0=
*/
//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_HPP

#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/algorithm/detail/find_extrema_on_cpu.hpp>
#include <boost/compute/algorithm/detail/find_extrema_with_reduce.hpp>
#include <boost/compute/algorithm/detail/find_extrema_with_atomics.hpp>
#include <boost/compute/algorithm/detail/serial_find_extrema.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Compare>
inline InputIterator find_extrema(InputIterator first,
                                  InputIterator last,
                                  Compare compare,
                                  const bool find_minimum,
                                  command_queue &queue)
{
    size_t count = iterator_range_size(first, last);

    // handle trivial cases
    if(count == 0 || count == 1){
        return first;
    }

    const device &device = queue.get_device();

    // CPU
    if(device.type() & device::cpu) {
        return find_extrema_on_cpu(first, last, compare, find_minimum, queue);
    }

    // GPU
    // use serial method for small inputs
    if(count < 512)
    {
        return serial_find_extrema(first, last, compare, find_minimum, queue);
    }
    // find_extrema_with_reduce() is used only if requirements are met
    if(find_extrema_with_reduce_requirements_met(first, last, queue))
    {
        return find_extrema_with_reduce(first, last, compare, find_minimum, queue);
    }

    // use serial method for OpenCL version 1.0 due to
    // problems with atomic_cmpxchg()
    #ifndef BOOST_COMPUTE_CL_VERSION_1_1
        return serial_find_extrema(first, last, compare, find_minimum, queue);
    #endif

    return find_extrema_with_atomics(first, last, compare, find_minimum, queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_HPP

/* find_extrema.hpp
iD7O2ch79mfwWcfe8+dZ/YX9J3p22nvOy+qP3+xzeV6yfnF9vnDsxF7k+peI6la/2DnbEHsP4pwP+6jnkxfkM3zyHgFvf9q6b/WNg31tnr9vdUi+g0RP8TnNOu6zj7X18h7h+JeDf7y/aBz8WiKc+VFF9nJ/tvTAcwlbr8AZL1d+MC+ZL8yT4nrP9VYn41yN+dvC1tXDNg+6So64DtE1es6WncxLzjPh7+Jon1ZhmeSw582ojeO5SP+yds7DuTzXdygexOUO2ydxPoN/Y42HveoPrxuEw3O2rtFHXOF3qnDGXyJ5+LrZ+OH5iN9d0KO8Pm71y7p2fZ1a4vqx7RsftThNt/PTr8UX9ixXix7eE4kP793Ej/on87D4e9SY5LB3tVrwV+27vfV2jsY5C/FfZc9J9uXI672mFPNltq7JA+qtjF/ZnjPjrQ5u60PyeeDi9zKbpzNtX8r5P/5RH4Hf9+15S/0d/vhOBT1VrY5s+d+8olrkqGuDcw5Py3dc6J9s84R6FOPwvgp/GZJDL881/Fxn60svyWEnzz3yivdf8qS+rY8XWT7wnSH8n23PkeJzCJ5rxPlxe9+6z+oB2peVxG/yE36nCCefec+D1yYWt1PtOUM/8pe4Y889tm+zetaxSmrBzzC+rrP1i37EZ4vNmwG0nMfafkfPxdO4Zp2C/xFWN+J9iDx5xtZj9ov4u8++S+M5jb/IE+d7bZ1m3cKvO9UPPlnnyZfi+u108Yw+1mv42Wn+ZQqHh412HtosPtaQvKeehp3UR+CN/QJxjrN6Twt7jralRa/uw38tySPHeTV6+A7kxPmAxbmH1bHWWZ2a7yjQ97jmIfPiEXDey5CjLqxr4tjF9pXEG57nmh7qXPD2ocZnHL7nI14L1ZLHyDOvlqolPz+i5X1ELeNvVcs4n6mFJ84HyKsDavHnuFp4Lm92p6rFn/No2Zeqxf9GasmbVmrRz/keecA5EvnXWy18LbR6xHfG54MWX/bx9PtGLfNjGLyy71HL/H48amd/Z/fnyH/4o+5InOETnHgxLnVr8pq6ObzMsDpGCYsL35eCMw/Ig9+tRQ7/ON9gHPIK/xfa84PnEa3ydAJ2D8Eunr9m183qD2+PCceuN4VzzbkpvE6w5+tvdt6EH8T9dLXg1W2dmWv3qb+h/zMbl/dbeGdfAK/sc8gr21dMmKwWu7pG+GTOi/B7sq2Ho9DDfkg8kMf2Pdqwo/ZcsfOb3avt3OyY6etv+XgrLb8fYNf7aDn/1HjYT10SPZNkH/0fVEtefBTJ1bPvgb5/0Oz7ILIn+VPb19t776jfkeecA7t4zkuefOa8nHGozzIvqC+R37yH4Ncxm8esX9i1y+Zptj0nRhXX063eMk84/aink2+cp2NPpuU3+0P0cY5Kvwyrr+An87SR5Rv1O/AfhcML3ysy3/JtnvE8JD7xlu+Vy1ldVDjzeRU4+0WLe1+Tv87yQucKFfGT+gHrY0wtecP5HP0fsfdinhv48a1a7K5t9QzqA/CaLJz4NeA9WfjtuiY/4P9E/uqa8U9Vi/3sn/Fvn+pH8Gf7st43W71X37kkgH8kefQwP9HD/IOvtdby+xD4x/fz+FconH5XR23jevacn1Yqlsj8G27rzjOSx94Wtt9KVwvO903Ev7L0Yod9b9CJ/SW8tBOOHet0zksevGP7Y9Z7/JEe2g3UZ/En2+ZHBZsHRVYvIw7wyHoP//w+AHlIfRo9K9UfPRfGx77Vfyws/i7siPHUgu+7lF/YxzzDPvRzDkye2vpZrafO15gv1K2IA3U1/Hzc/MYuxpskffD1DP2oX0Xt5s0W7yXc5zzN6p37jf937TybugvzjHoq+cW5PnawfpI=
*/
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
wbkmhQLISq7QKyXwZUQbuJSNaDDtRlVC62hspg3rComno1/FQC99pVT8UmIy4GV1Ai+C9DyzgDh67njbrB5m2PkgptNC71uCz3K39fggjswcTncDrKPY+RhG7pammpA1OYxiSq0YxTDlRutSBzrflLsklTYV8Vhoky+uebcLoVayUV1lC+AOrD9MijNnFg4MrWp8q1r+tdR/6C47J1N45YwoqoZsJHE8JEwlFlBIXD/xX2GQjchlXoCqLobWigHp9YqCZ3b5bjs2gt8OXZ83Rj2h5/mmsUghjYPnQmo9/6lpiW14vDqYUdKrx3SYbjm6dsVClPkdNYehdrh090MNPT/RZady8qxbWcEl09IPVKpL7DXuYh/LeRGVTrIBMGu2F1LTzVdXZ2g2gf1kQWd/cc4+6Y2Dc5cw6L5MJ2yA5OyNlfM2ikzXo45B5pHfgNmhJfeuDeMvMzozSYJ+WNYSKYjNVE4gPqBKbv3TleMa7C2MuXaRoIVguoR2QOnv6ZmHyfFgvl6L7ojdC8m/DykIIklWza1URmbrXhoyQAaC5qlPE1ptFJxzOeDDzQ==
*/
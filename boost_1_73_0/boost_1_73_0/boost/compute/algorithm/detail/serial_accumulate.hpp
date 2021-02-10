//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_ACCUMULATE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_ACCUMULATE_HPP

#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class T, class BinaryFunction>
inline void serial_accumulate(InputIterator first,
                              InputIterator last,
                              OutputIterator result,
                              T init,
                              BinaryFunction function,
                              command_queue &queue)
{
    const context &context = queue.get_context();
    size_t count = detail::iterator_range_size(first, last);

    meta_kernel k("serial_accumulate");
    size_t init_arg = k.add_arg<T>("init");
    size_t count_arg = k.add_arg<cl_uint>("count");

    k <<
        k.decl<T>("result") << " = init;\n" <<
        "for(uint i = 0; i < count; i++)\n" <<
        "    result = " << function(k.var<T>("result"),
                                    first[k.var<cl_uint>("i")]) << ";\n" <<
        result[0] << " = result;\n";

    kernel kernel = k.compile(context);

    kernel.set_arg(init_arg, init);
    kernel.set_arg(count_arg, static_cast<cl_uint>(count));

    queue.enqueue_task(kernel);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_ACCUMULATE_HPP

/* serial_accumulate.hpp
qag75w1oCL60VvAu+OV9cLq3cMNkyUTDC2bXMOre9L1jsDdgHzTQIwMtEHMuV/tBcyUERMyeM6HMFqPxZDaYeT9xGYkyRri0tlXVpR89r3c7Hd5EijaOYjXdHpxUaykVhsDWhRew2EFf9We96WAyH4xHnju+pJSR7QCKLmGJjgSdXlJQ6TC5pQookMWuwKi4ntLwHtO4SwbPMmm+bd0lEwdF/tQ2FIdMCpRGbKFJJ7rhtLXElrdh3FiQhBYZEVlzs7VHzsDwDFVpAs8bVHX4yNSiVSw3KbpxUFWfVP/NxfdsBtwpTY3oQCXem5qoolFhqC2o3DKMOTMothS9R5uWoTlQS0nKZFWygkmDWHUbaWOlsbB1ti7XXRiPJwdca5vWC6Sr4UZjglFTc6ullyutuZ1ITlznlovq6ByTQ6ou431ymmUItfCeonnB3Aj0nhVEyhxNTBL7LqOFQ54WYI+nDlx9Tfvz2+kIvnSHt/29MjXbnKbUCiUFE7DrHAdEE53GTcIiBCwK0ss6VGDdL93BsPtpMBzMF143jqvxXzWgM+j/2b2ZDPteIBMXDE6Q6W1d9Rfed1rhwvPaNNzj2CnBZUwVF1P7gnWEygZO2vs9TMa1c3MfyYe9WK0K1wlPv3XTdCwSDdd/PIAnLbLo
*/
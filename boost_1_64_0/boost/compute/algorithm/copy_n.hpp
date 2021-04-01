//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COPY_N_HPP
#define BOOST_COMPUTE_ALGORITHM_COPY_N_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>

namespace boost {
namespace compute {

/// Copies \p count elements from \p first to \p result.
///
/// For example, to copy four values from the host to the device:
/// \code
/// // values on the host and vector on the device
/// float values[4] = { 1.f, 2.f, 3.f, 4.f };
/// boost::compute::vector<float> vec(4, context);
///
/// // copy from the host to the device
/// boost::compute::copy_n(values, 4, vec.begin(), queue);
/// \endcode
///
/// Space complexity: \Omega(1)
///
/// \see copy()
template<class InputIterator, class Size, class OutputIterator>
inline OutputIterator copy_n(InputIterator first,
                             Size count,
                             OutputIterator result,
                             command_queue &queue = system::default_queue(),
                             const wait_list &events = wait_list())
{
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    return ::boost::compute::copy(first,
                                  first + static_cast<difference_type>(count),
                                  result,
                                  queue,
                                  events);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COPY_N_HPP

/* copy_n.hpp
r1QStFEoHGXj694BfblHu3Zb5Lxw48XeQ86G2fFFPkHe5nzGyQzQHEWSnlovKvEMeorZBocm1E5mUMYvxWf3+RS78m82IHXTqC+zvmNG9wmgVb7mMrMDUPGPDpyfRrwey+8hO5kNc0SzMvpyThvZp1GMke/abDPNmlaRp30v6O2VgN88WwaAcqZDdq6/kgqlCicWauqk0uEcMTUk9fB/2rLj25KDgrpcKuyqAc43DkPbWgC6C6vAt7Nd3j/Rf9OYNe7fwsYaVkxmd39u9VLYbhqGGa3M8AP4GvW5yo/o6EnOkKJ6hfBxLVxvyu2zg0WgfHuiFiENyL1kWtY9hL5Vp4crRFpnHQ4TlZVhildo/Qu9vxmMBwZw4cqqE0qr+OGSKJSQNGQDSQ130uvRGXdcax79tkgKW1m7FRy32Nf1Kt0sp/lPUUfTazOIDnnuN5E9TlXSMDpy2kJYZVhRVxaNez/Y5Or5bqWrnuVlayFv8XQx3TQx1mQpSBBokcTwsbOu5/PpS1JziQjVxtFDRkXFuGElfFsGmMKI/N8ZyNsCat/AOdnHyZM7XjmHtw==
*/
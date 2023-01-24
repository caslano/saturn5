//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_IOTA_HPP
#define BOOST_COMPUTE_ALGORITHM_IOTA_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/iterator/counting_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Fills the range [\p first, \p last) with sequential values starting at
/// \p value.
///
/// For example, the following code:
/// \snippet test/test_iota.cpp iota
///
/// Will fill \c vec with the values (\c 0, \c 1, \c 2, \c ...).
///
/// Space complexity: \Omega(1)
template<class BufferIterator, class T>
inline void iota(BufferIterator first,
                 BufferIterator last,
                 const T &value,
                 command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<BufferIterator>::value);
    T count = static_cast<T>(detail::iterator_range_size(first, last));

    copy(
        ::boost::compute::make_counting_iterator(value),
        ::boost::compute::make_counting_iterator(value + count),
        first,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_IOTA_HPP

/* iota.hpp
Ga2rhnJWssJ/B7IAOqP17N8Zo8VWWhbVqTz2d4SvTbUHM3A8N6IwgwYMsH/rZWarVBCjBTK7L5vp1oHvmvKXCN817VbNMXo5M8ae8KEOPTK+lg4To9DZCQygDsFuGWgvOQpXw/3ALjj8c1nMbpxOL1nLYA8JazJmx0tRewBgiGxMZNzwDu4tDTjPNesQG8MM/uFhkD8EMhQwXnmIy4pKuD3WJ2vZ+qows/VlZugB85yr9vrLGZQLEMrbLjdC+ZOrNCjbys5SnQZIX/23dpAuUFL+xiHdmz7dg8DWgyuPGMuCK9+F+69W2gvMgLP8pK3sCVxZwdbptrJxuDHLWwLJGKec9C/1ypunVLVpGJkp7VHtA6m3id8r6Guh2rtH9TdZ7y/a+Bv6uuKdNn21vwsVKPe+w3t735W0LppqgOiinpR/hL9coRGTmt6HX8otb59RDTQqAN068YOIyQTO+2Gc8bt1X4MRzgCwia2mhROZkRbNH0447ZXFzDwsHf+kumWnRbXXwJIuylmclhfouXE6nftdAj2KHOPNgcQix6Mx/jiSO2psLilsT/yJkaKlGNkG8xoDnwuvoR99inJM/p6wT/4RKwRbVX+Xt5KMFSAH3MYXF5Y1OxQWvR9Z1vAkq4V43x3aAXAtOwCY+abM1xi63LsALfBocVOZ71c6rWGB1nAT7gND8XSmVacQb0Qz/diXZOtz2N11xEJpXZ4s
*/
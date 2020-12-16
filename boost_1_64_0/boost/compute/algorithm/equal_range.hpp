//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_EQUAL_RANGE_HPP
#define BOOST_COMPUTE_ALGORITHM_EQUAL_RANGE_HPP

#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/lower_bound.hpp>
#include <boost/compute/algorithm/upper_bound.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns a pair of iterators containing the range of values equal
/// to \p value in the sorted range [\p first, \p last).
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline std::pair<InputIterator, InputIterator>
equal_range(InputIterator first,
            InputIterator last,
            const T &value,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return std::make_pair(
               ::boost::compute::lower_bound(first, last, value, queue),
               ::boost::compute::upper_bound(first, last, value, queue)
           );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_EQUAL_RANGE_HPP

/* equal_range.hpp
97UvHAIHwny9Plrti+AZsBQOgmVwMFwOh8AKtV8Ah8L1cBjcBofr76ER8EE4Ev4CjtLfR6PhM3AifBFOhsfhFGiT1gKYAKfCVDgNNoYzYUd4NuwGz4HD4Ww4Bp4L58A5sBCep/ViLlwDh+n8wnx4M1wAfwyL4HNwDPwjnAD1LFVd6yj6R+bCnGep0ocZufSMmsnl1VCuoIZy5TWUq6yhXFWUXF6MXJcoub01lKuuoVx6Zs3k8mooV3ACuU7R5VdDucoaylXVUG5vDeWqo+QKbKfcmujya3ByuUpMnspdp8+F+nCTytn6XPHDbJgAm8CGsBVMglNhMpwOU+AsWA8Ww/qwHDaAF6i/C2GqjiPS4GUwAK/S60fhLEy1pmuhpisFqsoWPU5o3PZnmKn2RmofBt+Ho9U+W+2Fatf5XdUN0rZd5nd36zjhN9APn4aN4DOa/2dhC/icjhOfh33hb+FAlR8J98Ex8EU4Hr6k+aNM0J85xylpcKHG/4Hm70OYA4/CdvBz2FPdB8Hj2l9/CUfCL+AYtU+CH8Nz1M47McEznE96zvNOHpKBbznPem7XOs3aBUfC2DOfH743dO7zQq5VwNC5z1//mc/x5z3Hn/U8EmXIJtIxC3qc+2zOfPY+7/nkZz07z3hG/q0Eax1xxp71XImb21nP20lj6LxnZO89+ZnP5Wl+PfcZ+cJEc/bzEbiTOLzOfn4uWB74DZ8B3RFO1zOg++Sm1PgM6GP31uwcaD0DmvOfkb+IeO8jXbh3hbFnQVdelHbK50E3xL6bMnQ7Dzr+LOh/7hxoawxphWMpr+YX+Wt8DvT2i9L+6bOgHyaM/Rhmi6wcTD5mDmYd5hrMTsxLmGpMww1pVh/MdEw5ZgtmB2Y35iAmYSPlhRmJmYdZh9mKeRizH/MxJv1iwsDMwqzHbMfswRzBBDZxDTMLsw6zFbMLsx/zMSZwyekzqv9dn3/T+X89gy/vf13n/2VnWmZPfvR/8umNycR0xyzI5vf767JHquxNKPsGOPcMKI9au6ey3eV6glwvN9cnmOtN5P3EWRpOJrSj1piVRMKJ2ouOdc3FS81+kaVGpr1ZB9hE10yN9VqPFrcPn6Td7PGTIG7lxm2eMOim7xTiVmLW72h6HGckyZyVfAaq3z6YRZThttgyLFy4akm5ZzmqfB+vctTrzU5ajhqOdzkamQ5R67UkbY79GZEx+zNy6T9e5rrnsLpLeh3nS3TU9/i6aUK6YjY3ZPwadR8q5i/uxaKqqHzjYs5kUFlCyLEST7qPi+6trekJhZPFu9iLufflM4Np09hi1pgeqmfJp38qaVYuxE/eG+F9ibW+9IqrK2Y96P53kEXrM8p6UeuP+ueXVnd9B/lcsQdSuxN7Lvsm/M0+37o1YZJVnnjU2pz0J+vZ5DTreylFVlN9N3nAAdlZKrmJ9RdfA/8ffZ8n7pN7vyu8b1eGqZPihzkNJj5k3++UABqOv1lr0d9uS9L9RzU9ldYYfu2IG3HsErc5bHUzICUY9h7JU1Q9XlwRvPVmndo9Ev6U5N7Wat7MX5sUdC8xYTf0TbECxLDOzhT3SPh1rUES/l7HuQPLFi1aWax1SdqBSSPhqFskjFQrX8JAdxPdTorLSWL4ndVnJX1J5p3XUilDn6MdEYdpRyxjc2uXZh1wkvj/Ibqg9SaMvJgwmOePbbemvP4m6fmeP40zH65ndiuczhfflX2RTZgDYsKsNmHy0TaRq2EelzRVJ3Th7fpvEcaf0WiPtwvt53yfWAf975tzTrzOKvvTe7asT2TkbfbxbPAnPceFpjQdmcWSFis1EsbSsvC+zmRP78ntKVHnYpoyayDp20roy80+iAekHAYlJ1g=
*/
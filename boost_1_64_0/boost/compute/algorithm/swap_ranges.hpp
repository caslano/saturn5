//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SWAP_RANGES_HPP
#define BOOST_COMPUTE_ALGORITHM_SWAP_RANGES_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Swaps the elements in the range [\p first1, \p last1) with the
/// elements in the range beginning at \p first2.
///
/// Space complexity: \Omega(distance(\p first1, \p last1))
template<class Iterator1, class Iterator2>
inline Iterator2 swap_ranges(Iterator1 first1,
                             Iterator1 last1,
                             Iterator2 first2,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator2>::value);

    typedef typename std::iterator_traits<Iterator1>::value_type value_type;

    Iterator2 last2 = first2 + std::distance(first1, last1);

    ::boost::compute::vector<value_type> tmp(first1, last1, queue);
    ::boost::compute::copy(first2, last2, first1, queue);
    ::boost::compute::copy(tmp.begin(), tmp.end(), first2, queue);

    return last2;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SWAP_RANGES_HPP

/* swap_ranges.hpp
nLskfkaG51Qq+oqie5sHh3JmEodt5/4/aOEsrKGZvsPH3R3KHT1WR/y/JAIBDr8g73xiXh3xdL9NHJsa22kKswoD+07lRmgDU/Sgz1NIkXwb4N+ZjUZikVR9hWpxfwojL9Fzl8MxSAgKyFZnTai6a++wOVTfmJI+4mXnKt95fTJ9LRovngAdcOSId2HB6na8pIZViZWJ5n9GoB3WESh5wSBy/XnV/tM8cHHqSe1rwIKMd8s3o0mMmYZ6tfAJwvx2q6bJHS7bA416nGZd5ikjBXwQKIoF+eBqC1RpKWaVmanebh1xaRd/om1acKyvgHUQKGcniTMaOLs8/D2qufNfQ63KVtC1YuoYZOq+BT3SAVBK2z2+FCW54fGiyZCa3zhVlI3aSuFed62iVC0ib22RmH1CZyePC10WmP42TgyMqW558HDqMH2XFiw56UzacXqdPK74GPWbmfPosky8eA88CcucIKoteMiZp4h4d0g8AA+xMSAe1rWnorVvASVjjWk+DP6B2Q7k6z+5LJ4TQR3iNLxOCLkfWuZTf9zoqIAtr98BvqV22TJjGxAhAw==
*/
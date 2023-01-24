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
UdaAsRQ/u+WfsX7xOLg3LJgmhrakqMPh+rJgN6/pv275gVa1P/zMWTpIwmAcgzEL0EJ4sWZxht4X8IR1nnKNBz6+WEYl8tTewroG4JN/R7xkYtuvi0POUW75v8Eb8Cb8uCzYE76EP9zyklaVdXMLdXOCd7O//Mxu9PTjtpPP8cDUImi10UJbK9gDmqaBJJpqUK+iASvji521S7tvwDwBAP4iO3x5QaAn/HtP0AoNUwyqGf4Y+RT1WD8frnt84GwQfo8FyoQyDFoORQuEspfowsrKXNDFo+wisKg02ohJMMtK8UYbPMEcbdBZqO0O4fcd1M2n1NbDHC9D0RS9m94szDMUzRDK0ow8kusNFFPes1BvPBy3IDLmBvH9CXAVxQwEkgn20eRWKpC3GSu4qnM02+YVRoMqbk5hz9VJpdHFMJjARQy8wH8Q1nr851MEsnw2ZjlbG+8psFaz3bMK81lRGKCzVfC1op07F8N0nRoDCLBZE2XNU94cWOlxdngEX4sod6gLGXwlMcBhaUVnhyj4OtTpoeidgctDUXOAMshSNEof/Dkg1GYK9GPt1VGsB6R+6rulX+ES4p2WzwZWh446QtUO5zZhSmusc7fp69zjKhM2t90PSGM6GscS5k3qk/9JLDhuG/ltzv7/k1d+2IJZuytoJ+1WHn2ArE1Or3yDNH/eT0r9nJ80VjwztFtjOe3l3VSTj2pyW0De0Ww1
*/
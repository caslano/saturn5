//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTIAL_SUM_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTIAL_SUM_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/inclusive_scan.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Calculates the cumulative sum of the elements in the range [\p first,
/// \p last) and writes the resulting values to the range beginning at
/// \p result.
///
/// Space complexity on GPUs: \Omega(n)<br>
/// Space complexity on GPUs when \p first == \p result: \Omega(2n)<br>
/// Space complexity on CPUs: \Omega(1)
template<class InputIterator, class OutputIterator>
inline OutputIterator
partial_sum(InputIterator first,
            InputIterator last,
            OutputIterator result,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    return ::boost::compute::inclusive_scan(first, last, result, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTIAL_SUM_HPP

/* partial_sum.hpp
ULdujN5n1a3a5R69MsJ53N3MGbjO72LbdONyFWVKhcW6FvdPcJ7HPdP+LOa2Htfw7c166TixT/I8a0Vch2ucDKObqJfYp3h2W76IZ3K3gt0l3AVirzDptFZ/j/Ww2EeGn9ltZJtWaV7FbsK3i7imHyT+wz0PW/GuZ3yvhKMkzDCP41x5zd854neinOHdwuoaovuuxsy790iYZ7lCnj5PmnI0+NzvYL02nyj9PPI54FoPMRKugz6X2GWQc5p1bbkcUxyyvixt4Bnh5N2xviwJW19WuJwRXh3hjPCV3+KM8JLIZ4SjT8fWddhUdRCdhc/eiXpW8VzHc6jbuzMN2zHSWc/qn2LWIZ+KvZX5zvO7BnwbDpcR0e/C9pnMYevur7Nt3Wcx8CvMWMZ/5iRTLrPuNt/btK/nSJi7tXzBOEnqz1+T5Rkp7FublteE32Peux4Qe1/uIm1dv+dWmDg3qJ27kVwj1qVOdW6R8H/VOg3Gb27yFKfjN13fCZ4o/s9ZXuq9Dc9q0wmRGrKWXSn+ubj2FvcFunYtnKTf5Ri16RK+zmON5jcWnyyrqcap89smfkuJNV7ykymu1XOC7+FOIVgvCbOWGSJZ3TzWZnH7ESnGhd5vTBlGin+hlUJN9sYMprz6nlrzkyX5kfWs81lDynOhhImmr2E3cW7gWtHSut2IO408O84W1z7woNZPktjtNuWJQNbmFzOOLs5mbS46jtdsCqzP/dyXo2NZPclyibe7ra36a3N9Xnpe0huvdtP+4Wtz01+elPAzw/uLkRuzDjOW/GHfR9Ncvo1nOp9rxa2bY8w555IdOZb8Fuj7+CLMuMB6fLIZc471uP3MW23ejWt9a5wCmZcLcd8l9iS39/OEdb6f3yz2hEhjTcMXua6pu6l8Fk2LXoYQ+ayEhMpDfWu5XdJMC8tD5Hf014h/H2mv8Hmw4DDrpOyQd/SFts5ksReFvaMvidCG9lrI+S28V3/tKHrRUZg8wrIkEf18py+p4RiIKhbsVeWLaymPacOympBnKg0fZ+Rp4sQ+xLX/TzThm5vx0Fzs/bT+nM9FhSb8aDO/eELG+izb33X8tMCWIP6DDvvNPcnxzZ0yqps9fqQcYWNI8mrGEAY3yZ/R0Vf9PdTRd6Q66L5vZ+FH0un3Y9HdVzH47S7Pzjruqz3zX5m3bnX7rv+7Z97fJfXWt2fPe275ZsGpKSPG9I2u7H4puvvsc+jlPlUhOu1IX/++mr8f179ftJj79O8P+Ps2/Tsf84j+vQpzv/7tIy8P6d9x/H2r/t2fv+/Qv/W8Z3Yi6H4xuMKq80uEi4I3KW+dvqp8mATHwRQ4DbaGx8PusAD2Uve+cDwcDCfCaXASnAmnwKUSztZfJXunYLpc36m/qp9evz9sAQfAlmK34+dp/LYu8Ydr/BGa75EwTex2/OqI18df4w/W6w/R62M38dcfIv4sjX+yxj9F4mPX+CWYbRq/QOPHwxm2Hvc1zWEbmAQzYCfYFvaF3eEgmAVHwM4wD3aBo9W/Tr+j7jWBqXIdp37HZNVP1xK2gCnm7GriarwNEs95dnUbLV877R/ttZ67aP/IhBNhRzhF3U9Q94WwA1yi/svU/3SYBS9Tu9Yzeyci17NX8+HTeo7SesZu4vuHRY6fqPGbavxmGh+7iZ89LHI/S9X4rbT8aTBN7Hb8kkNcP1bjx+n14/X62E37rdH4c1zarwXhMmASLITJ9nUZBJGv20eve5xeN1uvi90en4eIP0Pjz9T4J2p87Pb4PET87hq/h8bvKfGxa/xtmBKN/67GT4ZbNP7f9Qz6b+AMSEDRK+qDC2EKrIEt4UoYBc+HsfBC9b9E/S+H8XALbAJ/DpvC22E=
*/
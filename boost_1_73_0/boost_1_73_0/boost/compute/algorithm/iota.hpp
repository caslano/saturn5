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
ao1OwGLFoBAHpwEUntOwp8JyxgMOYCnaA9uRkHJusZTKmiI2Hrhl6FAPFDd1j+60ddBc8eDgJPZr105tPuKY8K4snjkU+dw8miIsK3gTAcKNeXoxHBy/vTw9mg4Ozy4mHC6PAK1K6KclLGyeo/5pB9QiVoLjDoDC5brlOfS8hsfTw6vp0eDk5HBw9J45m6pCksgsIP1Mxs+lC1nfTtVYF99U9XxwOR4GVX18sJmsRmCL0ReNrjA+knFqwaf6NDaG2r5sdH0/lfXQlRlZjMoykCbG4SbQ1hnpPN8rL45L6J3lslEsGs4FKJV737DPSiVspJjHpgL/ghuAXV5JOgn1HNzhy+rWh1zKlNCS+WThWWlfoESb8XD4fjoeTiL/BLT4qDwPT4+54nX1lK0EBH6Ig9mR0plDobmZd5YEp6PYlwU+FhgdzFLGpqPWC8aGy5hIXHYmAcC2NXGMTIjUgyNvB6OTNadyeLS1tYs/7KZwDVfbBxyOcM3gH4ELfGFjRGpIjblUmM6dYMLdLRituIuhM8lVioHXVYk7ki/OVYkmnXPh7zq2OCzTjos2h2qNlHNodKiuRiVlYTg0bFE7zr+N6DQhQvi6Z3NcODn4j/haJRCi3jt9iyJj026G4w458wpJ/LCbOIBx7S2SLFjI
*/
//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MISMATCH_HPP
#define BOOST_COMPUTE_ALGORITHM_MISMATCH_HPP

#include <iterator>
#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/iterator/zip_iterator.hpp>
#include <boost/compute/functional/detail/unpack.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns a pair of iterators pointing to the first position where the
/// range [\p first1, \p last1) and the range starting at \p first2
/// differ.
///
/// Space complexity: \Omega(1)
template<class InputIterator1, class InputIterator2>
inline std::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1,
         InputIterator1 last1,
         InputIterator2 first2,
         command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type value_type;

    ::boost::compute::equal_to<value_type> op;

    InputIterator2 last2 = first2 + std::distance(first1, last1);

    InputIterator1 iter =
        boost::get<0>(
            ::boost::compute::find(
                ::boost::compute::make_transform_iterator(
                    ::boost::compute::make_zip_iterator(
                        boost::make_tuple(first1, first2)
                    ),
                    detail::unpack(op)
                ),
                ::boost::compute::make_transform_iterator(
                    ::boost::compute::make_zip_iterator(
                        boost::make_tuple(last1, last2)
                    ),
                    detail::unpack(op)
                ),
                false,
                queue
            ).base().get_iterator_tuple()
        );

    return std::make_pair(iter, first2 + std::distance(first1, iter));
}

/// \overload
template<class InputIterator1, class InputIterator2>
inline std::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1,
         InputIterator1 last1,
         InputIterator2 first2,
         InputIterator2 last2,
         command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    if(std::distance(first1, last1) < std::distance(first2, last2)){
        return ::boost::compute::mismatch(first1, last1, first2, queue);
    }
    else {
        return ::boost::compute::mismatch(
            first1, first1 + std::distance(first2, last2), first2, queue
        );
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MISMATCH_HPP

/* mismatch.hpp
R9fV//4ovjcEvhe7tcFiaYT6baBy3s9LnI+jgt/Ep00P2H32N2XxH23Of3tH7Gm+oIziDAl/A2VpaY2nR8zCrLQ6a3i0wZ0gskCR2ljTH2nOc3tL7G9FubV5CnxD/JuLvcLEH6b+SHNMDdgfiHLtEypPu1vifEqYuj0oRVKGtSL1q/1G0+1v9VDdbS+K/VzvbXwN+z2mjWcQmvTikDrubL3s6YbE3SCJm0Sov0p6qar3jRYp1DyH9cF0lWdpLnnu5utlTfO+i3xxC19TR//cHNI/92K3Za+qKhervEOSyl3/UtJK98y3tpo0ssPSeN+ZRulKW2ZC0nhV8vugiZ8bFv+AxqeP8gtsIZHDqSQPpxK+pZT/dCSno1XuwiljZctr0EdVR2gX4qbics00kRX2eJG5aYpJw2QhXTgAczzpNZNw2q/wteXHFs9lUjQy4/dJPfzetxRNYTczeu6kT7cL6yN3WEv5LonsuSea76NdfCoXpGnHheST4kk3NLJj4jcxWcsgYg9G1t4ZTzqfXbc/lfJ9qu2FlJRcaynv0YdIWfLqNEmWIz5uxtxXEudST9iYkutMIQ9x1tzqVfOWL0bnmJEZvUXaIEmkP5Oou/ZWDzlzbIl+h3p6Sp2MVjtxq3M8KG67ou73ea2nMC9gAvJMuV6+I8UGZY0LkDXuhaxxVERZ448knXS1B+s71lXWOAX+RcK3FXmnLnq9TnF8Cw5cL+5Hz8W087VMOA7lkHE+b8KymLjEJvFmjn7VH6pfttroNF0ofXi+1Ufs9GbJw37fYsbFO9TKh5gvMT4v73aR8e6I6eP9ucdt3mkFKyS9BdpuwfT2+WKtX/s0jmP/UQt4icQZSv5amLHPF9fSRcvL7bMvKW8GdZtJeV8LlNf7o88C9RAwem4Zcoa22YB5HePm9kqILOuTmFnqVox5Q/yw6z1twxHIjO1wub/tcrm/7XG5v70S4f6213l/k7AyL4mbmdfE/YDtbs9VuOfa8lRhMpBmvJozZhmruOtYDdvfld0kwv6umUewv2vmYfZ3zfx2+7v6aF73a16b1UHWYJMpW15dXpkIiktr5loh9xrpb3pv0nDYQs6CXTbf3I+Nv+bz0OueONOGcg3VYWzO5yRdZ953Jhg5N/mlad5L7LzPqaqOmHcN1zpS3o2/fc9ZamTb5opf6jEp10Y9D7SnJtRDy7XGLtfyxZUrIpVLw/WMWC71dy3XOeLX7ZiU6/KmdQn0wzTH9NZy7bDLxf0tN1K5NFzb8HKZ/Qa/E/9MLaeGJ1fO+dQeQ++If5yZ+99uwD5TkU90KXfuIcpdpIMrThOK1XKzUBB5zMVS7Ij9VMPFyRxPGhHbVcMdVlf4kbRdcE6LCzSYfk/nT9wpF2XwaxlqitkLU76scq4VsRwatoWVpPfpDmLvYiXyr9R7A+RCQ/IsZ0b2kTSQU0t25ne75neGzmlTNb8lJr+i1rx0zqLySPnVsCPVzsnOYm/SYBnW8Lxer3k9Ldn0D8d+jF5at120f+ypyys3n0OOCw2XHnFcvCP+rbWfBMMnHbN+P1DLlSnrWfLDRdooC3HznyTlql1WuqJ8WU25Kix3rLuMbPdACfu6tYvc671R43dxfY4nefXPkjTSsPcT+5s8Z3ndnu3Ns05fCbfXeo1/9XlQ0+qAXdbG/L1MVsbBvQh9xP9d6yWV6Z9m4rQLbw9zrvEY8f+NdbeV5nguI57zjH/nvGX2SP1WwuUxbpoyG2ZyJdmPoOk+wxNKc/p9d+ti+DMrqt5asYf2mykSfj05T5YdU31gPrbpmGLsVVaGPtebPIeukw87ZlU+27FfpMBlTVcYYU1XBKlz3LXOcStx9jdNs/5Ye08=
*/
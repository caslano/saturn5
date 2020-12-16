//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REPLACE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_REPLACE_COPY_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/replace.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Copies the value in the range [\p first, \p last) to the range
/// beginning at \p result while replacing each instance of \p old_value
/// with \p new_value.
///
/// Space complexity: \Omega(1)
///
/// \see replace()
template<class InputIterator, class OutputIterator, class T>
inline OutputIterator
replace_copy(InputIterator first,
             InputIterator last,
             OutputIterator result,
             const T &old_value,
             const T &new_value,
             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<OutputIterator>::difference_type difference_type;

    difference_type count = std::distance(first, last);
    if(count == 0){
        return result;
    }

    // copy data to result
    ::boost::compute::copy(first, last, result, queue);

    // replace in result
    ::boost::compute::replace(result,
                              result + count,
                              old_value,
                              new_value,
                              queue);

    // return iterator to the end of result
    return result + count;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REPLACE_COPY_HPP

/* replace_copy.hpp
vTxC06ZITk3Su2r2GBvP1QKhOyJCN9d1Xp1HMX5X4cGiNVWCIAiCIP52Yvv/vVuDN6MOgiAIgiAIgiAIgiDiQ/j3/21FswtLgq57r9c9QvtfRW4ttO4hKdpMhAss1mQluAZuit4Eodclci8N18PyqH7wVHlcWOYRqy1YzwsgsdG8NmQZfRZr8NeHt2Ea9qnu2QjTtbcK7UsjtLGvM0w7Lzj4pmmPY5aI+IsLwrT50mmYtmqIM/PG3bj3nUJ/cbi+vS7g1ZV7GHwz22A87xV9xHtKw9tg0/fx8m7T+h5BEARBEARBEPsMMfz/Xq3b/9XyBEEQBEEQBEEQBEHEl3D//8ziqUV/Nn5s9Pr//cZ66OmSqjqrpSlyg7GP1hS90Pq3yH23oSe2ZM+snIOozXkIEq34nJpH9pear10j1t7vCGnzbdku9LjU48fLCIo1Ls1onydBEARBEARBEATxDxPt//+Z+Pt/tTxBEARBEARBEARBEPElEXau8N+rJpTjjcBOxSOp5Xl+RK/3SW4Ptk+X17s0Wfaq5T613qVo6X6satdLAUWe48jMzMjOHndiVla5XDlHKXf63ONyyl2BOofbowbSkcb3a2N9nVXocwEHY139BvwkjlHr6zMDmsfnmefxV6faZF/A45UUvFM4yVo2BDHBSwodttz8/Cm5thmOqQWz8opmFjCwH8u35mfqGsm8D+ViT/izCZiXwPFeHJ8+jLGMG/Q1+gUOh0d1Opz1To/XWemVHB6/R8PcxCTrupF4Rz2zFZ6ZZ0c5m3WwGJ/VvFwVT0sR4xXgaf1YCs8HAZDZrKetZlaWijbZeVuGoF6NX0WE+npJdah1AT2WueRm0My1+lF0Pq/Lm5CCvKNPYaDBpWQ4VA3jjhPkm2LNwHEZr78ImqJOS7Arkh/9QIUDUZ8uej/Pl4YR7oe07rxVznr+wuAhyFcD3Vau+zC+t5HNKlDrBWw0xnpgcjLrkclH8nkeSAB9rGYm8LFCfVbePrQdaaG2h/b7d+FYCL3ilYwlJ6w//91Xfv3x2q7Gq44Y9Pjis/GViEU8XSl7KcOyfN3zTafUb6vakbMc7x/m6WOuP3nNZzNWbx+0u989P224YhRj3/P0USs+f3D4pr4/vVw49/25h5fX4d3Td+vp1pL3lp89ovBQ/xFrZ+bmfFGLNvH0aQWuIZ+XdaX1CwzddNHYnS8wdhFPP+HC3K4Pv/x5UsuhrdveGr48CePH0++5uaqoNfG7j9asHPHrLc2XQ3POsXp67XUfXOzcnL772h+l5flbxk5lzD1KT6/rl31Q6Rr3xltXrJi9am1lMWO3H6OnL8hb/+g3Bw+68439jx+09tBbhzP2Ca9//JzhD7gLli1NffnF49885wncpPdG6Olr37//4WuvctjP+2T5qR27hn3FWL979PTrLyne+cyhi5dkPOm4s3/txPWMDcCYHvJLf9Yy2sJycCyBabBmWNsEC1sEa8e1Vpx3wDphFThP2t2frUuzsOQxKAfzwhbAmmFtsC5YQ7qFtcBWw0qOtzA3bB1saIaFpcFOhpXDvLCyk1AOx5GodxeOAzJRBjYf1g7rgG2GdcESsyzsEJgdeTUcV8BWwdphFUg7JBvlYG/DNsG6YLehfm8O0mFLYBtgyWMtLAMWgC2AzUdZgiAIgiAIgiD2Tjz8f92pVvHt+3D/P+FP+v8D4f9fkwwf8szS4pIihw3V7XVOQL++bhJjPVx2zMoOzhkMzUIcOzFnsCBBvNsNdhBsAqwFV9zLgnMGRSU2Rx765HF6PfMkhrZPsuZO5iPG/fg8lJ/H847iPnRqbB8a+U+03sDzMlaQxX3kUDuSLD23oy2sHSW4K7hHcLA=
*/
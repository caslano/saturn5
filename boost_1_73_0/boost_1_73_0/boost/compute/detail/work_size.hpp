//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_WORK_SIZE_HPP
#define BOOST_COMPUTE_DETAIL_WORK_SIZE_HPP

#include <cmath>

namespace boost {
namespace compute {
namespace detail {

// Given a total number of values (count), a number of values to
// process per thread (vtp), and a number of threads to execute per
// block (tpb), this function returns the global work size to be
// passed to clEnqueueNDRangeKernel() for a 1D algorithm.
inline size_t calculate_work_size(size_t count, size_t vpt, size_t tpb)
{
    size_t work_size = static_cast<size_t>(std::ceil(float(count) / vpt));
    if(work_size % tpb != 0){
        work_size += tpb - work_size % tpb;
    }
    return work_size;
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_WORK_SIZE_HPP

/* work_size.hpp
69koziaziwBnhLIlmh7QOJWSSkxgpJe58xVJ0mA3DXRSmjhkbCaUE/N7y9VmHPu5ENGXD8TnVmrjC5KQR0l2c20I7Y1WhVTrV3OlUnoXtbxHSDsiwkdBw4EZVTNNuLNASebok+GgvGAswN6UJ0wmtCODpWteNbc3VL60kyUJ0SYJhLwOXdmTp68FkQGnG5hbGqAuo8kF6T0Qfqm7RAz4mGPjkhchawKHZ3cuo1bU45ZXQq23wUQGY8aWd+YBZvUGwe6sQ6JyalkralLym0CAdyppqShLsKJXhPyi5op/dXK4o46Bo0samtaQgfRqsZgup7PJb7epnyawjn9utbnPsgC+/mgUJJJuljymHfuKoxOKxpWhELkTVIYXcPbDFPDG5L1CNsAliIm7OGydjG0wl6XMjzLwEWoqtZEFhtXHVZVlQlGEaC/I+3I+Hy1/7l98HowvX4zKqpW1X2BxRGHT1k4SUoC0iNypycRCfmBCQbDmA0gk+3iiDC/RMFItN29YEjdEaaYP3iEc3Grnk6ISrY3YkCyl3TFgL+TQJfjOHul75yuMFRq67hKgV1xyp/eUlhwFDkpssKOAk+cgOQ01upoQm/u6sAmFzuRQonBtGHEPy5O7csi1nEwXy/FgMbs4+fb0rpyePguZO9lN
*/
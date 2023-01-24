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
m78aZPd7k1M3720vm+MDzZMm187cuLp3tW+YyFKPOmW2mxuNaX2yb80heVcOjkkfv8V5XZ3GpU2jmt58XKdTkd+wMttVeX6jOxud2HInL2zhb6sK7Lbsrn7FcNj461N+1NlVN32x0+74YQcPuzxu+Kuh+aX8nEzrZQ0fvam+PfxMuz2Gu2c/TrNdXrv38Frnht5dvrKxTrZZH+sjO7tPeHb6geW4022/PvmkxPHkU8Ntd61Or7w3aspPzt8wdrtKizofP66/umRzl95PdPRstmiaNzW7ci3LM+n6jXqttjptvLNry4E7Z4+ci767LTS/g9Xa7bNvP3P7X95PuZveve0eYB3rsuG8/aBura607aJ3d6u35f59U995Tns61iVh78izr2paJRSdeKrv0ytu5PKlX07t4mgenqPr+01YgZXOvs9HLHz/xGL7opgpc4xurm7we92C9S7XHDdEjE08vXWDZbuEZZPXl9Wwid20b3+Xht077+j5KqOvyznJ3v4pezPn9I7xLD3e7Uur9pL1nc8PvqX3tdvMh9FRvb7xsj2cWaN9eb89A7f4r+ztc2mq9dGNJpcLE96dOnF17xNn5wsOS/ZtGZLkvm7JgyGDw+tPHe+4JdL/vkFMrbg33y6vm7V0rW1sjG3R7LKVRWsHZb81Dku02rO/4dBR2s65JocG+NRsVO6wMjp4UGDzjdWCipYk19vzyin2ub1Z
*/
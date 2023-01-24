//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_BALLOT_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_BALLOT_HPP

#include <boost/compute/context.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/algorithm/reduce.hpp>
#include <boost/compute/functional/detail/nvidia_ballot.hpp>
#include <boost/compute/functional/detail/nvidia_popcount.hpp>
#include <boost/compute/detail/meta_kernel.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Predicate>
inline size_t count_if_with_ballot(InputIterator first,
                                   InputIterator last,
                                   Predicate predicate,
                                   command_queue &queue)
{
    size_t count = iterator_range_size(first, last);
    size_t block_size = 32;
    size_t block_count = count / block_size;
    if(block_count * block_size != count){
        block_count++;
    }

    const ::boost::compute::context &context = queue.get_context();

    ::boost::compute::vector<uint_> counts(block_count, context);

    ::boost::compute::detail::nvidia_popcount<uint_> popc;
    ::boost::compute::detail::nvidia_ballot<uint_> ballot;

    meta_kernel k("count_if_with_ballot");
    k <<
        "const uint gid = get_global_id(0);\n" <<

        "bool value = false;\n" <<
        "if(gid < count)\n" <<
        "    value = " << predicate(first[k.var<const uint_>("gid")]) << ";\n" <<

        "uint bits = " << ballot(k.var<const uint_>("value")) << ";\n" <<

        "if(get_local_id(0) == 0)\n" <<
            counts.begin()[k.var<uint_>("get_group_id(0)") ]
                << " = " << popc(k.var<uint_>("bits")) << ";\n";

    k.add_set_arg<const uint_>("count", count);

    k.exec_1d(queue, 0, block_size * block_count, block_size);

    uint_ result;
    ::boost::compute::reduce(
        counts.begin(),
        counts.end(),
        &result,
        queue
    );
    return result;
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_BALLOT_HPP

/* count_if_with_ballot.hpp
FheKwKFCj8YzS6d3/V2Qatr4R6/iH73GK8+yJJWCh89NWZBYpT08b0F9mlHtIYLgFoaPdvnBWD0JdHQ7CPIJ7g8psnwZ029o6PN8AfCH0PsOtXf+LGInXcRONkiyAUWbQLRkOQhbc5y/ciyaJTl3BKYBqcFUsgF4kYyVVtWSbw+MkULVqcjw/QDfJEfe0xRtP8UqhWpgd021IK8Z6Ba+UAqJllT1JpR7s5R/NJ3W1Ik+6BJPEtGLG/E8wLEjOH0RnF6ksPICEd3WB8NASbZ+u7fBEFplNyzJzNXkIADpQTElHecPLZbyh8B1SKFtQPq/MwaPMaMEqpsT4mTjNghufwgttwNBinrQuQNNKEuy5eV2jOEYj32bmIoJo9Y+8BBvA5we5ekPfW8MHjwzAYiDSSN4Fl5sEOt5bDuqCxEr4HduNdbC6O3VXkAasYvnpo4fdNCT+aePEw07/yT1FobdvMSdaIDPUUgwPemqWMVyFGQQY50iOc2vFKUYhPKfiBDBlDvNz9ANFfvAGEGhDLUiwCiKci+Kj8IEmhhFtBD/mYH/jMZ/hlC01HOkpezljfQ74gfpFZUZj+D76j2d76JvDix/p7tox1Zdne/a8e5lne+icIA5aZPvWoysTrVQsYaOZm+o3iI6PxNCGLkVRRUGI67rvJzGUF4KdDZuDnJx5Gl8hAefOpe7W+RIQ8mFxVZakGLQrNj/8gtiDFoe
*/
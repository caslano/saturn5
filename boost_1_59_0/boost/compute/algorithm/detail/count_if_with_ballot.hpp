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
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
*/
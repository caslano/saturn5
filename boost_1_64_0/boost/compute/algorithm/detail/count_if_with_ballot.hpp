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
rai59PxTdYd6sJYcSyTpaf73FuF3Tzg9gRmtq6FFRENVCmG/n6TawuVlqO9h4KUBn+Wr+W572Ez7FMeH48gdbPzTa6R4L6mRSjJuiMFrEQlcckCEZRBW7h9V2dWjfnM7u9vc+e9+16vQjGiGyHqGE2YVaOP1O1eX4Nw/+o/QotwFwEc/fDopoVq8bd2TAA2DMa8IltcV6P4D8LDc4wbD4RWBWeJLM+EQ5xm0MCLAyXMasXRAETAgxyVeXY1Uyg4bEv2u42xq9EJqgSwA020OITAw6Su3xCgk88Y1n27lssb7FrmmX/P+a/yrQ0GfEzSC7xUe0dvg8KSSxYd4g3aVUc0BdVQPPAW3GdmRENSLkZBCQiRyZts6lprHKXAhm/58+N/OVwMnK6YMct8XcuYxvCxw7apqR4AGcMgR8V8hPCVsZLyN1127Wyn8CR044jEofVW77S2l7Vgts1Jr7TXFTeMtS34LhA0BNL+A7qAVu64ZGJFmPHlqbt1gsJd7nxnQogfJVPr9EeRGz2cjpbP1a3u5UlcHlcY+InOm74FMuogzNx68mqzp/e07Vw==
*/
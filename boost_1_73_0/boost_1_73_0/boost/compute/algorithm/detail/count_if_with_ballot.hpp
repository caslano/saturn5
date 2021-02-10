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
aH4zuZ/DQ38264/nC5j8Bf3xosX7ZzS+ptnglFUDPlUaDVWhgW8qwTE/Sv4dlT6/AdfPdFMLy1ONG7XFtCRKqefvIfwAd0xnJQ33+UUIoeAr5w2/xJfxzwffd0zWTIRBnNzAuH83DL6K+Q6ab8cPMrOH1l5oahcDH0JNN4YG08Mli/FkmoyS4AcuM1HnCFcOvJnC8mMQDO5nt3eZoo2vJT3xLnDWbDW2CJwRzlwNren09yBmuU96PUwGs9F0PpqMg5mHMlTcmqQkYVmMDoKWxbSp3U0LbR3moL24mZMdF4Kk8IiBczMVZrygph4xsMKWmrwDpMCGj8bjR0MSkFYrklnwUGJzGRxClCTzFdLGEdAXVi3LHiMgmRAwWzMuA9JLQZe12IPANRNOD1xu1aM/iqfTH9W5Kb05eX/qjqtkU9tBZirI08Tl+nVj6Xryh3NbtbvRKPJ1WqdgR1GAhbMTzcLFC9sIUjNpClIFXX+VVmuvDFem8PlsSXfTYS3QJyTV6OjFbHyWDqttCfFENJD4mU/sZBaMPD8Fl+jo6Ka1Ow7lYnIPlm8Q8lr7A39BjeBTbSxIZT3zwY7UzKUP6JSSMSFW1Ae6hGTmb18/cLPh/H42hn/7t/fDg4m2+4omdY0SNdHUYTTt5JJuqoJl
*/
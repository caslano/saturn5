//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_THREADS_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_THREADS_HPP

#include <numeric>

#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/container/vector.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Predicate>
class count_if_with_threads_kernel : meta_kernel
{
public:
    typedef typename
        std::iterator_traits<InputIterator>::value_type
        value_type;

    count_if_with_threads_kernel()
        : meta_kernel("count_if_with_threads")
    {
    }

    void set_args(InputIterator first,
                  InputIterator last,
                  Predicate predicate)

    {
        typedef typename std::iterator_traits<InputIterator>::value_type T;

        m_size = detail::iterator_range_size(first, last);

        m_size_arg = add_arg<const ulong_>("size");
        m_counts_arg = add_arg<ulong_ *>(memory_object::global_memory, "counts");

        *this <<
            // thread parameters
            "const uint gid = get_global_id(0);\n" <<
            "const uint block_size = size / get_global_size(0);\n" <<
            "const uint start = block_size * gid;\n" <<
            "uint end = 0;\n" <<
            "if(gid == get_global_size(0) - 1)\n" <<
            "    end = size;\n" <<
            "else\n" <<
            "    end = block_size * gid + block_size;\n" <<

            // count values
            "uint count = 0;\n" <<
            "for(uint i = start; i < end; i++){\n" <<
                decl<const T>("value") << "="
                    << first[expr<uint_>("i")] << ";\n" <<
                if_(predicate(var<const T>("value"))) << "{\n" <<
                    "count++;\n" <<
                "}\n" <<
            "}\n" <<

            // write count
            "counts[gid] = count;\n";
    }

    size_t exec(command_queue &queue)
    {
        const device &device = queue.get_device();
        const context &context = queue.get_context();

        size_t threads = device.compute_units();

        const size_t minimum_block_size = 2048;
        if(m_size / threads < minimum_block_size){
            threads = static_cast<size_t>(
                          (std::max)(
                              std::ceil(float(m_size) / minimum_block_size),
                              1.0f
                          )
                      );
        }

        // storage for counts
        ::boost::compute::vector<ulong_> counts(threads, context);

        // exec kernel
        set_arg(m_size_arg, static_cast<ulong_>(m_size));
        set_arg(m_counts_arg, counts.get_buffer());
        exec_1d(queue, 0, threads, 1);

        // copy counts to the host
        std::vector<ulong_> host_counts(threads);
        ::boost::compute::copy(counts.begin(), counts.end(), host_counts.begin(), queue);

        // return sum of counts
        return std::accumulate(host_counts.begin(), host_counts.end(), size_t(0));
    }

private:
    size_t m_size;
    size_t m_size_arg;
    size_t m_counts_arg;
};

// counts values that match the predicate using one thread per block. this is
// optimized for cpu-type devices with a small number of compute units.
template<class InputIterator, class Predicate>
inline size_t count_if_with_threads(InputIterator first,
                                    InputIterator last,
                                    Predicate predicate,
                                    command_queue &queue)
{
    count_if_with_threads_kernel<InputIterator, Predicate> kernel;
    kernel.set_args(first, last, predicate);
    return kernel.exec(queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_THREADS_HPP

/* count_if_with_threads.hpp
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
*/
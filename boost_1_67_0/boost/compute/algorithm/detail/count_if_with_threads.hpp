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
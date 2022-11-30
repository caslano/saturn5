//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REDUCE_HPP
#define BOOST_COMPUTE_ALGORITHM_REDUCE_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/array.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/algorithm/copy_n.hpp>
#include <boost/compute/algorithm/detail/inplace_reduce.hpp>
#include <boost/compute/algorithm/detail/reduce_on_gpu.hpp>
#include <boost/compute/algorithm/detail/reduce_on_cpu.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/memory/local_buffer.hpp>
#include <boost/compute/type_traits/result_of.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class BinaryFunction>
size_t reduce(InputIterator first,
              size_t count,
              OutputIterator result,
              size_t block_size,
              BinaryFunction function,
              command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type
        input_type;
    typedef typename
        boost::compute::result_of<BinaryFunction(input_type, input_type)>::type
        result_type;

    const context &context = queue.get_context();
    size_t block_count = count / 2 / block_size;
    size_t total_block_count =
        static_cast<size_t>(std::ceil(float(count) / 2.f / float(block_size)));

    if(block_count != 0){
        meta_kernel k("block_reduce");
        size_t output_arg = k.add_arg<result_type *>(memory_object::global_memory, "output");
        size_t block_arg = k.add_arg<input_type *>(memory_object::local_memory, "block");

        k <<
            "const uint gid = get_global_id(0);\n" <<
            "const uint lid = get_local_id(0);\n" <<

            // copy values to local memory
            "block[lid] = " <<
                function(first[k.make_var<uint_>("gid*2+0")],
                         first[k.make_var<uint_>("gid*2+1")]) << ";\n" <<

            // perform reduction
            "for(uint i = 1; i < " << uint_(block_size) << "; i <<= 1){\n" <<
            "    barrier(CLK_LOCAL_MEM_FENCE);\n" <<
            "    uint mask = (i << 1) - 1;\n" <<
            "    if((lid & mask) == 0){\n" <<
            "        block[lid] = " <<
                         function(k.expr<input_type>("block[lid]"),
                                  k.expr<input_type>("block[lid+i]")) << ";\n" <<
            "    }\n" <<
            "}\n" <<

            // write block result to global output
            "if(lid == 0)\n" <<
            "    output[get_group_id(0)] = block[0];\n";

        kernel kernel = k.compile(context);
        kernel.set_arg(output_arg, result.get_buffer());
        kernel.set_arg(block_arg, local_buffer<input_type>(block_size));

        queue.enqueue_1d_range_kernel(kernel,
                                      0,
                                      block_count * block_size,
                                      block_size);
    }

    // serially reduce any leftovers
    if(block_count * block_size * 2 < count){
        size_t last_block_start = block_count * block_size * 2;

        meta_kernel k("extra_serial_reduce");
        size_t count_arg = k.add_arg<uint_>("count");
        size_t offset_arg = k.add_arg<uint_>("offset");
        size_t output_arg = k.add_arg<result_type *>(memory_object::global_memory, "output");
        size_t output_offset_arg = k.add_arg<uint_>("output_offset");

        k <<
            k.decl<result_type>("result") << " = \n" <<
                first[k.expr<uint_>("offset")] << ";\n" <<
            "for(uint i = offset + 1; i < count; i++)\n" <<
            "    result = " <<
                     function(k.var<result_type>("result"),
                              first[k.var<uint_>("i")]) << ";\n" <<
            "output[output_offset] = result;\n";

        kernel kernel = k.compile(context);
        kernel.set_arg(count_arg, static_cast<uint_>(count));
        kernel.set_arg(offset_arg, static_cast<uint_>(last_block_start));
        kernel.set_arg(output_arg, result.get_buffer());
        kernel.set_arg(output_offset_arg, static_cast<uint_>(block_count));

        queue.enqueue_task(kernel);
    }

    return total_block_count;
}

template<class InputIterator, class BinaryFunction>
inline vector<
    typename boost::compute::result_of<
        BinaryFunction(
            typename std::iterator_traits<InputIterator>::value_type,
            typename std::iterator_traits<InputIterator>::value_type
        )
    >::type
>
block_reduce(InputIterator first,
             size_t count,
             size_t block_size,
             BinaryFunction function,
             command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type
        input_type;
    typedef typename
        boost::compute::result_of<BinaryFunction(input_type, input_type)>::type
        result_type;

    const context &context = queue.get_context();
    size_t total_block_count =
        static_cast<size_t>(std::ceil(float(count) / 2.f / float(block_size)));
    vector<result_type> result_vector(total_block_count, context);

    reduce(first, count, result_vector.begin(), block_size, function, queue);

    return result_vector;
}

// Space complexity: O( ceil(n / 2 / 256) )
template<class InputIterator, class OutputIterator, class BinaryFunction>
inline void generic_reduce(InputIterator first,
                           InputIterator last,
                           OutputIterator result,
                           BinaryFunction function,
                           command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type
        input_type;
    typedef typename
        boost::compute::result_of<BinaryFunction(input_type, input_type)>::type
        result_type;

    const device &device = queue.get_device();
    const context &context = queue.get_context();

    size_t count = detail::iterator_range_size(first, last);

    if(device.type() & device::cpu){
        array<result_type, 1> value(context);
        detail::reduce_on_cpu(first, last, value.begin(), function, queue);
        boost::compute::copy_n(value.begin(), 1, result, queue);
    }
    else {
        size_t block_size = 256;

        // first pass
        vector<result_type> results = detail::block_reduce(first,
                                                           count,
                                                           block_size,
                                                           function,
                                                           queue);

        if(results.size() > 1){
            detail::inplace_reduce(results.begin(),
                                   results.end(),
                                   function,
                                   queue);
        }

        boost::compute::copy_n(results.begin(), 1, result, queue);
    }
}

template<class InputIterator, class OutputIterator, class T>
inline void dispatch_reduce(InputIterator first,
                            InputIterator last,
                            OutputIterator result,
                            const plus<T> &function,
                            command_queue &queue)
{
    const context &context = queue.get_context();
    const device &device = queue.get_device();

    // reduce to temporary buffer on device
    array<T, 1> value(context);
    if(device.type() & device::cpu){
        detail::reduce_on_cpu(first, last, value.begin(), function, queue);
    }
    else {
        reduce_on_gpu(first, last, value.begin(), function, queue);
    }

    // copy to result iterator
    copy_n(value.begin(), 1, result, queue);
}

template<class InputIterator, class OutputIterator, class BinaryFunction>
inline void dispatch_reduce(InputIterator first,
                            InputIterator last,
                            OutputIterator result,
                            BinaryFunction function,
                            command_queue &queue)
{
    generic_reduce(first, last, result, function, queue);
}

} // end detail namespace

/// Returns the result of applying \p function to the elements in the
/// range [\p first, \p last).
///
/// If no function is specified, \c plus will be used.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param result iterator pointing to the output
/// \param function binary reduction function
/// \param queue command queue to perform the operation
///
/// The \c reduce() algorithm assumes that the binary reduction function is
/// associative. When used with non-associative functions the result may
/// be non-deterministic and vary in precision. Notably this affects the
/// \c plus<float>() function as floating-point addition is not associative
/// and may produce slightly different results than a serial algorithm.
///
/// This algorithm supports both host and device iterators for the
/// result argument. This allows for values to be reduced and copied
/// to the host all with a single function call.
///
/// For example, to calculate the sum of the values in a device vector and
/// copy the result to a value on the host:
///
/// \snippet test/test_reduce.cpp sum_int
///
/// Note that while the the \c reduce() algorithm is conceptually identical to
/// the \c accumulate() algorithm, its implementation is substantially more
/// efficient on parallel hardware. For more information, see the documentation
/// on the \c accumulate() algorithm.
///
/// Space complexity on GPUs: \Omega(n)<br>
/// Space complexity on CPUs: \Omega(1)
///
/// \see accumulate()
template<class InputIterator, class OutputIterator, class BinaryFunction>
inline void reduce(InputIterator first,
                   InputIterator last,
                   OutputIterator result,
                   BinaryFunction function,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    if(first == last){
        return;
    }

    detail::dispatch_reduce(first, last, result, function, queue);
}

/// \overload
template<class InputIterator, class OutputIterator>
inline void reduce(InputIterator first,
                   InputIterator last,
                   OutputIterator result,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type T;

    if(first == last){
        return;
    }

    detail::dispatch_reduce(first, last, result, plus<T>(), queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REDUCE_HPP

/* reduce.hpp
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
*/
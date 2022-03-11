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
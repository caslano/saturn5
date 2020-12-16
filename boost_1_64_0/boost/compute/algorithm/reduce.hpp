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
b/Rt23dN739pPW+jBc41vY02cvYa5gDM8ZjpG735JE888cQTTzzxxJN/ouyY+f+xhaUspd1e8/+Hh5wBMF2/k4/S8ozCjMOneLfg3E3/g0aMHj7isIOGDlKV5g6d5mN0L7TGIaU05nATdez3Kr8b9ibUVHNcdR8+buMmjjmhROcFAnGjxD4ce4nY83Sc24Q3+r3Hh+TXzupq5s6eErdo7EZ3K9cb1Pv7gvjbRtfthXp9jaw91C14zXvgKuu3JZ1JY0om1KTjw3anhEk04+G37KZrs8X/j+V21zPs1Jkca/SoUqfY48xYqJRdxkOTzHioqQ+HLu/SKFUYr4kfhBmPzyb39jwB9dd0Lrf21DiklGG1wD/QDkWq7zfg38DU5TdiP5D2b2XCM1JiwndqJXvw610XfnucKXeRY256oq47SMQ0VnMiPrmtXMtbUqBlzTbz/VJWDZ+ocydO3crqh13rwDl/a/yNjux66zWfKvYss27+eJ37C5RZ8nO0M+FEupNhC5gGi/Apjlhu2tlR9jFmbnOWxNnV1rrQNFq7tbn6JWPX+0fsMSF1Uz5mYlmB1k0g/Lnm/jyytcz3h/SPk805gA9I2K9D5q/yzdxunMQ7SO2BdLKc/UzPFbhN0vk5dG6xnP/M2QJVmk9g7c1R/vmOOszHOvSaa7/MC+mXum9C7VIPjr56tM6TH6nnrfSB5X6f3aXN8pmGDWu3mvYq0fbS9tHwXc18c1exd7ClvBK22JzjMMSE72LOZ+0i9nQJ3zSsPyfCPcV/N1vbUOPvac4oCZ8b7yb+je3QOc5EjdtP/C6lHrpbvaiJRG2DceK+ymqCzxCrm7YNK6n2CK61SJE1GyVmPdACiXOnrM2gnUU6iluSlSxuNY7Z4pZgj2fE+RZqOmTdhtHPMlbCvI0Oz27qhgYacbsWl5Fmn9axIWeYHFfHfVr+OTHSCp5Zov2iJOTZPh57qdhpK7OXBjrvd9N3sndWrfSqX6ElPAOfKqmvisLMfPe+k+3sOxq+uVnXtFTsa9SOlvkUaXtp62nhfcnEb2rmMJ8We2NmxO2I53uWSJpHOM/p1N/j1uKXY+a9izTsPlazkPT87z+WOdvzC8nzDLUH4oxw7rvTdq4Qv76ua28SoCX+15jziFZJ2s/QB2I1jKkTrQNjl36QUudnPO2uz/hpwXYP6kH35i132LzlkzV6Wh7MKj/63CZ735U1oWhi4plX/XfnLSPoU9e9TvoeDY/SeTqz10l1kEfBpTAevgiT4XK4O3wJpqt9T7XvC1fAYfBVOAK+Bg+Hz8JRat8McwPvkXCw5h8DD8BYqlvdzwfgrvAh2B4+AgfChXAQfBgepPbNMMPS9zKYqOlGwXaabhzh5BwnLRdG4lWbdxx5t5J4zUWXO6Lzdq3hZbAvvBwOgFfAQ+EcmAevhUfDubAcXq/zmDfCSlgJb4Hz4FJ4E3wezoer4C3wI3gr/BTeBj+Dt8Of4B0wjmu7E7aAd8E0eLeWIyXwuw2O1HK04e9m+ruZq/U4DHaDR8DecCTsB/NgNjwKHgKPhsfCMXAsHAsnwXw4GR4Py2ABPBlOgKfBiXA6LNJ528lwASyGd8OT4H3wHLgCTodvwXPhB/A8+AkshVtgGYzxvzfBneFpMBVO0/KfDveCZ8BMeCbsrjq0e8GzYB84I9D/zG8adab11MHf/0J0mGOsltrvk2EreDBsC1vBDLg7zIJ7wP1hCjwAttF+2lb7RarWX5rWXwd4EkzX+usEp8E9YQXsDGfAveBFsAu8DO4Nr4IZ8HrYFc6DmVq/+8C7YDf4AOwOF8He8Em4LxR97fAZ2A8ug/vDV+AA7YcHwrfhQPg1HAS3whzYQOY=
*/
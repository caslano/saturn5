//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_ON_GPU_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_ON_GPU_HPP

#include <boost/compute/kernel.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/memory/local_buffer.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class BinaryOperator>
class local_scan_kernel : public meta_kernel
{
public:
    local_scan_kernel(InputIterator first,
                      InputIterator last,
                      OutputIterator result,
                      bool exclusive,
                      BinaryOperator op)
        : meta_kernel("local_scan")
    {
        typedef typename std::iterator_traits<InputIterator>::value_type T;

        (void) last;

        bool checked = true;

        m_block_sums_arg = add_arg<T *>(memory_object::global_memory, "block_sums");
        m_scratch_arg = add_arg<T *>(memory_object::local_memory, "scratch");
        m_block_size_arg = add_arg<const cl_uint>("block_size");
        m_count_arg = add_arg<const cl_uint>("count");
        m_init_value_arg = add_arg<const T>("init");

        // work-item parameters
        *this <<
            "const uint gid = get_global_id(0);\n" <<
            "const uint lid = get_local_id(0);\n";

        // check against data size
        if(checked){
            *this <<
                "if(gid < count){\n";
        }

        // copy values from input to local memory
        if(exclusive){
            *this <<
                decl<const T>("local_init") << "= (gid == 0) ? init : 0;\n" <<
                "if(lid == 0){ scratch[lid] = local_init; }\n" <<
                "else { scratch[lid] = " << first[expr<cl_uint>("gid-1")] << "; }\n";
        }
        else{
            *this <<
                "scratch[lid] = " << first[expr<cl_uint>("gid")] << ";\n";
        }

        if(checked){
            *this <<
                "}\n"
                "else {\n" <<
                "    scratch[lid] = 0;\n" <<
                "}\n";
        }

        // wait for all threads to read from input
        *this <<
            "barrier(CLK_LOCAL_MEM_FENCE);\n";

        // perform scan
        *this <<
            "for(uint i = 1; i < block_size; i <<= 1){\n" <<
            "    " << decl<const T>("x") << " = lid >= i ? scratch[lid-i] : 0;\n" <<
            "    barrier(CLK_LOCAL_MEM_FENCE);\n" <<
            "    if(lid >= i){\n" <<
            "        scratch[lid] = " << op(var<T>("scratch[lid]"), var<T>("x")) << ";\n" <<
            "    }\n" <<
            "    barrier(CLK_LOCAL_MEM_FENCE);\n" <<
            "}\n";

        // copy results to output
        if(checked){
            *this <<
                "if(gid < count){\n";
        }

        *this <<
            result[expr<cl_uint>("gid")] << " = scratch[lid];\n";

        if(checked){
            *this << "}\n";
        }

        // store sum for the block
        if(exclusive){
            *this <<
                "if(lid == block_size - 1 && gid < count) {\n" <<
                "    block_sums[get_group_id(0)] = " <<
                       op(first[expr<cl_uint>("gid")], var<T>("scratch[lid]")) <<
                       ";\n" <<
                "}\n";
        }
        else {
            *this <<
                "if(lid == block_size - 1){\n" <<
                "    block_sums[get_group_id(0)] = scratch[lid];\n" <<
                "}\n";
        }
    }

    size_t m_block_sums_arg;
    size_t m_scratch_arg;
    size_t m_block_size_arg;
    size_t m_count_arg;
    size_t m_init_value_arg;
};

template<class T, class BinaryOperator>
class write_scanned_output_kernel : public meta_kernel
{
public:
    write_scanned_output_kernel(BinaryOperator op)
        : meta_kernel("write_scanned_output")
    {
        bool checked = true;

        m_output_arg = add_arg<T *>(memory_object::global_memory, "output");
        m_block_sums_arg = add_arg<const T *>(memory_object::global_memory, "block_sums");
        m_count_arg = add_arg<const cl_uint>("count");

        // work-item parameters
        *this <<
            "const uint gid = get_global_id(0);\n" <<
            "const uint block_id = get_group_id(0);\n";

        // check against data size
        if(checked){
            *this << "if(gid < count){\n";
        }

        // write output
        *this <<
            "output[gid] = " <<
                op(var<T>("block_sums[block_id]"), var<T>("output[gid] ")) << ";\n";

        if(checked){
            *this << "}\n";
        }
    }

    size_t m_output_arg;
    size_t m_block_sums_arg;
    size_t m_count_arg;
};

template<class InputIterator>
inline size_t pick_scan_block_size(InputIterator first, InputIterator last)
{
    size_t count = iterator_range_size(first, last);

    if(count == 0)        { return 0; }
    else if(count <= 1)   { return 1; }
    else if(count <= 2)   { return 2; }
    else if(count <= 4)   { return 4; }
    else if(count <= 8)   { return 8; }
    else if(count <= 16)  { return 16; }
    else if(count <= 32)  { return 32; }
    else if(count <= 64)  { return 64; }
    else if(count <= 128) { return 128; }
    else                  { return 256; }
}

template<class InputIterator, class OutputIterator, class T, class BinaryOperator>
inline OutputIterator scan_impl(InputIterator first,
                                InputIterator last,
                                OutputIterator result,
                                bool exclusive,
                                T init,
                                BinaryOperator op,
                                command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type
        input_type;
    typedef typename
        std::iterator_traits<InputIterator>::difference_type
        difference_type;
    typedef typename
        std::iterator_traits<OutputIterator>::value_type
        output_type;

    const context &context = queue.get_context();
    const size_t count = detail::iterator_range_size(first, last);

    size_t block_size = pick_scan_block_size(first, last);
    size_t block_count = count / block_size;

    if(block_count * block_size < count){
        block_count++;
    }

    ::boost::compute::vector<input_type> block_sums(block_count, context);

    // zero block sums
    input_type zero;
    std::memset(&zero, 0, sizeof(input_type));
    ::boost::compute::fill(block_sums.begin(), block_sums.end(), zero, queue);

    // local scan
    local_scan_kernel<InputIterator, OutputIterator, BinaryOperator>
        local_scan_kernel(first, last, result, exclusive, op);

    ::boost::compute::kernel kernel = local_scan_kernel.compile(context);
    kernel.set_arg(local_scan_kernel.m_scratch_arg, local_buffer<input_type>(block_size));
    kernel.set_arg(local_scan_kernel.m_block_sums_arg, block_sums);
    kernel.set_arg(local_scan_kernel.m_block_size_arg, static_cast<cl_uint>(block_size));
    kernel.set_arg(local_scan_kernel.m_count_arg, static_cast<cl_uint>(count));
    kernel.set_arg(local_scan_kernel.m_init_value_arg, static_cast<output_type>(init));

    queue.enqueue_1d_range_kernel(kernel,
                                  0,
                                  block_count * block_size,
                                  block_size);

    // inclusive scan block sums
    if(block_count > 1){
        scan_impl(block_sums.begin(),
                  block_sums.end(),
                  block_sums.begin(),
                  false,
                  init,
                  op,
                  queue
        );
    }

    // add block sums to each block
    if(block_count > 1){
        write_scanned_output_kernel<input_type, BinaryOperator>
            write_output_kernel(op);
        kernel = write_output_kernel.compile(context);
        kernel.set_arg(write_output_kernel.m_output_arg, result.get_buffer());
        kernel.set_arg(write_output_kernel.m_block_sums_arg, block_sums);
        kernel.set_arg(write_output_kernel.m_count_arg, static_cast<cl_uint>(count));

        queue.enqueue_1d_range_kernel(kernel,
                                      block_size,
                                      block_count * block_size,
                                      block_size);
    }

    return result + static_cast<difference_type>(count);
}

template<class InputIterator, class OutputIterator, class T, class BinaryOperator>
inline OutputIterator dispatch_scan(InputIterator first,
                                    InputIterator last,
                                    OutputIterator result,
                                    bool exclusive,
                                    T init,
                                    BinaryOperator op,
                                    command_queue &queue)
{
    return scan_impl(first, last, result, exclusive, init, op, queue);
}

template<class InputIterator, class T, class BinaryOperator>
inline InputIterator dispatch_scan(InputIterator first,
                                   InputIterator last,
                                   InputIterator result,
                                   bool exclusive,
                                   T init,
                                   BinaryOperator op,
                                   command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    if(first == result){
        // scan input in-place
        const context &context = queue.get_context();

        // make a temporary copy the input
        size_t count = iterator_range_size(first, last);
        vector<value_type> tmp(count, context);
        copy(first, last, tmp.begin(), queue);

        // scan from temporary values
        return scan_impl(tmp.begin(), tmp.end(), first, exclusive, init, op, queue);
    }
    else {
        // scan input to output
        return scan_impl(first, last, result, exclusive, init, op, queue);
    }
}

template<class InputIterator, class OutputIterator, class T, class BinaryOperator>
inline OutputIterator scan_on_gpu(InputIterator first,
                                  InputIterator last,
                                  OutputIterator result,
                                  bool exclusive,
                                  T init,
                                  BinaryOperator op,
                                  command_queue &queue)
{
    if(first == last){
        return result;
    }

    return dispatch_scan(first, last, result, exclusive, init, op, queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_ON_GPU_HPP

/* scan_on_gpu.hpp
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
*/
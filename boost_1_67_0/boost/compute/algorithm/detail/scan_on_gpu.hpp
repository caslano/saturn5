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
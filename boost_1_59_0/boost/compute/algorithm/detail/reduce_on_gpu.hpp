//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_ON_GPU_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_ON_GPU_HPP

#include <iterator>

#include <boost/compute/utility/source.hpp>
#include <boost/compute/program.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/vendor.hpp>
#include <boost/compute/detail/parameter_cache.hpp>
#include <boost/compute/detail/work_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/utility/program_cache.hpp>

namespace boost {
namespace compute {
namespace detail {

/// \internal
/// body reduction inside a warp
template<typename T,bool isNvidiaDevice>
struct ReduceBody
{
    static std::string body()
    {
        std::stringstream k;
        // local reduction
        k << "for(int i = 1; i < TPB; i <<= 1){\n" <<
             "   barrier(CLK_LOCAL_MEM_FENCE);\n"  <<
             "   uint mask = (i << 1) - 1;\n"      <<
             "   if((lid & mask) == 0){\n"         <<
             "       scratch[lid] += scratch[lid+i];\n" <<
             "   }\n" <<
            "}\n";
        return k.str();
    }
};

/// \internal
/// body reduction inside a warp
/// for nvidia device we can use the "unsafe"
/// memory optimisation
template<typename T>
struct ReduceBody<T,true>
{
    static std::string body()
    {
        std::stringstream k;
        // local reduction
        // we use TPB to compile only useful instruction
        // local reduction when size is greater than warp size
        k << "barrier(CLK_LOCAL_MEM_FENCE);\n" <<
        "if(TPB >= 1024){\n" <<
            "if(lid < 512) { sum += scratch[lid + 512]; scratch[lid] = sum;} barrier(CLK_LOCAL_MEM_FENCE);}\n" <<
         "if(TPB >= 512){\n" <<
            "if(lid < 256) { sum += scratch[lid + 256]; scratch[lid] = sum;} barrier(CLK_LOCAL_MEM_FENCE);}\n" <<
         "if(TPB >= 256){\n" <<
            "if(lid < 128) { sum += scratch[lid + 128]; scratch[lid] = sum;} barrier(CLK_LOCAL_MEM_FENCE);}\n" <<
         "if(TPB >= 128){\n" <<
            "if(lid < 64) { sum += scratch[lid + 64]; scratch[lid] = sum;} barrier(CLK_LOCAL_MEM_FENCE);} \n" <<

        // warp reduction
        "if(lid < 32){\n" <<
            // volatile this way we don't need any barrier
            "volatile __local " << type_name<T>() << " *lmem = scratch;\n" <<
            "if(TPB >= 64) { lmem[lid] = sum = sum + lmem[lid+32];} \n" <<
            "if(TPB >= 32) { lmem[lid] = sum = sum + lmem[lid+16];} \n" <<
            "if(TPB >= 16) { lmem[lid] = sum = sum + lmem[lid+ 8];} \n" <<
            "if(TPB >=  8) { lmem[lid] = sum = sum + lmem[lid+ 4];} \n" <<
            "if(TPB >=  4) { lmem[lid] = sum = sum + lmem[lid+ 2];} \n" <<
            "if(TPB >=  2) { lmem[lid] = sum = sum + lmem[lid+ 1];} \n" <<
        "}\n";
        return k.str();
    }
};

template<class InputIterator, class Function>
inline void initial_reduce(InputIterator first,
                           InputIterator last,
                           buffer result,
                           const Function &function,
                           kernel &reduce_kernel,
                           const uint_ vpt,
                           const uint_ tpb,
                           command_queue &queue)
{
    (void) function;
    (void) reduce_kernel;

    typedef typename std::iterator_traits<InputIterator>::value_type Arg;
    typedef typename boost::tr1_result_of<Function(Arg, Arg)>::type T;

    size_t count = std::distance(first, last);
    detail::meta_kernel k("initial_reduce");
    k.add_set_arg<const uint_>("count", uint_(count));
    size_t output_arg = k.add_arg<T *>(memory_object::global_memory, "output");

    k <<
        k.decl<const uint_>("offset") << " = get_group_id(0) * VPT * TPB;\n" <<
        k.decl<const uint_>("lid") << " = get_local_id(0);\n" <<

        "__local " << type_name<T>() << " scratch[TPB];\n" <<

        // private reduction
        k.decl<T>("sum") << " = 0;\n" <<
        "for(uint i = 0; i < VPT; i++){\n" <<
        "    if(offset + lid + i*TPB < count){\n" <<
        "        sum = sum + " << first[k.var<uint_>("offset+lid+i*TPB")] << ";\n" <<
        "    }\n" <<
        "}\n" <<

        "scratch[lid] = sum;\n" <<

        // local reduction
        ReduceBody<T,false>::body() <<

        // write sum to output
        "if(lid == 0){\n" <<
        "    output[get_group_id(0)] = scratch[0];\n" <<
        "}\n";

    const context &context = queue.get_context();
    std::stringstream options;
    options << "-DVPT=" << vpt << " -DTPB=" << tpb;
    kernel generic_reduce_kernel = k.compile(context, options.str());
    generic_reduce_kernel.set_arg(output_arg, result);

    size_t work_size = calculate_work_size(count, vpt, tpb);

    queue.enqueue_1d_range_kernel(generic_reduce_kernel, 0, work_size, tpb);
}

template<class T>
inline void initial_reduce(const buffer_iterator<T> &first,
                           const buffer_iterator<T> &last,
                           const buffer &result,
                           const plus<T> &function,
                           kernel &reduce_kernel,
                           const uint_ vpt,
                           const uint_ tpb,
                           command_queue &queue)
{
    (void) function;

    size_t count = std::distance(first, last);

    reduce_kernel.set_arg(0, first.get_buffer());
    reduce_kernel.set_arg(1, uint_(first.get_index()));
    reduce_kernel.set_arg(2, uint_(count));
    reduce_kernel.set_arg(3, result);
    reduce_kernel.set_arg(4, uint_(0));

    size_t work_size = calculate_work_size(count, vpt, tpb);

    queue.enqueue_1d_range_kernel(reduce_kernel, 0, work_size, tpb);
}

template<class InputIterator, class T, class Function>
inline void reduce_on_gpu(InputIterator first,
                          InputIterator last,
                          buffer_iterator<T> result,
                          Function function,
                          command_queue &queue)
{
    const device &device = queue.get_device();
    const context &context = queue.get_context();

    detail::meta_kernel k("reduce");
    k.add_arg<const T*>(memory_object::global_memory, "input");
    k.add_arg<const uint_>("offset");
    k.add_arg<const uint_>("count");
    k.add_arg<T*>(memory_object::global_memory, "output");
    k.add_arg<const uint_>("output_offset");

    k <<
        k.decl<const uint_>("block_offset") << " = get_group_id(0) * VPT * TPB;\n" <<
        "__global const " << type_name<T>() << " *block = input + offset + block_offset;\n" <<
        k.decl<const uint_>("lid") << " = get_local_id(0);\n" <<

        "__local " << type_name<T>() << " scratch[TPB];\n" <<
        // private reduction
        k.decl<T>("sum") << " = 0;\n" <<
        "for(uint i = 0; i < VPT; i++){\n" <<
        "    if(block_offset + lid + i*TPB < count){\n" <<
        "        sum = sum + block[lid+i*TPB]; \n" <<
        "    }\n" <<
        "}\n" <<

        "scratch[lid] = sum;\n";

    // discrimination on vendor name
    if(is_nvidia_device(device))
        k << ReduceBody<T,true>::body();
    else
        k << ReduceBody<T,false>::body();

    k <<
        // write sum to output
         "if(lid == 0){\n" <<
         "    output[output_offset + get_group_id(0)] = scratch[0];\n" <<
         "}\n";

    std::string cache_key = std::string("__boost_reduce_on_gpu_") + type_name<T>();

    // load parameters
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    uint_ vpt = parameters->get(cache_key, "vpt", 8);
    uint_ tpb = parameters->get(cache_key, "tpb", 128);

    // reduce program compiler flags
    std::stringstream options;
    options << "-DT=" << type_name<T>()
            << " -DVPT=" << vpt
            << " -DTPB=" << tpb;

    // load program
    boost::shared_ptr<program_cache> cache =
        program_cache::get_global_cache(context);

    program reduce_program = cache->get_or_build(
        cache_key, options.str(), k.source(), context
    );

    // create reduce kernel
    kernel reduce_kernel(reduce_program, "reduce");

    size_t count = std::distance(first, last);

    // first pass, reduce from input to ping
    buffer ping(context, std::ceil(float(count) / vpt / tpb) * sizeof(T));
    initial_reduce(first, last, ping, function, reduce_kernel, vpt, tpb, queue);

    // update count after initial reduce
    count = static_cast<size_t>(std::ceil(float(count) / vpt / tpb));

    // middle pass(es), reduce between ping and pong
    const buffer *input_buffer = &ping;
    buffer pong(context, static_cast<size_t>(count / vpt / tpb * sizeof(T)));
    const buffer *output_buffer = &pong;
    if(count > vpt * tpb){
        while(count > vpt * tpb){
            reduce_kernel.set_arg(0, *input_buffer);
            reduce_kernel.set_arg(1, uint_(0));
            reduce_kernel.set_arg(2, uint_(count));
            reduce_kernel.set_arg(3, *output_buffer);
            reduce_kernel.set_arg(4, uint_(0));

            size_t work_size = static_cast<size_t>(std::ceil(float(count) / vpt));
            if(work_size % tpb != 0){
                work_size += tpb - work_size % tpb;
            }
            queue.enqueue_1d_range_kernel(reduce_kernel, 0, work_size, tpb);

            std::swap(input_buffer, output_buffer);
            count = static_cast<size_t>(std::ceil(float(count) / vpt / tpb));
        }
    }

    // final pass, reduce from ping/pong to result
    reduce_kernel.set_arg(0, *input_buffer);
    reduce_kernel.set_arg(1, uint_(0));
    reduce_kernel.set_arg(2, uint_(count));
    reduce_kernel.set_arg(3, result.get_buffer());
    reduce_kernel.set_arg(4, uint_(result.get_index()));

    queue.enqueue_1d_range_kernel(reduce_kernel, 0, tpb, tpb);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_ON_GPU_HPP

/* reduce_on_gpu.hpp
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
*/
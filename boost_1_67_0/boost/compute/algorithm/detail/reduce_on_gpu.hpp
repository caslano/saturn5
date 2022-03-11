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
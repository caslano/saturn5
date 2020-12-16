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
yyvV3s+7Xeexxi93qN4c0Pn7xCNqR9RvPv8qHZ+/6vnRLtXbFt2v1/fYV+5Qf4B+b0OxnFRP52uedoPen7bmjzrPNV586lM63uoPj9+tfB/RfU3Vq6esGl+oHV/xiOpdh+brN6pcKzQP+wv1AzROWPNZjWf0/oa5S9Vf1nP9j25UvXhU/SHle/ZvlC/NVz3xoOqv1pPZ87Lavf3Kl47rhuW6zin/uw+rvqu+TdM48071a6fOUT9f4+GNev/F439Sv3yD0W5P/7HOpyHd1/mTvn+u+ZAZuu93i87/R987ReNz9Wcesug5HI13GtTf+Zn6jSFdJ+3G+0e3Xazrs1X9zw9pu9rnzerHPanr4M6jmgfUfNIG3Te/rV3jx1mad7vAuI97QO3C/ITmt3+gcZ3Cu/dylZPa4TW6vzo3qvP1TD0HvVLjj/P03I76U7u1HsIdG3ReezS+3Kz2+6Dma3XfZ95Nek+qX/OoW9Ve3qD+mOrJzk9oHmGxrj9Xqj19Uf1m3d+e8iWNx/RetEeXq5+wV+fTyxqv7lI7NE/t3fXqt67R9XnSG/S8mp4n1fzo9i26rj6ofv3PJ2ucqHkfzUdco3juO6J57ZTqlV3l+nvdB9N7Cqf+XO1IaR5a855Pr9A4JqXnAUvXjTv1/sy/qJ8T0/l9ueqZ4m3Xcz5zbzHu792ufvj52zWv+AfNE+r68sAujat0vq+5XPX6AuVD49d5vC93ajG9pXmRq9VvP6r53h/q+0fTNM99W+k5Kt1Pfk79uGrVO7WH6x5UOJtP0zyqxjFqt3ZpvL1xuo73I5oH0rzfmRmNiy5TveR5yDOKn/+Oru9TNG92QM/fu/Vc6T6dj2/UcZym673a0Qu1fvtsk477PM2f/VHtfljPper+zPmVqgfqP2+dpvhUL5/U3w8v1nzcB/S+g0+qv6fnsXYe1Pha161J31e5PK/+ucrz9iMqnx/pOqL2Y0Ve7YbmVXbr/t6ST6ucvUqnvvd8ka5zF6o9vO/Lem7tGp13Gufer3Zozb2ap9mm82dymZ47Nn7feZrxHpZ1i9TOnqb2aYpZ98d1nS2t0/8u4773gS9qfBA8TfVY/b0rNd9zv+7TaJ50pfrHd6hffnvlFKNftvuNGmfqPswflZ+Vyq+eD9/3SX1/Sd8nf1TX7/bTdbxv0vyFxhePah5+ywy1KwHV8xtON9L/kPr/l+i8Unux+Xpdp7+lcetcXU/1nNadV6ufp+vvkumqz6qf95bmw28tXd90vus9Y7verXbzZj3HoPKZq/Njeul5xR+pP6P1oJfpftUTs4z1Mu5UP2CO+pvL1B9+QuP6lS26vms8cljznE/p+1L36jmzWyZpfKn79XP+rXb7pdPVj1W91P2vLe/Tfc9J6mfu0nNbv9O8kurnLWo3nyxXuY+rXVqo/spizX9pXLlrcyndGoct1PHW+O7M3yv/mhd6QOfl4z9TP+ha9Y/a9D2CVfqezGPq7y/V8wofVP+SccK24vfutV7oYeV/s8ar83eaXzkvNup4XqXncM8+qH7tzRpvrlf++3Vcf656NVP9xwWnq3+u8eunVd9U7o//Tu8n6ta8kZ5nnKr++3TV2wU63pv36DmW7xjjin2Nmgf6m+YvE3o+arP6FbzHw1xsbxT/wk+p/mqed+eYrue3apx+WPXggMaZ89SfUj/igSc1X7RA89aX6Pqm93tM69D5r+v5tts1jpmn66Luay9Re7WmdN9xtq6f3fpe4c90Hqk92+M27muu0XzzFI3zD+h+xErNp03R89cPaB7p2XvUPxzQ+TtF1+ttmsfVebItq/SU7hu1af78gM5PnX/blmh+/iY9f9as+5J7NG7eoflbXX8=
*/
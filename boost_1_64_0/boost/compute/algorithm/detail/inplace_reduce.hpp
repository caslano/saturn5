//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_INPLACE_REDUCE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_INPLACE_REDUCE_HPP

#include <iterator>

#include <boost/utility/result_of.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/memory/local_buffer.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class BinaryFunction>
inline void inplace_reduce(Iterator first,
                           Iterator last,
                           BinaryFunction function,
                           command_queue &queue)
{
    typedef typename
        std::iterator_traits<Iterator>::value_type
        value_type;

    size_t input_size = iterator_range_size(first, last);
    if(input_size < 2){
        return;
    }

    const context &context = queue.get_context();

    size_t block_size = 64;
    size_t values_per_thread = 8;
    size_t block_count = input_size / (block_size * values_per_thread);
    if(block_count * block_size * values_per_thread != input_size)
        block_count++;

    vector<value_type> output(block_count, context);

    meta_kernel k("inplace_reduce");
    size_t input_arg = k.add_arg<value_type *>(memory_object::global_memory, "input");
    size_t input_size_arg = k.add_arg<const uint_>("input_size");
    size_t output_arg = k.add_arg<value_type *>(memory_object::global_memory, "output");
    size_t scratch_arg = k.add_arg<value_type *>(memory_object::local_memory, "scratch");
    k <<
        "const uint gid = get_global_id(0);\n" <<
        "const uint lid = get_local_id(0);\n" <<
        "const uint values_per_thread =\n"
            << uint_(values_per_thread) << ";\n" <<

        // thread reduce
        "const uint index = gid * values_per_thread;\n" <<
        "if(index < input_size){\n" <<
            k.decl<value_type>("sum") << " = input[index];\n" <<
            "for(uint i = 1;\n" <<
                 "i < values_per_thread && (index + i) < input_size;\n" <<
                 "i++){\n" <<
            "    sum = " <<
                     function(k.var<value_type>("sum"),
                              k.var<value_type>("input[index+i]")) << ";\n" <<
            "}\n" <<
            "scratch[lid] = sum;\n" <<
        "}\n" <<

        // local reduce
        "for(uint i = 1; i < get_local_size(0); i <<= 1){\n" <<
        "    barrier(CLK_LOCAL_MEM_FENCE);\n" <<
        "    uint mask = (i << 1) - 1;\n" <<
        "    uint next_index = (gid + i) * values_per_thread;\n"
        "    if((lid & mask) == 0 && next_index < input_size){\n" <<
        "        scratch[lid] = " <<
                     function(k.var<value_type>("scratch[lid]"),
                              k.var<value_type>("scratch[lid+i]")) << ";\n" <<
        "    }\n" <<
        "}\n" <<

        // write output for block
        "if(lid == 0){\n" <<
        "    output[get_group_id(0)] = scratch[0];\n" <<
        "}\n"
        ;

    const buffer *input_buffer = &first.get_buffer();
    const buffer *output_buffer = &output.get_buffer();

    kernel kernel = k.compile(context);

    while(input_size > 1){
        kernel.set_arg(input_arg, *input_buffer);
        kernel.set_arg(input_size_arg, static_cast<uint_>(input_size));
        kernel.set_arg(output_arg, *output_buffer);
        kernel.set_arg(scratch_arg, local_buffer<value_type>(block_size));

        queue.enqueue_1d_range_kernel(kernel,
                                      0,
                                      block_count * block_size,
                                      block_size);

        input_size =
            static_cast<size_t>(
                std::ceil(float(input_size) / (block_size * values_per_thread)
            )
        );

        block_count = input_size / (block_size * values_per_thread);
        if(block_count * block_size * values_per_thread != input_size)
            block_count++;

        std::swap(input_buffer, output_buffer);
    }

    if(input_buffer != &first.get_buffer()){
        ::boost::compute::copy(output.begin(),
                               output.begin() + 1,
                               first,
                               queue);
    }
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_INPLACE_REDUCE_HPP

/* inplace_reduce.hpp
t+w29v+4PLElJ53nEHj0weR4zKP+2LIbLpAXVPxSvLrAvvKTu6bDQcPl2fLELrhn3bPwKj9bXAlH/sJzBr6K67IGpHp1NL7nKfgh+LQYp+OJivjTKv0A88TxwPdxfaU8fKL9H43Ptd8FpZ7v7/DfMPr8mng1OvVjVQX83Nj4nKwT/1IQvH6M0+TrZ4qD1erGD4j3lfRxTnr+tkfxROJRzRPsPsY478lkjPvFGPOuSsZYp3HEmgwvIH/dZh9uwaO9xD6S9fYLP5ypI7wMV16nDg4HlgZvFNeJC13j4Ad9CbOq6CledOUAdWT+YflI/VJ/hA8eTN8Xzv833m22uPqgfuVV7GWn/uv58p0XvCeB7+p9gz1VsJtidjhfPKogr+v2wR+KM9E3Esf74I1G+cMr8g16OwuPk4+PHjWMvvxIveVd67kQTkzqCquTPyZ9wu9cAOf5/2yFm/H2/PaoP6rrDuOPV8vTvGdWfw68Cjc2+76ov+fOgn++kJ5X7vshr/L3d8fx5D7fFI/XwZnkWrzT/PK42k36D+7YJ32uLHXtKnnROv0oL9uv1+BD9+m4E17Zws78//uSevau/tVwML+L75nVmcbFnWvxbpEfxViXnep3Ueb9K/3FT7K3fvBTB/8gfh68Wz53CdzRD//Gn9WH/4rj68nnqMiPEvk4fw+eaMRiz9UA/83U31WoX68/fjcbP4YPaHlWf2Mvvutcz4sHbHtBXbXe/jUMlNfjjy6AKw9Rp8RzjynGS3TAPXfyV/fpvyxVz0/i4gGx3lvEr5ni9pPqBMHPx/xf4ud+kp7Xu1CcjD7hOO/iTLzUPx88YTw/HnX6+55zvu/H4KemyOPoTfvv6YU6cGU1/1EHX5fp+5/HflvZ9xb7t13eswe+6rEPn8Fl3n+tyZIPfZG8wu/F+f/hT9vZT9J/kxvXwZFL7jbPO/jModY9gz/T/zOkHq8zGr8yWB70tLrXdfAAP7To+njPN94roceBF+J58/ido8X9venY8JfkvLjfl32Pn2pM4u/guE+e+gz/fbA66izyrSffs8mv6QP2y1/UnCIO/VO+F/xqzD+bnK7Fc4qHC8y/bgr/OwoOwnvWiCe1kVfF87GHsotjjDpkbvreYov4g89uu4v9Bc8e4zP6HbPVT97Df81WxzB24Xc7LsF7Vsh7WuTZL6mTxTwh5zn89vv6wN6EE+1b4RH45aj3xjpfJN8f4fv44caj9BkF3xZyv0b/2en86hnq/vXs41hx7xJy72BHjfoZnoPL4aYd/GDtk3BSEkeGZSfPsZPfDH8c68v8DsAqeHgm/LABXoMvyrzntO0kuOWv2el5nmMl/q/V2GncYyz8vvVsxfNdpM7SF2PknfBrxJd43tC/GA/ijz7SH4pfn/QEPv5h+3As/n9jMsb9zyDv++GfqfDRk/x68AYx73rP3yu/jfpJzId36DoInvwSfzvFerboxz8NPl0jTwmeNua503qWZn7vSd4ovuXG/WPsdL55F45JcGvcZ0u+ehA8hscdqc+v0v2a6tWTP6cuPh1PkDsgnf969cbF+oOOibgUebO4fod8KeJkzGdfxkyG5xaJr+Sw7Mvim/rF8jn806zUv698T12EHW6brh/5mNRuW/Zmw2H60Pdll/jdyi30mX8uIN/qGfh/fMDY75L3LfYv+hTj+Fn69Ya5bws+Zo51wCnl9L4Ojih+Cw8Yx2OUX494hp1+y7wj6e3x/OPINE5UHAoPzBXv/6Xushv/N0PcneP5M7/vUxp4OfJzOKUvGWOeF8j9E3VcPPKozHtt9/FX/8YPZvPLX3L+7fxgZ5wf+QJ89TjerdF5md+v2QhH/guP7HmqP49v+1w6Llg=
*/
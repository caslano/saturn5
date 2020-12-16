//---------------------------------------------------------------------------//
// Copyright (c) 2016 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_ON_CPU_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_ON_CPU_HPP

#include <algorithm>

#include <boost/compute/buffer.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/parameter_cache.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/result_of.hpp>
#include <boost/compute/algorithm/detail/serial_reduce.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class BinaryFunction>
inline void reduce_on_cpu(InputIterator first,
                          InputIterator last,
                          OutputIterator result,
                          BinaryFunction function,
                          command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type T;
    typedef typename
        ::boost::compute::result_of<BinaryFunction(T, T)>::type result_type;

    const device &device = queue.get_device();
    const uint_ compute_units = queue.get_device().compute_units();

    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    std::string cache_key =
        "__boost_reduce_cpu_" + boost::lexical_cast<std::string>(sizeof(T));

    // for inputs smaller than serial_reduce_threshold
    // serial_reduce algorithm is used
    uint_ serial_reduce_threshold =
        parameters->get(cache_key, "serial_reduce_threshold", 16384 * sizeof(T));
    serial_reduce_threshold =
        (std::max)(serial_reduce_threshold, uint_(compute_units));

    const context &context = queue.get_context();
    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return;
    }
    else if(count < serial_reduce_threshold) {
        return serial_reduce(first, last, result, function, queue);
    }

    meta_kernel k("reduce_on_cpu");
    buffer output(context, sizeof(result_type) * compute_units);

    size_t count_arg = k.add_arg<uint_>("count");
    size_t output_arg =
        k.add_arg<result_type *>(memory_object::global_memory, "output");

    k <<
        "uint block = " <<
            "(uint)ceil(((float)count)/get_global_size(0));\n" <<
        "uint index = get_global_id(0) * block;\n" <<
        "uint end = min(count, index + block);\n" <<

        k.decl<result_type>("result") << " = " << first[k.var<uint_>("index")] << ";\n" <<
        "index++;\n" <<
        "while(index < end){\n" <<
             "result = " << function(k.var<T>("result"),
                                     first[k.var<uint_>("index")]) << ";\n" <<
             "index++;\n" <<
        "}\n" <<
        "output[get_global_id(0)] = result;\n";

    size_t global_work_size = compute_units;
    kernel kernel = k.compile(context);

    // reduction to global_work_size elements
    kernel.set_arg(count_arg, static_cast<uint_>(count));
    kernel.set_arg(output_arg, output);
    queue.enqueue_1d_range_kernel(kernel, 0, global_work_size, 0);

    // final reduction
    reduce_on_cpu(
        make_buffer_iterator<result_type>(output),
        make_buffer_iterator<result_type>(output, global_work_size),
        result,
        function,
        queue
    );
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_ON_CPU_HPP

/* reduce_on_cpu.hpp
/THzO7P8VvEk31+qDncBnDwXDzIRL2RdrRX+70MJXB24Lsb+eJrjcpLzkud+Fz5+yHOX048Mz9vJXvMHpJ+X4Msyz3sLfLE5xqjv8fdlcEQf/qSBvibvy30hrvslnBf4Luadxr6ifhnH9Zt0n6CfmD42/42/j32J69QH6+zLwsqMPdC7CnH2OfFO/jdpP/wYPes5h13yP3VzUl58FL6t4i/w/wf6TA6HJ1rxpPDBMvFiHT/ZtCw5HmPIN44/Qj9WZnAivYSzJi1WX8QvtM+JMeo0Kf+way8eFm8zBC/UXYT/Heh5ThCXHoVXMn28+L2CI70HM0+d4Bn7rJ4/5hDxbjI8cR68PiLeo0jkFL9PEHJVtzk7+tNCDsP4fXinaRo/fJW65Il4vRE+x7rjumu8V6hOkq+fo3qMuHwJedinmlcTfxrr+gB/OZUd40tKlsCLgRPjOX+B11krX3/Ycx7BD4S+xn1Cn+O6fdR7TpHXW1fuXPXnwXDS9fDkqXn6+vGrteSdea97snrqftZ3A393gr6WB+Jz4H95mPpeA7w9qzc7XWeF5zlfP/WX8I+l9Mrz931sHwrpZQf81OT9jExd7DE8y8H2xVieI7+0D72Hk/uw9HhWHvv5jbh0hbh5pboNfnz57fblIn0TZfwP/ajy3meJfpZa+lcZdYIYJ8jTxePu8CdxHv4vP4+/D9wTctgunz6K3v1Ov1aaNyY8Snre2SsT/YnnzPzOsTp+63z5esgh5tOPmYVvbj6O/Yefj3nm6qMqjTHqrepP4usI+K3MuKiKXVSrx/1E3bGVPu4bnwPf6lMQN9fpR8oKnj3O34zndX0BvqlBnOi8PhlDfvmD8cL8KDw2Yq24enGePBqvleh7/7iuTj5TiCcL3BnzrYJXP5IPneH9Gfa1AG7bEX0dcV0D3H2p55R3TL8CrzAEP/g/9u4/vo2ygON4NjLJsGinnXZYtGjBoZsULdhJp5100mk2CgtStGMZS6HTbstYxjLMXKZFOwkatGjRIEGDFu00aJFMMpZJpkU7Cdpp0eCCBgmSsQw61rF08RPum22wzv99vai+X2W9y/PrnnvueZ673KN6tu6Tyvftyl9B9eBcXY91nZh/j65rms85rO/zLdmn+4IaBz85pPkAlc/G83Q+aJw3z63y1n2tszs1HtJ84qOaX9npUT+81J/TuhUHDhvzKFuuVD/arXLs13j2sL4f9wbVk2t0X+kFXQ/UT73qMj23o/mKw/PVzzis6+qjGte4jPt6m/Uc3hyV95m8n+LKYj5vVvu2UfU6WLo/pfbEpfZW/fsVX1E5rNZ917tVn57QdeUGfZ9b/ZOF31P/40O6f6fnnqf/QuPMQ+p/btPn36n2I6Tn1Ejn5cXjpHqxU/nY9WmVk+Lfo+/3T1uq8+fTxrzXOTM0H3uZzjeN225X+e55TuHu1bhF7dOecZVjqb35lL7Xt1vPAaqcpq3Tc/W71Z/S+XPVw5oHqVD7f5P6Y4t13PW5nZpv33lUz9uOa353s8YTGq9sXaX5A+6HjBWfvy+1t+smG/mcr3qv+eBJ6437zbeXng/U/NYCXR/3XKJx21eUjumap9Hz0gvUj79P16O5v9V9lHM0f9Ku+bwfWYzxVVb3ofZovrdH7YfmVXb/WfVsn75f+lO9B+6XahcY399afM5c/c9dm9U//6bKV+fF1N2av1T7f9ulet5X/cgn1C6eo/n+dd/R/MJWHV89R/OA7pOt+YHuZ+t+7FM6L/ct0Hmr/u463U8/8KzqS6kfv1r3K1V+K5arnXpM8xdKzy6NQ3d9XuXfq+eC/qx5Yz1/tULvRZirdnZcz33tulbpU79mzjrVG+X/idJ8ifo=
*/
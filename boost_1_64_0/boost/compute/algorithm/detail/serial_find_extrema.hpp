//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_FIND_EXTREMA_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_FIND_EXTREMA_HPP

#include <boost/compute/command_queue.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/container/detail/scalar.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Compare>
inline InputIterator serial_find_extrema(InputIterator first,
                                         InputIterator last,
                                         Compare compare,
                                         const bool find_minimum,
                                         command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    const context &context = queue.get_context();

    meta_kernel k("serial_find_extrema");

    k <<
        k.decl<value_type>("value") << " = " << first[k.expr<uint_>("0")] << ";\n" <<
        k.decl<uint_>("value_index") << " = 0;\n" <<
        "for(uint i = 1; i < size; i++){\n" <<
        "  " << k.decl<value_type>("candidate") << "="
             << first[k.expr<uint_>("i")] << ";\n" <<

        "#ifndef BOOST_COMPUTE_FIND_MAXIMUM\n" <<
        "  if(" << compare(k.var<value_type>("candidate"),
                           k.var<value_type>("value")) << "){\n" <<
        "#else\n" <<
        "  if(" << compare(k.var<value_type>("value"),
                           k.var<value_type>("candidate")) << "){\n" <<
        "#endif\n" <<

        "    value = candidate;\n" <<
        "    value_index = i;\n" <<
        "  }\n" <<
        "}\n" <<
        "*index = value_index;\n";

    size_t index_arg_index = k.add_arg<uint_ *>(memory_object::global_memory, "index");
    size_t size_arg_index = k.add_arg<uint_>("size");

    std::string options;
    if(!find_minimum){
        options = "-DBOOST_COMPUTE_FIND_MAXIMUM";
    }
    kernel kernel = k.compile(context, options);

    // setup index buffer
    scalar<uint_> index(context);
    kernel.set_arg(index_arg_index, index.get_buffer());

    // setup count
    size_t count = iterator_range_size(first, last);
    kernel.set_arg(size_arg_index, static_cast<uint_>(count));

    // run kernel
    queue.enqueue_task(kernel);

    // read index and return iterator
    return first + static_cast<difference_type>(index.read(queue));
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_FIND_EXTREMA_HPP

/* serial_find_extrema.hpp
p9rPKNhjx+iU+xULt5hGhfeBU6ZR52ExTB2r2lPuWzwYrg+U8vI/91u61kXAN5wQbuNJaX3VObL22Dlwiv2MNln1YOJ9dK4Uw1I9OL7fgnkXnRhfsU1W/T15H52TKo+TtiueE8Mo1jfts8g2/7L5Vy5dvtJZ3K7yv+Sk7Y51J2xPKY7j241UlrbXnvz54sl6vF5NuF0nRbHNK6WjYcL91mnHtaX4TL87KT3FerfuWH5O2l4skeJ2pffkeIp1Z10pHfYJt5+cXu/E+ym9xeOs9M597X462U2mi4+l6XiaF11ltZauzYvOKqXpNduL1+XSNudrthUze+y6e82xuC//+CfnX2pbuvzG9mWudiNuXQdP2kf9nVKfTuEf367+Tmn7Z177efV3SvXvhM9fapt/7Cq1qGn+J15Vl6+fNNF+xcp6vI8w8T7FCnu8jThFfCrT42GdYr9i2R4bO0y8j8pYx/eGCdKkK/qxOvmLY+G0XGprLaVl6bH25zXbixV/efuNrqXXdy67YW0xzbpGT7Cfdll2rP5OsM+qlaXdiuel6sYE+61e4dCOxf1Uz0/er9iAHtvvWL/+1fsVy+h4G/CabWtPkT/TL1+738n5K3/tPqfIX/Vr9ztF/mon2E/5036Kd/D4fldyJs/7uHW+DrWujwrv1Pvp+qhjfor9VL2O97sm2E8VaNWxvvsE+xjnls7Rk7frKlzs46i8VI9ftY9rg9OIR23FI8fCWXxCPVYfmJ/4CdtVV5Y5nUsdy1zLXtWfnmC/0nE+lp6T9yFL7SuLd3AXrNG771H8fctH9A7zl7T2ynqtAf603tmttQzPXKV3metzB75v/J6X0dpW3zT+fXiH3sV8tt4Fbn/DK783dxvbL3qn3lk+Re9yv1Pv4taaTRvX6p347yh75fe+F7T2zXlaO0drEkx1TzL+nTUZ6f6T8Xv3Ub0L+93G9lvOKjPSGdO71Xdp7aZZxv4Lp1NWxXJ5s9a2/YrWpPu88fmzu414z+01/n3PiNY8+qveqW4z/j7tYuP3nDdqjaedxr+XJY14zn3kDcbn1xi/7zus/b+iNfMe0JrwO7UWzceMz0170fg9p8n43IwexXem8Xt6zPi94V6tLf4RrbGyTWvKHZxs5Ouo8jXN2H9qnZH+u0aM7XsWG/FeOM/4/PZarWF0oxHvs+PKT4XKbaMR/rQrtPZE1th++9TJxue+r7WRP2aU/+y5xvYHho3tG240/n3HI8bvO92qf28ywr93tdYsmWPEP+ktxueeelxrjmT1rvhFxv4bpxjbly3Xu8nfZHzuyb9ozatGY797zjHia3+7jofW6J/+bWP7NefquCwytm9VOS20GNvPrNba5g/q3drXaS3ytNY0udrYb1dyklF/R/SufKfK57vG9p0B1dtJRvmce77OhzMnG/tfoDWAdHy2XKx3hH9M6ZxkhLfgbwp3ttZu+aXWOPyb1mK6+Q1G+X/Y+NySMWP/p6+dbJTzU3oX/C1aC+s2rWlYnK8r1ptDOi5ble7Dxu+rtLbOluWTjfI9Y5IRXpPeqf6S1gq5UmvBnKHz8ieqR2e8wSj3z6k+/1hr4q+YbJRvk9ZYvtv497NXa62QD+j4nG/8/Y5KlfPFbzDi+bvWUi3XGleXaE2Da3U+9xrpP39cn0toLZdK4+9TXlb9/pzx+Sf7jXBXfkrpfq/K/RK9S13ny+EnjL/v+oTe/T7N+Ny+zToO3zDCvSKofP5W5R0x9pvforUUfVp76G5j/6e1RsKGzxj7P5rQWm2Tje1zn9BaJKcb8W+cbfxeV2v8/aJ9RvgL32uU10G1R+OLdF506t30U4y/P/Vj4/eTZtX387WWyhuNf99x0SQ=
*/
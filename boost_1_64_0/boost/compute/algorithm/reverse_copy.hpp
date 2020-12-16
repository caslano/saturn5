//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REVERSE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_REVERSE_COPY_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class OutputIterator>
struct reverse_copy_kernel : public meta_kernel
{
    reverse_copy_kernel(Iterator first, Iterator last, OutputIterator result)
        : meta_kernel("reverse_copy")
    {
        // store size of the range
        m_size = detail::iterator_range_size(first, last);
        add_set_arg<const cl_uint>("size", static_cast<const cl_uint>(m_size));

        *this <<
            decl<cl_uint>("i") << " = get_global_id(0);\n" <<
            decl<cl_uint>("j") << " = size - get_global_id(0) - 1;\n" <<
            result[var<cl_uint>("j")] << "=" << first[var<cl_uint>("i")] << ";\n";
    }

    void exec(command_queue &queue)
    {
        exec_1d(queue, 0, m_size);
    }

    size_t m_size;
};

} // end detail namespace

/// Copies the elements in the range [\p first, \p last) in reversed
/// order to the range beginning at \p result.
///
/// Space complexity: \Omega(1)
///
/// \see reverse()
template<class InputIterator, class OutputIterator>
inline OutputIterator
reverse_copy(InputIterator first,
             InputIterator last,
             OutputIterator result,
             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<OutputIterator>::difference_type difference_type;

    difference_type count = std::distance(first, last);

    detail::reverse_copy_kernel<InputIterator, OutputIterator>
        kernel(first, last, result);

    // run kernel
    kernel.exec(queue);

    // return iterator to the end of result
    return result + count;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REVERSE_COPY_HPP

/* reverse_copy.hpp
SSLNMRIEQRAEQcST+Pj/Ytv63+T/N2XAj+XfU+99fPieY86Z5wP01vfoOZZbbF+igwV9iZbEARFx3SpgHUjD/8HjEu/d8APm9xzjPSKWW+y47rFjuhMEQRAEQRAE8Rt7VwLeRBGFJz1TmtIGS6kVERGxoGiKgAWhrVoUtNaoKKhoGpItjcQ0JhsV79t64433feun3+d9o+LxKd6oeF+oeOOFqEX95+XtdhOyTRHqOf/H4+9s3sy8OTbZ2Xkzo6CwdtFL4/8Y7UW3Fsb/Q4TLvXEd5h0/xJQV5lx96VPVwCDolEKn4SPWSZ2OpjQa8HlHa4HISUnD2x6S5YxnP1NAvmc43yPMeWsMWQGw/AxSDdkLeYjj5fxoh88X84fimrmbXyvvyod86tzTaP5YM4zwRQ0rAGP+uYjSGcrzv0a6RVn39R/C8/rTaK7ULo9x7mJKT4gZdclwOYcncbiKwye5k+GRHPbV0doD87zFp7keXoIUQRZC6qDTSPpOH/cE36y4WQVUhlr7Mpi+BRsJWQZMF1v3QeS54BYqn3GVbDLXVXhyBWEdSB6VFzbhXUnTCak2xfyRWRpts2jYlt1vwuq7cDvnczHECTkfcn25EEHKZ7KRT3onyJqHcabiECo/x0INBLXUcl6Sxytp0DDyQhF4Juql+kQqp13+kw5ZjTbIZAP7d/BnUb+cxUffwqeJiM5xveCj3CmfxwVQIXLdd6Le5sF2mf7HZCvKQO1qpBmS5eS6Lk3unVEgCAdA+kBmQoIo6+EnkZ9IwB/VycBELKZFdJhC3wCwxfS3iaZ8K1jvtZMpjb35XjPSLLH4RUw5wD+LvDegsy2V7UyOUwEdGAlsn4gE5K02KaLH5lBak5HW9aS3FYcd4l2EDT+gXCqT1ZtBUPotlvRNP45Mfi7Qnd6lm+LHASPaw94A5bsz7DifdHajdm/I4qvhNf16Vq2zCvrcuDfNeqE2bzF9PCxl4jSnm3EylWOcm9oAn2v8/XMlh9s4vJjDsxG29otlTkE4kO/BEPeLvI6UfhGNaQeF2hNxo2P0qF+UUhoa9wsjzWK7fkHl7086LVn7xRYdqf3iAAo7u+0X0a70s/aLti5d237RBDsGks4046xYoFUmEjfqoVK2H+lM7VHfacnSd1ps+k60m77TlqXvoJ1S+s7wjtS+09Jh9J2enUlbdL28ftKe+199SeU7Ez6fv6EYOfruiepM2mxn0n4ne60A+FlhNKSSn48miCQOFeLoIoH/8M8NPgZcBT4DXA0+EzySwzK9eZBGTu8lTq8McppIYgGn9wR4APgp8CCwAzf/CHAOeCw4F7w9OA88FZwPbhEoC3h/cB+wDi4GHwl2gc+XeYFvBrvB8+U9BV4IrnAk7fMIfq4Ar8P25UKGiiTWxXRGHrgK3Be8Xk4y3tGQIMe7mOOVQHSO9wDSd4IfBFeAH3Yky/Uzl+sXLtevXK5OKheA9PeT5Qe3SVvAMVlu8CmyfDnJcrnYjnsh1cZvsCNpRznkFpFEnSPZTvXgDcDbgDcBHw7eEnwEuB58JHgX8FHgfcHHgWeBjwcfCD4RLMvcAe4Anwo+E3w6+ELwXPC14LPAD4HPAb8FPg/8K/h88ErwRWC0mbiY698r+PcafADXYyGkUSSxOapa1usYsGyfrbi/1YI3BY8He2T/BM8Eb8/9bjokj783DuR0nZAmkcQU6BWDd+V+vDtY6uzJ6U/n9Pfm9GeAQ+DZYJw3RvN1CwowPwdxFrpoDm9Rpjk8B/z/8Ln0/Vsxns5pSvH/M+b24P9nO7+3BJ/ZzvFhftCL9CeAg2Bjzk8vtPcDTD/v+fiC4qxnPl+C9IwznuAjmHLO0yLIvfjcOO8=
*/
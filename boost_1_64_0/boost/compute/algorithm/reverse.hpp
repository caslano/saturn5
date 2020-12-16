//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REVERSE_HPP
#define BOOST_COMPUTE_ALGORITHM_REVERSE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator>
struct reverse_kernel : public meta_kernel
{
    reverse_kernel(Iterator first, Iterator last)
        : meta_kernel("reverse")
    {
        typedef typename std::iterator_traits<Iterator>::value_type value_type;

        // store size of the range
        m_size = detail::iterator_range_size(first, last);
        add_set_arg<const cl_uint>("size", static_cast<const cl_uint>(m_size));

        *this <<
            decl<cl_uint>("i") << " = get_global_id(0);\n" <<
            decl<cl_uint>("j") << " = size - get_global_id(0) - 1;\n" <<
            decl<value_type>("tmp") << "=" << first[var<cl_uint>("i")] << ";\n" <<
            first[var<cl_uint>("i")] << "=" << first[var<cl_uint>("j")] << ";\n" <<
            first[var<cl_uint>("j")] << "= tmp;\n";
    }

    void exec(command_queue &queue)
    {
        exec_1d(queue, 0, m_size / 2);
    }

    size_t m_size;
};

} // end detail namespace

/// Reverses the elements in the range [\p first, \p last).
///
/// Space complexity: \Omega(1)
///
/// \see reverse_copy()
template<class Iterator>
inline void reverse(Iterator first,
                    Iterator last,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    size_t count = detail::iterator_range_size(first, last);
    if(count < 2){
        return;
    }

    detail::reverse_kernel<Iterator> kernel(first, last);

    kernel.exec(queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REVERSE_HPP

/* reverse.hpp
e27He71ox7bIdnBffR0Sbh6p+5zt+Ree+P1JEwp2PH7ksDbrAS2xfeCefdfe+8CxfOkc7gN/dMquxVMWLbuourI9LzPL/ljsOYKe5wJi+9J9eX9bf97uajyyr3+y/aHjt7zz3S7GxvL0Vy/Yr3q/O5dumb1s1aL7V71ZFmsOIvacgsR1b2ob9vXmtsOWVBx+w9jx47/dGWtuIvYcxFJeT2nqVRvcF3WtOb857+CNw3b/HHtuBTeXzw+4f+3P5sOaYQ/CuucHYDiPnhfYiDQxNyDmBaLmBP7gfEAn6omeE8DMRY/zArHnBCLnA5JRPno+IBVp0XMCGUgrhBEEQRAEQRAEEV//H3/D/a9Ww/3/PpH763v0/0934iw1V1UlX6Xu+wOsUE+0Mtdct944tzvUEjQDP2OlWdHqAuWVdR6vu9yHP7yBjlpJ8Uve7CwmNUiiIC8WKm6X6jNz9M6WN2RniVb7vONy0vUCquL6XTVcL69Wo/vqVH3B9yAOsKbiWHhpEnzqoxvcTs2pNvrYJOHjbxRzDUcycRQ+/tsXc1/c4UBtdYpHa3S4aiRXrcMly7UeSa+3r/XrYJ4ivKgboeWLXA0oOwTpW410/csF0/DVhjolYv29AraO+47Nxx3sbnTcc96Y+wJjv7nx4UsY283Tx60aeuDKG/usYe+fPfj1MXU/4PsS9+rpL4xc2HnQqcq21de/WTb3w8uvwjvDefoju3YOb196RO2SicWj5jkWn4+5C2g0w996kHwugiAIgiAIgiCIfZJE2Fkm+/+umlpVq01Hyn/S9/d5VFdET6N9//FRvn+68P1bhe9/BiyRH8X6fpPw/YPVYYT6Wn8IprnUzAx+brlYnGdlRPj1N97L134LPp037AT71oqVfZqalo5oNtev74RPn5RAfj1BEARBEARBEMS/mURYpcn+f3WdU3HzCABOzVXz1+cBntzn5wEiexw9H7Dq8sj5gCliPmB1Au8eromjmA/o3BqcD4is1YFX2Xu9Dr8ciF7bf4377gnWq299asplRx1jn5M/qCphmblzANPh/1fQHABBEARBEARBEMS/lnh8/79arXH63fDe05H4N8T/q8/o3suvCWf6cNG3wbCTEAsg7WIR/+/U4unBxtn079fzGH1dExmuTW1wSWiA7C+SXLKCEH18T/1pCUbZ/jyuH6R4mT778TKqhvB7HrVGUqYpTp/UXeYEXiaJn88IqyMFZbdzPZuMIW7QhJqerzCUL4lrTRZaJ0zS89uD8wCQEiV5mTOMMnxMz7LilDVkML7/f2TM/f+4LuL2oe+I2xfVd3F9PI7oJ67v2U/E/ePt287LR/SFl52Oa2g3ru3ZbsxdhPZDtCUyzmwx/1EMm4hyhT3fLzwXPtn/B+9BsI6R4jyBnc/PD9zrmOahbBnPmy/un1FXEr9/Fl421DA7pnXE/TPyzeYaAf7KRxvfwcGbNsWponk8VmMR8lbxvDZ2gHguDpvE36Lhn4uXR+pvrsRJqC9X87wpPN9A1l3vzKoqVdKC+WoTUJrnK+H6R4XlK5OVWU5vnS4fem4cPG8u2hOZFz+E+t3E8wwLlVnBz/uFnrVG8ayxvTxrybGfJX59cOznhT9rqbhu4dcjxj00D9YCm8bjUJzx4o6bvpl4wR0zLhxnWfj0Skvv41CYFTMyVnyKoTwuQ3cMhlX63BqOiIPA4x924HwrrD0TaZYBLA2mxzuYPqYv24oPjB3nZTANthimx224DUc9ZsNzOIbHbXgb5104bsaxoTt+A24GyuE4FMeTYUYshwr8HB7P4XKcL4WJuA5R8RxCMRx4XMdW5HsdtkLEb/gaP2/KRhkcRSzHUMyGwYl7xmzIQVo=
*/
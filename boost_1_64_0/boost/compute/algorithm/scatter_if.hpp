//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Pola <jakub.pola@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SCATTER_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_SCATTER_IF_HPP

#include <boost/static_assert.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class MapIterator, class StencilIterator, class OutputIterator, class Predicate>
class scatter_if_kernel : meta_kernel
{
public:
    scatter_if_kernel() : meta_kernel("scatter_if")
    {}

    void set_range(InputIterator first,
                   InputIterator last,
                   MapIterator map,
                   StencilIterator stencil,
                   OutputIterator result,
                   Predicate predicate)
    {
        m_count = iterator_range_size(first, last);
        m_input_offset = first.get_index();
        m_output_offset = result.get_index();

        m_input_offset_arg = add_arg<uint_>("input_offset");
        m_output_offset_arg = add_arg<uint_>("output_offset");

        *this <<
        "const uint i = get_global_id(0);\n" <<
        "uint i1 = " << map[expr<uint_>("i")] <<
        " + output_offset;\n" <<
        "uint i2 = i + input_offset;\n" <<
        if_(predicate(stencil[expr<uint_>("i")])) << "\n" <<
            result[expr<uint_>("i1")] << "=" <<
            first[expr<uint_>("i2")] << ";\n";
    }

    event exec(command_queue &queue)
    {
        if(m_count == 0) {
            return event();
        }

        set_arg(m_input_offset_arg, uint_(m_input_offset));
        set_arg(m_output_offset_arg, uint_(m_output_offset));

        return exec_1d(queue, 0, m_count);
    }

private:
    size_t m_count;
    size_t m_input_offset;
    size_t m_input_offset_arg;
    size_t m_output_offset;
    size_t m_output_offset_arg;
};

} // end detail namespace

/// Copies the elements from the range [\p first, \p last) to the range
/// beginning at \p result using the output indices from the range beginning
/// at \p map if stencil is resolved to true. By default the predicate is
/// an identity
///
/// Space complexity: \Omega(1)
template<class InputIterator, class MapIterator, class StencilIterator, class OutputIterator,
         class Predicate>
inline void scatter_if(InputIterator first,
                       InputIterator last,
                       MapIterator map,
                       StencilIterator stencil,
                       OutputIterator result,
                       Predicate predicate,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<MapIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<StencilIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    detail::scatter_if_kernel<InputIterator, MapIterator, StencilIterator, OutputIterator, Predicate> kernel;

    kernel.set_range(first, last, map, stencil, result, predicate);
    kernel.exec(queue);
}

template<class InputIterator, class MapIterator, class StencilIterator, class OutputIterator>
inline void scatter_if(InputIterator first,
                       InputIterator last,
                       MapIterator map,
                       StencilIterator stencil,
                       OutputIterator result,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<MapIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<StencilIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<StencilIterator>::value_type T;

    scatter_if(first, last, map, stencil, result, identity<T>(), queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SCATTER_IF_HPP

/* scatter_if.hpp
MWKwzxfVY2NHD6+WHwyvS+4nUOdeSj4vUfapMdLtY/rNX0ZhF8q6s/sGhMOw5wPY58rtRz7zvoEy/kH+cEKjOJOhc7WMg5LkiGZ3FXQ2EkAOtjfQAokYOoov0N4+O9SlfzHpO7vzSZpMeyuwT9JS8oeJihzkYdTTolxBGMQR1ud6un2VetIia1pP0ub7Kd0yrjcjnz5UTy+ijvRco54G9KgevEjjHkpjwJ+qB2NvizvzBKGII0i9L6G32FoPsXbdr5tV4Eu2nrBtz7cobj6X1Ugrl/RLyqR+vC3UqrOPlfF5UTflGEzl6MflQJ4oB+VJ12QkpItrlC6Vbzcu34R8XgvA32XFkOdRviUd1j008KUWaz+YDgRFKcOhwJzx4wPtkdbQrERMo8vCck7HErTTxxBaK2Nvb4pP9C0FgjDFaBjID7BDnEx2wME76ItqsqnlsSCC/Be/oz4UOsA/S/PN9Mc1AXCdcrwNLG0QO8jPn+9kfj6F0vmRemVrKBbXjQxIb1e53kbqIdSPwvDYpPAw3A85lrhhvyWq0f8MXbLhU9IL6QJIpgU9+ny0KBSbZko/a7+t4vb+jvptaj1wu3NfQNnT/Izn8XqIzUUSIyErkM6MZH2H4mhnXYvI7+bwHNmjQ0GfJQcq+/Ju6n8Gl6Mq2U5ARPe1af4g7g9/MBjT4nHzfkiQbjmHHcIvw6tR/uWrlD/Vf3QZl7WP6LqXf0WcecmyNuvbJWIxlHWqNjPrPWb9brgGmUuMg+Qxd9bh+snWe8cfwK9jTDNP1Q23B2ab9Qfobajs1tBMLWatv4e5/8rvvx9gv468lsrvv6IS+v4zfE8/92RfkyZt3pFt9hYJwmi2eQu2+csUmw03Zn+rrsWsO/cEBEC/XbCnEml9JG1ylaff+2RjP1zLZRu/hHy1mrYuZFv7s61lbKvnlEy2ztRa22NaurFGPX3Tw7y357ybuLNUc94bcd5NGfOWf+ttMXRvY+WdUfZvke93kO9XM/+n+2Qu+9HZ8udVS0Z7/Pgn8p5QIgh+/l2YLIB6zElkzFs7JKDRWU3oxGF0l259jDmNDUy/9wcovGV3PsYcZ6DpY3wvhWu6XX9yN+lMpLDXzLfK8HvH33+wdx2wcRRRdF1iG2JIHIIxIUAIzUACxhhEdQzGIQEnGDCEEjCHbx0fnO+OuzVO6CWCAAEBogQIVYjeBBGiCSJ6E72EHlFDL0IQOm/+vVnvXe5sA7sHiHnR6GfOM/P+/J3dnZn9f9fTB6vfN/lOKdfC67+utwZqav36+yvzHsY57Imyta6uRRKX0sbYsRmNGfXk/VPeenVZ9fbX91KeOz/UFc4Xegx+V8e7WNrx2IixT21uW9l2kL+L7jOkzaz+8l1er0s/pf2MMbeYY66O430zvsur5sxcY643ln1Nknhd2utHpJ+Qfh7iuNfXm6ZVs+ZC1KF9CDok8V8sbtzj9iu4fxsifyP5rRH9c6AypGak32DLRAZ/BquDIjKmP1RjjOssecsZx/QoS9cfr20k12JrS5RHKh6Cn/0Yjq0P5bh6OTKP4bG8c76LtIqS1P+ZfPrHY/0rwdTg/ZB2UGoUrwPvSf5J627oMCa9pgDS65EweGTWos4zzjMa56vyM6wS/FP3sFLY+wOk99Q9bO2D5Le7kV+KJGuN8pjcx1Tyjq+SLdOpFGmQdYjMNTcX3mTe2DPAjT27CWUZb9hg0fZtA9h+Om1fuZoluJhj93yk4SoWZH6G7RGPGI/1QUkuvjs601Of9NyO8SETZA3iYFpvO545CdvaGGVUHj06S+WHg69YrlvjOBYx5wQw5+zwtMHr8GfSxpnMF1mzpY1h1hh3Ls1pNCeLlmfOvok=
*/
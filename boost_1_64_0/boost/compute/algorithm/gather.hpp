//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_GATHER_HPP
#define BOOST_COMPUTE_ALGORITHM_GATHER_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class MapIterator, class OutputIterator>
class gather_kernel : public meta_kernel
{
public:
    gather_kernel() : meta_kernel("gather")
    {}

    void set_range(MapIterator first,
                   MapIterator last,
                   InputIterator input,
                   OutputIterator result)
    {
        m_count = iterator_range_size(first, last);

        *this <<
            "const uint i = get_global_id(0);\n" <<
            result[expr<uint_>("i")] << "=" << 
                input[first[expr<uint_>("i")]] << ";\n";
    }

    event exec(command_queue &queue)
    {
        if(m_count == 0) {
            return event();
        }

        return exec_1d(queue, 0, m_count);
    }

private:
    size_t m_count;
};

} // end detail namespace

/// Copies the elements using the indices from the range [\p first, \p last)
/// to the range beginning at \p result using the input values from the range
/// beginning at \p input.
///
/// Space complexity: \Omega(1)
///
/// \see scatter()
template<class InputIterator, class MapIterator, class OutputIterator>
inline void gather(MapIterator first,
                   MapIterator last,
                   InputIterator input,
                   OutputIterator result,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<MapIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    detail::gather_kernel<InputIterator, MapIterator, OutputIterator> kernel;
    
    kernel.set_range(first, last, input, result);
    kernel.exec(queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_GATHER_HPP

/* gather.hpp
q5fQmY0sF/sjwdsAc+GZ02hQAWO4mdsMk3gVZFw7QPvqW903Rtex9+SW4j0qVu9dX0mvPnEjrHO0d0f/zFH9gM9jmur+lZZcKz9Yudh4bgX0T793Jo1zgTlTebPY5/uFlzujfdcXPtHMi1eKvYW+P/FW+KjMZ3mShfnpWTC3zMy/75B4K0xfyNd07OeW3HrtCz7/bkYnwgNiXxr43mXGz0fFf4oVz30J13e0XTGYc793DfDphox61OhLKTHeBHkPk3qKd+jA0nJr2BTjLmVztNXkWO/FIzQTlTD9Pff00SD3dIanraIgPfjzg7al8VSv+G3iL91MYsk4ZYc5Zx93vrvJdczZoKSNm0nbUaa4GiXLlEKZCkOUKfQzUb+f+JWpyJRJYtn6Cn6GMhWJm0nbUaa2upBdhxauS4OpSZxQZeKQ5tzQZdJ41eVZsVL8PRHSZ2VNz544x8zdTTgp+2o73IzsSdO0D5kwP6rsvvF6pbg58xCv4/Vq9dPrOupldjz/+O0X7ogZRL0Uh6oXtLKMyw1ZLxqvk9TLIvGXCCgFmpCXmaX1EhBusV+4rGl2uNSAcAv9wuVmz5jBB0UdZ5zhfu0XTj+TBHnOahzV7ZfnHyc3P9iz1YSX+YFf+HxWExXoNbr6xekqcUr3PD7bvV0kbo56NM/ixeLnrLu6+ixeKH7O+sJP6uHXxs/UkdHPlKd+WhfE0fHSuJsyS1vqrW3pmCqRq6oFi8IMqck/j4VoSyQyC0V/Vuh+pnGrSp1fK/6eSFoNpp85w8034UyVaHtyhisw4UxxtD2ZcD/pvl0rbo78mvs2X/ycedT7pvXsyJdzfK5rzjI0586nUs/RIet55vic7Amh6ljjJUqdTBJ/Ipgsax0HhMsx4TT7po5NOO1XGk5aktZvQJgCE0aKG7SvEt701YXmGcJ4dm1Wyb4aOrxHaWWwfkr4n95PJ4mbo+7M/c5RP1Nf2t8STH8zdaTzZtMOTL1o/9R+bcov7l2NuymntJn+2mYi6ulaOz950XDaTGqINoOZMHN6doEmFaLtaHxSbeisZ2ds04ZM+B9Vz020nrWcQa7jnG+vCVLmEZQ5w1lmeY2Ugus4lG3K4aePuYz5zjZ5dOrt2ai6T1vpONkMk0Se8r15Gtp7QPr4GVnj0GuV7i00f/qdGH9JzuSJOOaspA2SZ97UzDPW4a/vBPZ70WTb3/E9V84MKsW5SOSH8kl+zByZPOAmeQg4F4nrBuhKT20Q/Byh4sdKf44QYc96jtCOx36ec4RIQOeM9vPtHsp6zJtXuU/ada0q5l4YPdcarrKf33i9Rz6/auc857+a5NFXx6StfUHr3KFv7HiQ/Hb1BN7tzG967xH9eg3vk5LeZ3Bqev8hUo8VoyXv6X7frDVeZT//8cZ/oPGvJu/X4Vx7JeZJchKl34RK22cqSv1zbXWLNm5yPYfuwAP6Erhcy7dYv3UleMsog4NDvhREXkRz0/ANrABZjPnevFL8I4yM5z6xuwNlLyJD6Cd+U8ose0nb7ZS9TBN7VanPE9TlV41U9tJ6SEnZi4apnaDf4qp1LSl70TDdE3yyl9a27KUU3z187eBiyVctaau1XWcfIxICZCrVVM5CnXnczHv5WrFTT2YuqbrAg+joa0z+ju326Tczw7cs6R/cLy1laF+520Fl7ORf48brd7USuuWMv6mbMug543qBes60rFwjoGypQfQBNiW+tedsZZMvQjKfuVfyPoGlFKzYsMtHfGf+R5Yi/745xb2SV00zIL+ng+S3u6evnSO/M/U9sUPJe0HcH68Tr4Opa2c+DzcN3maSz5pPUUkYss0QN3SbEf8fr4+wLG1mbhB9fw2In3H2ss0=
*/
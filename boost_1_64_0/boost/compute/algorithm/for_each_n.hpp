//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FOR_EACH_N_HPP
#define BOOST_COMPUTE_ALGORITHM_FOR_EACH_N_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/for_each.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Calls \p function on each element in the range [\p first, \p first
/// \c + \p count).
///
/// Space complexity: \Omega(1)
///
/// \see for_each()
template<class InputIterator, class Size, class UnaryFunction>
inline UnaryFunction for_each_n(InputIterator first,
                                Size count,
                                UnaryFunction function,
                                command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::for_each(first, first + count, function, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FOR_EACH_N_HPP

/* for_each_n.hpp
xnh1qUB9//gKY/SjGN0oJd4RjC6UVIzRexJc34mZow8KrdNE5sWdXiqft5b/lf+V/5X/lf+V/5X/lf+V/5X//a/+/SLv/7lZnHGckz3e8wHgZ3j/r6xKZcMstgdMyxw3PTPdc4W8TN7M6+Ifif/nOzz+qOpSL9+7/yo/3YEZbvv87uqYqzD1PGk/6H33H5Wanjqw3+Xec3jGZWb69qRvrGHhL6Uy+zXvkjgDrGb+58GIWx3Rv/EVcRfhtoYrR0UNNmui16qOC1+YIziuE10ZPRxr1bku5XKuwU7B8wG5RjWjA+EpsUc60jxDuPWeNGs0NGmONHo/Rki66WtxrOioL3ONOyTNuFLv96F+WIcm9eM4O2S36gJciKmta06ac23roeD1nT4uJ3scGfE7tyvP72w3jddE91Oio03sl1t9HfouJk7Py9U16SZOgtFFkSD2DGugnrGeSZsYSz7vlvPpa0dW4eCrGpFZHHtVye2ru89UP2O6JOhsB50lve6sV410nBW4mvTuKcOeKdVLlFdy/buUx3F+bqHqCvxQEzqOaUW9Fger1wl5+XMsk3/8M2eQrrZZjUNKdjufMX2C2Udh/Et9xly6tAWuoW7Rpn1Iuo5yDFK9e//Q8/Q/wLSlHIeKg5SD87AytRytpV+gPMAuh8Y53+xj/kHs+4OeG8y1NHwDozftE7G/a1XReqD2zV687g/LXj/y3oZ9nW51x0PcC63uuGXrGX3vSUPNMnuuV0iYetjdps8+JG5hVgva3yLu5YGKfO+jRsKSaHwNPIewwRpoQ6nalH/cDTxlaFez5DnG4ySdRnzHjGYcxM3kaQdrvMZLjldwbb8yyR4vvkdquJelftbW0H2BRnep41xW3eOh56ZKPFufQA+xN5Uxb1kFvtlRlk0EjGo6zYw9A3Xs8YVZQ5jNnjAxV5gwgwPC7CPMFtEPZI+dQzWMfz+7H7cHMKHHNbuNVJK8JkhbjnadtS1LHdHOZP+rOfPNFfrc5yT9jJar68WvhBcSP3pH8LYsWjVCt2eNl2D2FSaJ/Ua+ibqD6joYaOI0MHvYzxP7YNe1VljIM+lbS5jhrurEW6DPsskmrbpB97k/In7P65hhj4kNdU9lvvh/QW+MZLd/CmvuKlu3kqu6usdyu/g/h4/bGoGZZA327ztmH2KuhGPnC20ilbGiWWXVGRTWIrLFOc627675j9V+MQq792z75JD6gi7cYZ9rH6/X3Mg1t3n6ZuE+rhcRY/cL2cxldAoelbiLKUcY6xtT1R0tm+K+jP7Ylf4YLv0kkTQ3YLYTMapC4etmv5df+26o10+s4ivzwmpa6JA6klJd1NFO7/7UhmL3XX87+UE6gkmz2pGbCkHroAZsvNPUgclDPhd8SOrg3cjmnv94OnIGm5SlLX45GOnPsYWnAvuzx/hkJ8W4PYzZUcr++nvJe/Vzyll0r2eJ/joaOva/O/R/abk1Lm0PtyzZD5qy0+xDdjyvTmsfn4CpoRzHj2M7g/VxtkA6nrvSR8x+3r9LnBQtqy+NumpHk94u7PyndYc+gFKdZ+aYU6Q752WmHHujHDIw3BkrqLuMXUHKwQGJpFViz5+eCaxxOrKbubJpQ7eJW7Tl6UNnqLNFUdo+KnWMqoBd2lboezqg5LxIrukYb/fpOfvDNFIqpk9N3EOVwXOkZp7lv8c6f2rWnPTsTNPeNC5nKAaEGc97DgF1nPWFG1Yi3MQctBGYvmjCSd318o7xkgndw238Y23//KxceTCYPP0gYWLluZzo1Mur8V2B7yjm/MXnxH+QPtOdOno17jnndfE6r9P91abO6jrOZ3TWk56pqn6OujG68SgvflIfco1E203r4NzvFys=
*/
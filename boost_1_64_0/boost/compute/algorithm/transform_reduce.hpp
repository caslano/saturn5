//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_TRANSFORM_REDUCE_HPP
#define BOOST_COMPUTE_ALGORITHM_TRANSFORM_REDUCE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/reduce.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/iterator/zip_iterator.hpp>
#include <boost/compute/functional/detail/unpack.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Transforms each value in the range [\p first, \p last) with the unary
/// \p transform_function and then reduces each transformed value with
/// \p reduce_function.
///
/// For example, to calculate the sum of the absolute values of a vector
/// of integers:
///
/// \snippet test/test_transform_reduce.cpp sum_abs_int
///
/// Space complexity on GPUs: \Omega(n)<br>
/// Space complexity on CPUs: \Omega(1)
///
/// \see reduce(), inner_product()
template<class InputIterator,
         class OutputIterator,
         class UnaryTransformFunction,
         class BinaryReduceFunction>
inline void transform_reduce(InputIterator first,
                             InputIterator last,
                             OutputIterator result,
                             UnaryTransformFunction transform_function,
                             BinaryReduceFunction reduce_function,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    ::boost::compute::reduce(
        ::boost::compute::make_transform_iterator(first, transform_function),
        ::boost::compute::make_transform_iterator(last, transform_function),
        result,
        reduce_function,
        queue
    );
}

/// \overload
template<class InputIterator1,
         class InputIterator2,
         class OutputIterator,
         class BinaryTransformFunction,
         class BinaryReduceFunction>
inline void transform_reduce(InputIterator1 first1,
                             InputIterator1 last1,
                             InputIterator2 first2,
                             OutputIterator result,
                             BinaryTransformFunction transform_function,
                             BinaryReduceFunction reduce_function,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<InputIterator1>::difference_type difference_type;

    difference_type n = std::distance(first1, last1);

    ::boost::compute::transform_reduce(
        ::boost::compute::make_zip_iterator(
            boost::make_tuple(first1, first2)
        ),
        ::boost::compute::make_zip_iterator(
            boost::make_tuple(last1, first2 + n)
        ),
        result,
        detail::unpack(transform_function),
        reduce_function,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_TRANSFORM_REDUCE_HPP

/* transform_reduce.hpp
xiluW8adJNaROU8z1m2B+/1f5VeZvnOra9Z4vVqo/D4ne1UxTjCXpHo+j3arpP12XiffUd/acnY/lF1V5rJWuTR2539i/ej7mer4gVp9ITaX97xd6vkznIP90tTt38Oag+Vc77ixeJjrndF6wzlD52/lx7n/Xr1swpx/Ub3LOAeZYj2pwVXVUcSd/2k99/eNN5VfUe7V7DWsjocZI08N3Re43u3GkqVZ7x3ydTGKy86dCZYWK8i45Y1lumezSsZiOdnLaorhzllrGUtbzVzqK4b7bN9Edl1YR4qx9MLM5X5j0bXs0cPGAs3IHpFdKff7H8ZSCrnzP2OpTqsexiK/so7equ1+ajVAMR5nzoOMhXNRl6Faz92TRxlLtGfc57Wee+8yUevVYNyp6nkO9/u/ym8rNU0obn5qsEC+rt4lyuVn1rtcWj3AuG+oby7G2+qb6+UHt2aIdazRep9Tlw3GQjnItsjXvSfepjnIzv22U7VN5TzvU23fsbZDWm8ptT8m1pLXsNPSYDBjZCjn/szvO8VoT61+FnO/OfmbseB77vxP9U7MCXZN+rlZ+0/rDeV62WraHLi/M8xtLFaSOec3ltqMrJCxjKepSzFj6c73TrEljFFOvg+48z9jKXNYW1VjwaJBsLBy+SQXWD1jaT/Rt7FqS+M8t5DdJsZtpVzc918eUgz3rNJevrWygz1mLDKJe7Wz1lvDersbS7pz/qeMhdxZQX/5tmSPnjEWb8xZGyJNUxljpPLLyjkYayxzCllcutzP9V4wlniO+c1Ufoe4F+ao3t7u/E92zdnzxaqjCnV5TTHmM+eVqsP9rflbmj/3/vx9zYE7Q/lYvu75dL3sosxvs+K6z/FbVcdwarDDWOAJzstezcGHzDldmia43lHZHWC9p6Sze/Y5p15WY84X5DufPfpJrBNj/Gos6nT5XXtmMWP8rfxcLjdUW2HqnDVsuZxkbbmMZf7MOchnLFiDdgWNRe4kK2osUY61lTKWUYs6h4ylu9ruMhZ+hKyKsdQEY9TUelloV9dYrKc7/zMWbUXWXHV86b7/ZyzQnVo9aCzknjvbKe5UXiM6aL0V7v//Ux0F6NvNWEoL9qiX4mZlHf3EWjC//xlLe5fzHFO97p3mCMWdyb6NUc7uHjVBPXf31SnGkuPJZkj7ecxvtjQdwfVeVtz1vJe9opzdOfoyaeA+w67QDLk63tR69Rj3PbFSnIOPNEMB+q6Tfifo+6nqaEG7NOni5u9L+XZkfnukcwv3+x+qzZ0ZHVF+bWh3Ur513f//J+2rcA6+1Z7JQ61+lC712fNLmsmb1PmK6jjOnP+Sndu//0qD8fTNUku/I8tZy2ksM0atbjOWeo0zHjQW/pHrFTGWUZealjQWfJa5lNV67vm0orH4GdrdYyzhdK5hLN19jq9jLOB61FC+7p7STDHc59/7pIGbtQekgTsLamss5s5UH5XvIWrQUXZXA2BPar37GCOqnFtxNvoaS3bgek/XUn85G88aS8nFeocrxiU+0zwn1phajRdzf7812VjE9Wi6WBvOwUvG0kbxujZPvXTPa4uk/VTWu1R1DKKmr0urhDv/03oXafeudBnKuKnSL072ieL+xx5tklbud68/N/b4LM7GdvlWZj92K7/CnJcDspvN9b6SVkWY8wkxd/84q9pOcB99I02nMMYPmqvfuN5FsdOcg8vaC1+48z+xqdTgH9WRkzkHatt6l5hfDmPJOfTNaywznXuwgLHIM5yhwsbSHmZ+JYyldssLVsZY4B2uV8FYLMhrYmVj4Z3sR3Vj6dnd+Z98j3KGGijuV2RNVVt35nKvfBtS+9bGUi5wD7YxFhzGa2xE+T3qzv+kQRo=
*/
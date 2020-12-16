//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_TRANSFORM_HPP
#define BOOST_COMPUTE_ALGORITHM_TRANSFORM_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/iterator/zip_iterator.hpp>
#include <boost/compute/functional/detail/unpack.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Transforms the elements in the range [\p first, \p last) using
/// operator \p op and stores the results in the range beginning at
/// \p result.
///
/// For example, to calculate the absolute value for each element in a vector:
///
/// \snippet test/test_transform.cpp transform_abs
///
/// Space complexity: \Omega(1)
///
/// \see copy()
template<class InputIterator, class OutputIterator, class UnaryOperator>
inline OutputIterator transform(InputIterator first,
                                InputIterator last,
                                OutputIterator result,
                                UnaryOperator op,
                                command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    return copy(
               ::boost::compute::make_transform_iterator(first, op),
               ::boost::compute::make_transform_iterator(last, op),
               result,
               queue
           );
}

/// \overload
template<class InputIterator1,
         class InputIterator2,
         class OutputIterator,
         class BinaryOperator>
inline OutputIterator transform(InputIterator1 first1,
                                InputIterator1 last1,
                                InputIterator2 first2,
                                OutputIterator result,
                                BinaryOperator op,
                                command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<InputIterator1>::difference_type difference_type;

    difference_type n = std::distance(first1, last1);

    return transform(
               ::boost::compute::make_zip_iterator(boost::make_tuple(first1, first2)),
               ::boost::compute::make_zip_iterator(boost::make_tuple(last1, first2 + n)),
               result,
               detail::unpack(op),
               queue
           );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_TRANSFORM_HPP

/* transform.hpp
rEz2heKu4l7YZSzFvQvcL01nMJfD6q/7jeHj0m8J7c6I1afdedVWnDp/r/X8//+nPeiuk5liTThDV6VBQep8XTnX5UzeFHNnadkr2tz/j7nkMZa+gnFvN5Y8y9ruMBbtSU2LG0s7wvVKGwsfoqbljSXaMEYlY5l12ctqxjI+ZoxayqUHWX3l0pK6NJFdxP3+r7HgWvrer1w68przsFh3skeMpb5G/R43FulGuy7KOerO/4zFtrFHvaWzey85QPnVowaDVId7xzzUWMpuslHSIMj7zPOKMZlzMFE5u+emqcbicff9P7FszCVhLOTOoBao5/Wo6RLNVUv6LlfcatTlDdkN4XpvK66b8Q80Qy2Y8xrV5v6PmQ3Sfgx12SLfuoy7TVq57x3ulPYvUKt96tvfWcEOaU7d5+Rj6sftZKel1SOsI0Ma3MN6v9NcbeU14mfVdht7+ZtqO83a/pBdVdZ2TfOymev9J52Hs95sd1nf+nOv5jYWcp8l8xtLKcR9VMhYdAnrLWYs8yhj3GksvIpzVc5YMM55udtY+kPcC1WNRV5ivWFjsW7MpZ5iNGLOjY2lHqJ+LZTzUmrVSmwD7R4ylnSfu9tLq2yM8Zh0acf+dlYuM1hvd2m6iVo9ZSxeinb9lXMj1vaM7JzOQ5Tzf9RqpFh11jZWcVfQLi5NF7u//5X2M8lmGssYzVzmGEtUd3//K61ijLtYGrxSFOw11bGS9a5Uve6z/VuaoTaM+77mJS9jfCy7Upyh9ZqNLlxvs7GGLpetsivOXHZIv9703av+Hma96dI0ybhHjQX+os6npEuI16tz8nXXqwvSoBXr/Um17XC//6H5q871fpddGbK/1cvy3NM35PsV91HWuwOBZ5ZRl1zG4nW5F/KJVWdtBY2lZ1KXosaiVVlHKdlVYb0hsdHU/i5jSXcuVcVYakV3/mcssZ511DUW/o8xGsluM+2aK24/5tzSWHAEe/6gWGfGbWcs9ok7/zOWUpLad5LdZGrfTfrVI+tlLNN9LutnLOS//2csYzjnICadf80NNkK+sxhjjOrYwpwnKL9aXG/KLf2o/Qxp5X5nYLaxiDuve1k9GsxevmIs0J+aLlMu82m3Quu1CYK9Ka2qcf7eUy8fZS4faV7cZ5x1yrkM7T5VfiXI0oylNeA8fyn93nR//yudt9D3oOIOpaZHFMPVcVJ2pdjLr7XeIPb8W+Wygn37UWw47S6pb+Op3xVpupO9/EtztZVx/1UuLm6WSqZ9nOvlNJbehP29zVjm51wvaCzlXtoVMRZ3vy9ZUixO37Jiu5lzRWMZI5nLPcaiP5HVUM4XuM/rKJffyRoaS3P3lGbGUoexl/ep3obM7wFjiTKcv7bKL855edRY4Ffm19FYbBbXe1JxF1D7qLHkP5y1vlrvSWr6tHxb5AB7VnZnaTfcWCiFmj4nXWqz3vHqZTn6TjYWPMXZna46SvN68JJyLkPfedI5m/v9X2kaY71LlcsE+r6uGI0496tVR1navauelydLVdxy1PkT6fIN+7FJMe51//+f6vggP9h2zZrLb7dyOcX1Dki/0u78T7UN47X4hNgZanpWOh91//+fYtzJ9X5QvaOY80XNn9u/l7WPrnEm/5RdVs7VP+rHMV6vApUtRiPOeA5j4Y6sI6+x0FhqUMBY8hJZYdm5z4gljKW45/syxjIXc69WMBZ0vpWNpbvn9uryLcJ5rm0supu9bKD1snO9psplLzW4V2wu62gtXVwubRT3JvsWUYy3qdUT0qWr+/6f8pvJ/vZUjPaM0UfrPUe7gdLA5TLYWIZjw6R9Fu7V0WJf8nowTv11cScpP7feNNXrZuhF2V0im6v8HqYuC2U3kD0=
*/
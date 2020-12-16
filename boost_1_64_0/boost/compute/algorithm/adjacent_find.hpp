//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ADJACENT_FIND_HPP
#define BOOST_COMPUTE_ALGORITHM_ADJACENT_FIND_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Compare>
inline InputIterator
serial_adjacent_find(InputIterator first,
                     InputIterator last,
                     Compare compare,
                     command_queue &queue)
{
    if(first == last){
        return last;
    }

    const context &context = queue.get_context();

    detail::scalar<uint_> output(context);

    detail::meta_kernel k("serial_adjacent_find");

    size_t size_arg = k.add_arg<const uint_>("size");
    size_t output_arg = k.add_arg<uint_ *>(memory_object::global_memory, "output");

    k << k.decl<uint_>("result") << " = size;\n"
      << "for(uint i = 0; i < size - 1; i++){\n"
      << "    if(" << compare(first[k.expr<uint_>("i")],
                              first[k.expr<uint_>("i+1")]) << "){\n"
      << "        result = i;\n"
      << "        break;\n"
      << "    }\n"
      << "}\n"
      << "*output = result;\n";

    k.set_arg<const uint_>(
        size_arg, static_cast<uint_>(detail::iterator_range_size(first, last))
    );
    k.set_arg(output_arg, output.get_buffer());

    k.exec_1d(queue, 0, 1, 1);

    return first + output.read(queue);
}

template<class InputIterator, class Compare>
inline InputIterator
adjacent_find_with_atomics(InputIterator first,
                           InputIterator last,
                           Compare compare,
                           command_queue &queue)
{
    if(first == last){
        return last;
    }

    const context &context = queue.get_context();
    size_t count = detail::iterator_range_size(first, last);

    // initialize output to the last index
    detail::scalar<uint_> output(context);
    output.write(static_cast<uint_>(count), queue);

    detail::meta_kernel k("adjacent_find_with_atomics");

    size_t output_arg = k.add_arg<uint_ *>(memory_object::global_memory, "output");

    k << "const uint i = get_global_id(0);\n"
      << "if(" << compare(first[k.expr<uint_>("i")],
                          first[k.expr<uint_>("i+1")]) << "){\n"
      << "    atomic_min(output, i);\n"
      << "}\n";

    k.set_arg(output_arg, output.get_buffer());

    k.exec_1d(queue, 0, count - 1, 1);

    return first + output.read(queue);
}

} // end detail namespace

/// Searches the range [\p first, \p last) for two identical adjacent
/// elements and returns an iterator pointing to the first.
///
/// \param first first element in the range to search
/// \param last last element in the range to search
/// \param compare binary comparison function
/// \param queue command queue to perform the operation
///
/// \return \c InputIteratorm to the first element which compares equal
///         to the following element. If none are equal, returns \c last.
///
/// Space complexity: \Omega(1)
///
/// \see find(), adjacent_difference()
template<class InputIterator, class Compare>
inline InputIterator
adjacent_find(InputIterator first,
              InputIterator last,
              Compare compare,
              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    size_t count = detail::iterator_range_size(first, last);
    if(count < 32){
        return detail::serial_adjacent_find(first, last, compare, queue);
    }
    else {
        return detail::adjacent_find_with_atomics(first, last, compare, queue);
    }
}

/// \overload
template<class InputIterator>
inline InputIterator
adjacent_find(InputIterator first,
              InputIterator last,
              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    using ::boost::compute::lambda::_1;
    using ::boost::compute::lambda::_2;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::adjacent_find(
            first, last, _1 == _2, queue
        );
    }
    else {
        return ::boost::compute::adjacent_find(
            first, last, all(_1 == _2), queue
        );
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ADJACENT_FIND_HPP

/* adjacent_find.hpp
RvZGj7FXZPa4buWLZiRtL1XfKfT7Tdrhjfq3xY1OgC54teoOrmnGeqH+739P38C3elltDU1A9xeNaLuV8rto7+N9tj4+av5H2LyAlq9vGHs9Ryf7+ZbPO4g9L8B5PcfvyXyB4+3uXnnZn16ecM5XNw1+7I7P/cHJ/t9pnUqn+QWO8wVkXoC+w8g73BOwDr9O/97iH0vSv2/WtQ7pU3TMScZk5Fwifrimcy8Pvhfug9003FPD4+B9MJjOsZOk8xVN54CmQ5h0CGs6BzWdwZbq/mGeppOAz9F07kCuPbwT9oN3hcXbdpJ4D2q8hzTel8LiHdF4yZHxdA1HPz8Nz4AL1e69OKjbhRM13hn6t98NIf1MOBT2gMNgbzgSDoQj4AgNnydhXUPQ6BZFjyrp9sJ3dukeicjlwvPgYFgAR8EJcCo8H66CU+A6WAQ3w83wBjgD3gRnwtv0+D54EfwSnAMf0eNPwkvgM/BT8Igefx4uhL/V8CtwMXxNw2/CCvg2XAb9N7Mc9oI+2BeuhGNgPTwPXgYnwtVwFlwD58L18FNwI/TBq6HuBaq6LnR6Uv72vUD/QT1lwbfgQHgCDoVttZz+rWtRvg198F24Cr4HV8P34R3wHXgXdGk5ueHXYAJ8HLaBh2EyPKLpkz9uWnVJqqd6Qt9fpe/WeSYev4zuzbkRdoXXwxx4FcyDm+BIPT4WXgNnw2vhUngdXAk/AzfALXCzyOseoUFdD5gk+bDvEbrdFbjuzbAv3AEHwFvgULgTjoa7YaDdq/4ATo7R7vtregP0+T4b9oGD4CA4EJ6r4UIJh+bTLNJ8lkq69vk0K3XeUl3YvJ4RcDUsgKtgEWyC0+DlcJ6e13lE+o3Msy/p2+cRlWr6i7Xcy+AQWAEvgcvgAg2XaHixhpdr2AeXw3VwBbwS1sDr4VJ4J6yEe/X4GzAfX6DlmaP5aiN9mH4Ha791lvabfeGZGtb64PvNuT66a3300ProqfXRS+sjG56r4UINa770W4Y6jZGvz2i+tkAP3Apz4A0mX/pODFfHyFdHlU+DY2A6nAw9sAh2hfNhZ7hEw29An3nPQ1b7x7PxZdo/btP5UDfBPvBmrccdcA68VevpdrgTPgv3wJ/Ar8CfwkfgL+Dj8JfwCfgc/BZ8Hj4Dfw2fhb+BP4F/hS/AV+Gf4N/h+/AYTCFv34S94CF4FvwWzIXfhgPgYTgUPgVHwqfhWPg9WAgPwIvgQbgSfhU2wkfgdvgovBk+BnfDr8M74RfhY/Ah+CR8GD4F74J/hS/DY/D38F0Nt3Hz/MMkeAxu8l9/eYp1BH8Mn1qdYg3GF+N9+C34WHvHPRMxJ2tfdcppzctqzpysiD3cbPOwhvdNZv5V7LlX8/GHq1NOOe/qZHOuikj/ZHOuXiT9NitSrFz8dLwPvwV/AH8EfwyfWpNi5eGL8GX4Dfhd+Efxz+FP1MTnacVd3MVd3MVd3MVd3MXdB3cfhv0//5T4sKNsDft/v41/vccye53luc13rtUTJsHXGegs7iNjFrIxE6MVKyQDnA/Z+ElmdNwiKN/P7Dt2mYT/EbWmn45ZqHyO2berQcKviny9yNcuCd8zb6Wc/4sZoyK+GdMqQN5CnnE4Y3uzXs7/0dj5vYfMArUx+qyuv3e0WXZ+ien9c6L28Vc7OSkDHVeMXm+vGNbLMbkX2x5z09WO/1LVo8zFv0W5P5ETUe6NNf6Sl/ssNOViyl3ls53KWc/31HqL3ovwb3J+YOT+bHKPf5BzI824da2/3JpRZlpGXEHvPXYZmfFZrmsbw5jvbvneWS3dI6ulYxittRfWf3vPq5aO/bx+q6zx1JQ+I/l4m+sWrDzjK3Xl6TOdxk4++ns=
*/
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
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
*/
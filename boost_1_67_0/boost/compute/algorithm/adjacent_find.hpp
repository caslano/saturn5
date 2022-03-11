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
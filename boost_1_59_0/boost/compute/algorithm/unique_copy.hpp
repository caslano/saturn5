//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_UNIQUE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_UNIQUE_COPY_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/algorithm/gather.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class BinaryPredicate>
inline OutputIterator serial_unique_copy(InputIterator first,
                                         InputIterator last,
                                         OutputIterator result,
                                         BinaryPredicate op,
                                         command_queue &queue)
{
    if(first == last){
        return result;
    }

    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    const context &context = queue.get_context();

    size_t count = detail::iterator_range_size(first, last);

    detail::meta_kernel k("serial_unique_copy");

    vector<uint_> unique_count_vector(1, context);

    size_t size_arg = k.add_arg<const uint_>("size");
    size_t unique_count_arg = k.add_arg<uint_ *>(memory_object::global_memory, "unique_count");

    k << k.decl<uint_>("index") << " = 0;\n"
      << k.decl<value_type>("current") << " = " << first[k.var<uint_>("0")] << ";\n"
      << result[k.var<uint_>("0")] << " = current;\n"
      << "for(uint i = 1; i < size; i++){\n"
      << "    " << k.decl<value_type>("next") << " = " << first[k.var<uint_>("i")] << ";\n"
      << "    if(!" << op(k.var<value_type>("current"), k.var<value_type>("next")) << "){\n"
      << "        " << result[k.var<uint_>("++index")] << " = next;\n"
      << "        " << "current = next;\n"
      << "    }\n"
      << "}\n"
      << "*unique_count = index + 1;\n";

    k.set_arg<const uint_>(size_arg, count);
    k.set_arg(unique_count_arg, unique_count_vector.get_buffer());

    k.exec_1d(queue, 0, 1, 1);

    uint_ unique_count;
    copy_n(unique_count_vector.begin(), 1, &unique_count, queue);

    return result + unique_count;
}

template<class InputIterator, class OutputIterator, class BinaryPredicate>
inline OutputIterator unique_copy(InputIterator first,
                                  InputIterator last,
                                  OutputIterator result,
                                  BinaryPredicate op,
                                  command_queue &queue)
{
    if(first == last){
        return result;
    }

    const context &context = queue.get_context();
    size_t count = detail::iterator_range_size(first, last);

    // flags marking unique elements
    vector<uint_> flags(count, context);

    // find each unique element and mark it with a one
    transform(
        first, last - 1, first + 1, flags.begin() + 1, not2(op), queue
    );

    // first element is always unique
    fill_n(flags.begin(), 1, 1, queue);

    // storage for desination indices
    vector<uint_> indices(count, context);

    // copy indices for each unique element
    vector<uint_>::iterator last_index = detail::copy_index_if(
        flags.begin(), flags.end(), indices.begin(), lambda::_1 == 1, queue
    );

    // copy unique values from input to output using the computed indices
    gather(indices.begin(), last_index, first, result, queue);

    // return an iterator to the end of the unique output range
    return result + std::distance(indices.begin(), last_index);
}

} // end detail namespace

/// Makes a copy of the range [first, last) and removes all consecutive
/// duplicate elements (determined by \p op) from the copy. If \p op is not
/// provided, the equality operator is used.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param result first element in the result range
/// \param op binary operator used to check for uniqueness
/// \param queue command queue to perform the operation
///
/// \return \c OutputIterator to the end of the result range
///
/// Space complexity: \Omega(4n)
///
/// \see unique()
template<class InputIterator, class OutputIterator, class BinaryPredicate>
inline OutputIterator unique_copy(InputIterator first,
                                  InputIterator last,
                                  OutputIterator result,
                                  BinaryPredicate op,
                                  command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    size_t count = detail::iterator_range_size(first, last);
    if(count < 32){
        return detail::serial_unique_copy(first, last, result, op, queue);
    }
    else {
        return detail::unique_copy(first, last, result, op, queue);
    }
}

/// \overload
template<class InputIterator, class OutputIterator>
inline OutputIterator unique_copy(InputIterator first,
                                  InputIterator last,
                                  OutputIterator result,
                                  command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::unique_copy(
        first, last, result, ::boost::compute::equal_to<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_UNIQUE_COPY_HPP

/* unique_copy.hpp
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
*/
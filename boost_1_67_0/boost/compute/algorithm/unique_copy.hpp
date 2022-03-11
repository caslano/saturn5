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
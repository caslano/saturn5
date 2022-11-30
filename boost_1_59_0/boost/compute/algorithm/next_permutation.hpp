//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_NEXT_PERMUTATION_HPP
#define BOOST_COMPUTE_ALGORITHM_NEXT_PERMUTATION_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Helper function for next_permutation
///
/// To find rightmost element which is smaller
/// than its next element
///
template<class InputIterator>
inline InputIterator next_permutation_helper(InputIterator first,
                                             InputIterator last,
                                             command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0 || count == 1){
        return last;
    }
    count = count - 1;
    const context &context = queue.get_context();

    detail::meta_kernel k("next_permutation");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    atomic_max<int_> atomic_max_int;

    k << k.decl<const int_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("cur_value") << "="
      <<     first[k.var<const int_>("i")] << ";\n"
      << k.decl<const value_type>("next_value") << "="
      <<     first[k.expr<const int_>("i+1")] << ";\n"
      << "if(cur_value < next_value){\n"
      << "    " << atomic_max_int(k.var<int_ *>("index"), k.var<int_>("i")) << ";\n"
      << "}\n";

    kernel kernel = k.compile(context);

    scalar<int_> index(context);
    kernel.set_arg(index_arg, index.get_buffer());

    index.write(static_cast<int_>(-1), queue);

    queue.enqueue_1d_range_kernel(kernel, 0, count, 0);

    int result = static_cast<int>(index.read(queue));
    if(result == -1) return last;
    else return first + result;
}

///
/// \brief Helper function for next_permutation
///
/// To find the smallest element to the right of the element found above
/// that is greater than it
///
template<class InputIterator, class ValueType>
inline InputIterator np_ceiling(InputIterator first,
                                InputIterator last,
                                ValueType value,
                                command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return last;
    }
    const context &context = queue.get_context();

    detail::meta_kernel k("np_ceiling");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    size_t value_arg = k.add_arg<value_type>(memory_object::private_memory, "value");
    atomic_max<int_> atomic_max_int;

    k << k.decl<const int_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("cur_value") << "="
      <<     first[k.var<const int_>("i")] << ";\n"
      << "if(cur_value <= " << first[k.expr<int_>("*index")]
      << "      && cur_value > value){\n"
      << "    " << atomic_max_int(k.var<int_ *>("index"), k.var<int_>("i")) << ";\n"
      << "}\n";

    kernel kernel = k.compile(context);

    scalar<int_> index(context);
    kernel.set_arg(index_arg, index.get_buffer());

    index.write(static_cast<int_>(0), queue);

    kernel.set_arg(value_arg, value);

    queue.enqueue_1d_range_kernel(kernel, 0, count, 0);

    int result = static_cast<int>(index.read(queue));
    return first + result;
}

} // end detail namespace

///
/// \brief Permutation generating algorithm
///
/// Transforms the range [first, last) into the next permutation from the
/// set of all permutations arranged in lexicographic order
/// \return Boolean value signifying if the last permutation was crossed
/// and the range was reset
///
/// \param first Iterator pointing to start of range
/// \param last Iterator pointing to end of range
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(1)
template<class InputIterator>
inline bool next_permutation(InputIterator first,
                             InputIterator last,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    if(first == last) return false;

    InputIterator first_element =
        detail::next_permutation_helper(first, last, queue);

    if(first_element == last)
    {
        reverse(first, last, queue);
        return false;
    }

    value_type first_value = first_element.read(queue);

    InputIterator ceiling_element =
        detail::np_ceiling(first_element + 1, last, first_value, queue);

    value_type ceiling_value = ceiling_element.read(queue);

    first_element.write(ceiling_value, queue);
    ceiling_element.write(first_value, queue);

    reverse(first_element + 1, last, queue);

    return true;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_NEXT_PERMUTATION_HPP

/* next_permutation.hpp
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
*/
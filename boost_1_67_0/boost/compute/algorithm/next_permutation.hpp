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
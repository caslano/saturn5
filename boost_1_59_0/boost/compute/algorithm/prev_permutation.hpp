//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PREV_PERMUTATION_HPP
#define BOOST_COMPUTE_ALGORITHM_PREV_PERMUTATION_HPP

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
/// \brief Helper function for prev_permutation
///
/// To find rightmost element which is greater
/// than its next element
///
template<class InputIterator>
inline InputIterator prev_permutation_helper(InputIterator first,
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

    detail::meta_kernel k("prev_permutation");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    atomic_max<int_> atomic_max_int;

    k << k.decl<const int_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("cur_value") << "="
      <<     first[k.var<const int_>("i")] << ";\n"
      << k.decl<const value_type>("next_value") << "="
      <<     first[k.expr<const int_>("i+1")] << ";\n"
      << "if(cur_value > next_value){\n"
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
/// \brief Helper function for prev_permutation
///
/// To find the largest element to the right of the element found above
/// that is smaller than it
///
template<class InputIterator, class ValueType>
inline InputIterator pp_floor(InputIterator first,
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

    detail::meta_kernel k("pp_floor");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    size_t value_arg = k.add_arg<value_type>(memory_object::private_memory, "value");
    atomic_max<int_> atomic_max_int;

    k << k.decl<const int_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("cur_value") << "="
      <<     first[k.var<const int_>("i")] << ";\n"
      << "if(cur_value >= " << first[k.expr<int_>("*index")]
      << "      && cur_value < value){\n"
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
/// Transforms the range [first, last) into the previous permutation from
/// the set of all permutations arranged in lexicographic order
/// \return Boolean value signifying if the first permutation was crossed
/// and the range was reset
///
/// \param first Iterator pointing to start of range
/// \param last Iterator pointing to end of range
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(1)
template<class InputIterator>
inline bool prev_permutation(InputIterator first,
                             InputIterator last,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    if(first == last) return false;

    InputIterator first_element =
        detail::prev_permutation_helper(first, last, queue);

    if(first_element == last)
    {
        reverse(first, last, queue);
        return false;
    }

    value_type first_value = first_element.read(queue);

    InputIterator ceiling_element =
        detail::pp_floor(first_element + 1, last, first_value, queue);

    value_type ceiling_value = ceiling_element.read(queue);

    first_element.write(ceiling_value, queue);
    ceiling_element.write(first_value, queue);

    reverse(first_element + 1, last, queue);

    return true;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PREV_PERMUTATION_HPP

/* prev_permutation.hpp
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
*/
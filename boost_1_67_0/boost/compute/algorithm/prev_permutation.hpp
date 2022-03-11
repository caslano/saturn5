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
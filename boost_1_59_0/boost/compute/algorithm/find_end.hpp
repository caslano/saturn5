//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_END_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_END_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/detail/search_all.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Helper function for find_end
///
/// Basically a copy of find_if which returns last occurrence
/// instead of first occurrence
///
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_end_helper(InputIterator first,
                                     InputIterator last,
                                     UnaryPredicate predicate,
                                     command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return last;
    }

    const context &context = queue.get_context();

    detail::meta_kernel k("find_end");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    atomic_max<int_> atomic_max_int;

    k << k.decl<const int_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("value") << "="
      <<     first[k.var<const int_>("i")] << ";\n"
      << "if(" << predicate(k.var<const value_type>("value")) << "){\n"
      << "    " << atomic_max_int(k.var<int_ *>("index"), k.var<int_>("i")) << ";\n"
      << "}\n";

    kernel kernel = k.compile(context);

    scalar<int_> index(context);
    kernel.set_arg(index_arg, index.get_buffer());

    index.write(static_cast<int_>(-1), queue);

    queue.enqueue_1d_range_kernel(kernel, 0, count, 0);

    int result = static_cast<int>(index.read(queue));

    if(result == -1){
        return last;
    }
    else {
        return first + static_cast<difference_type>(result);
    }
}

} // end detail namespace

///
/// \brief Substring matching algorithm
///
/// Searches for the last match of the pattern [p_first, p_last)
/// in text [t_first, t_last).
/// \return Iterator pointing to beginning of last occurence
///
/// \param t_first Iterator pointing to start of text
/// \param t_last Iterator pointing to end of text
/// \param p_first Iterator pointing to start of pattern
/// \param p_last Iterator pointing to end of pattern
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(n)
///
template<class TextIterator, class PatternIterator>
inline TextIterator find_end(TextIterator t_first,
                             TextIterator t_last,
                             PatternIterator p_first,
                             PatternIterator p_last,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<TextIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<PatternIterator>::value);

    const context &context = queue.get_context();

    // there is no need to check if pattern starts at last n - 1 indices
    vector<uint_> matching_indices(
        detail::iterator_range_size(t_first, t_last)
            + 1 - detail::iterator_range_size(p_first, p_last),
        context
    );

    detail::search_kernel<PatternIterator,
                          TextIterator,
                          vector<uint_>::iterator> kernel;

    kernel.set_range(p_first, p_last, t_first, t_last, matching_indices.begin());
    kernel.exec(queue);

    using boost::compute::_1;

    vector<uint_>::iterator index =
        detail::find_end_helper(
            matching_indices.begin(),
            matching_indices.end(),
            _1 == 1,
            queue
        );

    // pattern was not found
    if(index == matching_indices.end())
        return t_last;

    return t_first + detail::iterator_range_size(matching_indices.begin(), index);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_END_HPP

/* find_end.hpp
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
*/
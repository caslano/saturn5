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
5v+yxIC9WWHOdopoLDvdPe+DPuk0gJVRR47W6sDt7LiHdq4B/H8CrdcWiuZEwdlRv3UosoyS3u4dQTTWh8nQ0wyUqPLFt9Khr9lMbo8aFp93vWNLognK6FuNi+9DwVBmiJ4x5WHVTU5s1bDeBLVla4vvXicQ17yhmxn+IHq0A8P3cCLzqha4h83nyux0oMESwvE952RdyTUqBxz8iVmAzcHExsNPD7a23wzlUkNdueBtu6LorLwpNvpPLoPo7yi+j67j+3j25EVp2nyxNC+MJsXp7S1E99MRTrnryVdTGnwkIICvNynyUWLw7f5/UEsDBAoAAAAIAC1nSlJgyueGxgYAAL4QAAAtAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL2N1cmxfZ2xvYmFsX3NzbHNldC4zVVQFAAG2SCRgrVdtU9tGEP6uX7HjfihkhAzJJGmatFMDbuPiyB5kkjLDjEeWTta18p2rO0E8Tf97nz1JWIBJ+FBngm3dvt2zu8+ug6sePfvfXl7A5uibr7n7P8cL763StNR/isTuVpjPv1D9D4pXeH+Cqz5ttb7M9+lJWl9oz2nNG1/v+PN8/gR3Vxwk/+mz8tWcP+JJrdnon+j1ppTL3NLeyT4dvXnzAx3Q88Pnhz6dxkqK
*/
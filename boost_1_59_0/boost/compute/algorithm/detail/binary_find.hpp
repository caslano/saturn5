//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_BINARY_FIND_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_BINARY_FIND_HPP

#include <boost/compute/functional.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/parameter_cache.hpp>

namespace boost {
namespace compute {
namespace detail{

///
/// \brief Binary find kernel class
///
/// Subclass of meta_kernel to perform single step in binary find.
///
template<class InputIterator, class UnaryPredicate>
class binary_find_kernel : public meta_kernel
{
public:
    binary_find_kernel(InputIterator first,
                       InputIterator last,
                       UnaryPredicate predicate)
        : meta_kernel("binary_find")
    {
        typedef typename std::iterator_traits<InputIterator>::value_type value_type;

        m_index_arg = add_arg<uint_ *>(memory_object::global_memory, "index");
        m_block_arg = add_arg<uint_>("block");

        atomic_min<uint_> atomic_min_uint;

        *this <<
            "uint i = get_global_id(0) * block;\n" <<
            decl<value_type>("value") << "=" << first[var<uint_>("i")] << ";\n" <<
            "if(" << predicate(var<value_type>("value")) << ") {\n" <<
                atomic_min_uint(var<uint_ *>("index"), var<uint_>("i")) << ";\n" <<
            "}\n";
    }

    size_t m_index_arg;
    size_t m_block_arg;
};

///
/// \brief Binary find algorithm
///
/// Finds the end of true values in the partitioned range [first, last).
/// \return Iterator pointing to end of true values
///
/// \param first Iterator pointing to start of range
/// \param last Iterator pointing to end of range
/// \param predicate Predicate according to which the range is partitioned
/// \param queue Queue on which to execute
///
template<class InputIterator, class UnaryPredicate>
inline InputIterator binary_find(InputIterator first,
                                 InputIterator last,
                                 UnaryPredicate predicate,
                                 command_queue &queue = system::default_queue())
{
    const device &device = queue.get_device();

    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    const std::string cache_key = "__boost_binary_find";

    size_t find_if_limit = 128;
    size_t threads = parameters->get(cache_key, "tpb", 128);
    size_t count = iterator_range_size(first, last);

    InputIterator search_first = first;
    InputIterator search_last = last;

    scalar<uint_> index(queue.get_context());

    // construct and compile binary_find kernel
    binary_find_kernel<InputIterator, UnaryPredicate>
        binary_find_kernel(search_first, search_last, predicate);
    ::boost::compute::kernel kernel = binary_find_kernel.compile(queue.get_context());

    // set buffer for index
    kernel.set_arg(binary_find_kernel.m_index_arg, index.get_buffer());

    while(count > find_if_limit) {
        index.write(static_cast<uint_>(count), queue);

        // set block and run binary_find kernel
        uint_ block = static_cast<uint_>((count - 1)/(threads - 1));
        kernel.set_arg(binary_find_kernel.m_block_arg, block);
        queue.enqueue_1d_range_kernel(kernel, 0, threads, 0);

        size_t i = index.read(queue);

        if(i == count) {
            search_first = search_last - ((count - 1)%(threads - 1));
            break;
        } else {
            search_last = search_first + i;
            search_first = search_last - ((count - 1)/(threads - 1));
        }

        // Make sure that first and last stay within the input range
        search_last = (std::min)(search_last, last);
        search_last = (std::max)(search_last, first);

        search_first = (std::max)(search_first, first);
        search_first = (std::min)(search_first, last);

        count = iterator_range_size(search_first, search_last);
    }

    return find_if(search_first, search_last, predicate, queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_BINARY_FIND_HPP

/* binary_find.hpp
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
*/
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
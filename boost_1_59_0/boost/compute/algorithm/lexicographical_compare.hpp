//---------------------------------------------------------------------------//
// Copyright (c) 2014 Mageswaran.D <mageswaran1989@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/any_of.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/utility/program_cache.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

namespace detail {

const char lexicographical_compare_source[] =
"__kernel void lexicographical_compare(const uint size1,\n"
"                                      const uint size2,\n"
"                                      __global const T1 *range1,\n"
"                                      __global const T2 *range2,\n"
"                                      __global bool *result_buf)\n"
"{\n"
"   const uint i = get_global_id(0);\n"
"   if((i != size1) && (i != size2)){\n"
        //Individual elements are compared and results are stored in parallel.
        //0 is true
"       if(range1[i] < range2[i])\n"
"           result_buf[i] = 0;\n"
"       else\n"
"           result_buf[i] = 1;\n"
"   }\n"
"   else\n"
"       result_buf[i] = !((i == size1) && (i != size2));\n"
"}\n";

template<class InputIterator1, class InputIterator2>
inline bool dispatch_lexicographical_compare(InputIterator1 first1,
                                             InputIterator1 last1,
                                             InputIterator2 first2,
                                             InputIterator2 last2,
                                             command_queue &queue)
{
    const boost::compute::context &context = queue.get_context();

    boost::shared_ptr<program_cache> cache =
        program_cache::get_global_cache(context);

    size_t iterator_size1 = iterator_range_size(first1, last1);
    size_t iterator_size2 = iterator_range_size(first2, last2);
    size_t max_size = (std::max)(iterator_size1, iterator_size2);

    if(max_size == 0){
        return false;
    }

    boost::compute::vector<bool> result_vector(max_size, context);


    typedef typename std::iterator_traits<InputIterator1>::value_type value_type1;
    typedef typename std::iterator_traits<InputIterator2>::value_type value_type2;

    // load (or create) lexicographical compare program
    std::string cache_key =
            std::string("__boost_lexicographical_compare")
            + type_name<value_type1>() + type_name<value_type2>();

    std::stringstream options;
    options << " -DT1=" << type_name<value_type1>();
    options << " -DT2=" << type_name<value_type2>();

    program lexicographical_compare_program = cache->get_or_build(
        cache_key, options.str(), lexicographical_compare_source, context
    );

    kernel lexicographical_compare_kernel(lexicographical_compare_program,
                                          "lexicographical_compare");

    lexicographical_compare_kernel.set_arg<uint_>(0, iterator_size1);
    lexicographical_compare_kernel.set_arg<uint_>(1, iterator_size2);
    lexicographical_compare_kernel.set_arg(2, first1.get_buffer());
    lexicographical_compare_kernel.set_arg(3, first2.get_buffer());
    lexicographical_compare_kernel.set_arg(4, result_vector.get_buffer());

    queue.enqueue_1d_range_kernel(lexicographical_compare_kernel,
                                  0,
                                  max_size,
                                  0);

    return boost::compute::any_of(result_vector.begin(),
                                  result_vector.end(),
                                  _1 == 0,
                                  queue);
}

} // end detail namespace

/// Checks if the first range [first1, last1) is lexicographically
/// less than the second range [first2, last2).
///
/// Space complexity:
/// \Omega(max(distance(\p first1, \p last1), distance(\p first2, \p last2)))
template<class InputIterator1, class InputIterator2>
inline bool lexicographical_compare(InputIterator1 first1,
                                    InputIterator1 last1,
                                    InputIterator2 first2,
                                    InputIterator2 last2,
                                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);

    return detail::dispatch_lexicographical_compare(first1, last1, first2, last2, queue);
}

} // end compute namespace
} // end boost namespac

/* lexicographical_compare.hpp
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
*/
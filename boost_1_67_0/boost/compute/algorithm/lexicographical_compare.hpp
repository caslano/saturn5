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
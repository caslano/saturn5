//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SEARCH_N_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SEARCH_N_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Search kernel class
///
/// Subclass of meta_kernel which is capable of performing search_n
///
template<class TextIterator, class OutputIterator>
class search_n_kernel : public meta_kernel
{
public:
    typedef typename std::iterator_traits<TextIterator>::value_type value_type;

    search_n_kernel() : meta_kernel("search_n")
    {}

    void set_range(TextIterator t_first,
                   TextIterator t_last,
                   value_type value,
                   size_t n,
                   OutputIterator result)
    {
        m_n = n;
        m_n_arg = add_arg<uint_>("n");

        m_value = value;
        m_value_arg = add_arg<value_type>("value");

        m_count = iterator_range_size(t_first, t_last);
        m_count = m_count + 1 - m_n;

        *this <<
            "uint i = get_global_id(0);\n" <<
            "uint i1 = i;\n" <<
            "uint j;\n" <<
            "for(j = 0; j<n; j++,i++)\n" <<
            "{\n" <<
            "   if(value != " << t_first[expr<uint_>("i")] << ")\n" <<
            "       j = n + 1;\n" <<
            "}\n" <<
            "if(j == n)\n" <<
            result[expr<uint_>("i1")] << " = 1;\n" <<
            "else\n" <<
            result[expr<uint_>("i1")] << " = 0;\n";
    }

    event exec(command_queue &queue)
    {
        if(m_count == 0) {
            return event();
        }

        set_arg(m_n_arg, uint_(m_n));
        set_arg(m_value_arg, m_value);

        return exec_1d(queue, 0, m_count);
    }

private:
    size_t m_n;
    size_t m_n_arg;
    size_t m_count;
    value_type m_value;
    size_t m_value_arg;
};

} //end detail namespace

///
/// \brief Substring matching algorithm
///
/// Searches for the first occurrence of n consecutive occurrences of
/// value in text [t_first, t_last).
/// \return Iterator pointing to beginning of first occurrence
///
/// \param t_first Iterator pointing to start of text
/// \param t_last Iterator pointing to end of text
/// \param n Number of times value repeats
/// \param value Value which repeats
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(distance(\p t_first, \p t_last))
template<class TextIterator, class ValueType>
inline TextIterator search_n(TextIterator t_first,
                             TextIterator t_last,
                             size_t n,
                             ValueType value,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<TextIterator>::value);

    // there is no need to check if pattern starts at last n - 1 indices
    vector<uint_> matching_indices(
        detail::iterator_range_size(t_first, t_last) + 1 - n,
        queue.get_context()
    );

    // search_n_kernel puts value 1 at every index in vector where pattern
    // of n values starts at
    detail::search_n_kernel<TextIterator,
                            vector<uint_>::iterator> kernel;

    kernel.set_range(t_first, t_last, value, n, matching_indices.begin());
    kernel.exec(queue);

    vector<uint_>::iterator index = ::boost::compute::find(
        matching_indices.begin(), matching_indices.end(), uint_(1), queue
    );

    // pattern was not found
    if(index == matching_indices.end())
        return t_last;

    return t_first + detail::iterator_range_size(matching_indices.begin(), index);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SEARCH_N_HPP

/* search_n.hpp
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
*/
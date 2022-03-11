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
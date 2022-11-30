//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SEARCH_ALL_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SEARCH_ALL_HPP

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Search kernel class
///
/// Subclass of meta_kernel which is capable of performing pattern matching
///
template<class PatternIterator, class TextIterator, class OutputIterator>
class search_kernel : public meta_kernel
{
public:
    search_kernel() : meta_kernel("search")
    {}

    void set_range(PatternIterator p_first,
                   PatternIterator p_last,
                   TextIterator t_first,
                   TextIterator t_last,
                   OutputIterator result)
    {
        m_p_count = iterator_range_size(p_first, p_last);
        m_p_count_arg = add_arg<uint_>("p_count");

        m_count = iterator_range_size(t_first, t_last);
        m_count = m_count + 1 - m_p_count;

        *this <<
            "uint i = get_global_id(0);\n" <<
            "const uint i1 = i;\n" <<
            "uint j;\n" <<
            "for(j = 0; j<p_count; j++,i++)\n" <<
            "{\n" <<
            "   if(" << p_first[expr<uint_>("j")] << " != " <<
                    t_first[expr<uint_>("i")] << ")\n" <<
            "       j = p_count + 1;\n" <<
            "}\n" <<
            "if(j == p_count)\n" <<
            result[expr<uint_>("i1")] << " = 1;\n" <<
            "else\n" <<
            result[expr<uint_>("i1")] << " = 0;\n";
    }

    event exec(command_queue &queue)
    {
        if(m_count == 0) {
            return event();
        }

        set_arg(m_p_count_arg, uint_(m_p_count));

        return exec_1d(queue, 0, m_count);
    }

private:
    size_t m_p_count;
    size_t m_p_count_arg;
    size_t m_count;
};

} //end detail namespace
} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SEARCH_ALL_HPP

/* search_all.hpp
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
*/
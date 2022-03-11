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
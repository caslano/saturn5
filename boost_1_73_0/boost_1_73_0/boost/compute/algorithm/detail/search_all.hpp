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
n2JEpQoinwk5qXdpcqdyhDboCCAgd0WKZC32GG+73rW8awhq7rt3dm0SCKcmqs75YbM78+bN25kxwV0DTn7Y5QUWDl68QvcX0kX3ndOkUH9hZL7vEIYPUP2Q4x3dXxGqDU9eD2ELXuX1AE3nFdaxLu1zGL4i3J0laf+1rfNdaB9ppfKs/Xsq3xZ8lRpo9lrQOT9/D2/g7PTs1IcrJjkKmBmUSyxWPlzGbuW3lN3fBxo/+oAGmAgOAOcp16BVYjasQKBnwSOUGmNgGmLUUcGX9IFLMClCwgVCbzxZDEZ/+LBJeZTWOFtVgk5VKWJI2RqhwAj5uoLJWWFAJYRA+DHXhjBLw5UMKDyCwSLTNYwlwYRWwNaMC7akcMxAakyuf223o7IQlEk7VpFuRzspgtRkz7JaEJuMbUHlBoyCUqMP1t6HTMU8sXeSiBbzcim4Tv0nWhRQxm1VgEYhajhy5airFBBmtVq+tYSc2HNjb1pJbaNtUpUdGJKsNVBSFpLCkSxkFysS3odSxlg4eyfELkqtspP8hSN74h6DksQKGt0ZDGYNWDLNtQ9fB/Pr8e0cvnan0+5ovoDx79AdLWq8z4PRFdUGp6gF4H1eoCYWBfAsFxzjg+A/sNPn12DPM8xKYXi4YX9jmcNbaHTewUit
*/
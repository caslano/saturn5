//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_COMPACT_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_COMPACT_HPP

#include <iterator>

#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/system.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Compact kernel class
///
/// Subclass of meta_kernel to compact the result of set kernels to
/// get actual sets
///
class compact_kernel : public meta_kernel
{
public:
    unsigned int tile_size;

    compact_kernel() : meta_kernel("compact")
    {
        tile_size = 4;
    }

    template<class InputIterator1, class InputIterator2, class OutputIterator>
    void set_range(InputIterator1 start,
                   InputIterator2 counts_begin,
                   InputIterator2 counts_end,
                   OutputIterator result)
    {
        m_count = iterator_range_size(counts_begin, counts_end) - 1;

        *this <<
            "uint i = get_global_id(0);\n" <<
            "uint count = i*" << tile_size << ";\n" <<
            "for(uint j = " << counts_begin[expr<uint_>("i")] << "; j<" <<
                counts_begin[expr<uint_>("i+1")] << "; j++, count++)\n" <<
            "{\n" <<
                result[expr<uint_>("j")] << " = " << start[expr<uint_>("count")]
                    << ";\n" <<
            "}\n";
    }

    event exec(command_queue &queue)
    {
        if(m_count == 0) {
            return event();
        }

        return exec_1d(queue, 0, m_count);
    }

private:
    size_t m_count;
};

} //end detail namespace
} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_COMPACT_HPP

/* compact.hpp
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
*/
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
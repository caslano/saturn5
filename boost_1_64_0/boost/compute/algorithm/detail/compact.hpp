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
WV1Y2hTf92xhjwTn3TWFZXXz86Mu9mWUdFh9bHnT+3YRfYNz58uw5T0v11xY3ic+5lcIK5wafP8nLPsWz3NH/DjFx/IaYbEFpR12PXqHeb03IvdmgsMykQueUQOF5c7x2G34G9SzhworyPbcj4SrbV7vWOSC58dEYUXv+DydKizjRj/evXB12MftfvzY7nmZA9bQY/MY7yav93H0Bs+KBfS92+t4nlgG8+hl5OZ7XvKI20aPvUncgm8m3oHTCV7ve9j3gO+7mngE31ivg7+pPk83omOH93crMQq//8OPYJ/4OXq/8DH6ir5LPQffEsugDrIXbI6X20/fgIND6Ajy9Hd8q+T9iF0tLHjvKSmscFecw8oISw2+PSovLGWit6WisNx2Xq4afY94W85Cx2bP87nCCoLnQh3k1vm41ROWt8Hb3EhYzjvelkuFFbX24zXDluYeayUsK1jr2sHLOT7/rqZvcK6WQd8bvN7r4KWbl+sJlhJ8/wdX5/p4DEDvVJ+7g4TFnqjgsCH49oCP0Qi4et/LjYGXOzx/E4Sl3+ptmYJvVYP6H7ac7nm+T1j4bzHMFpb2a5LD5mLLCx57DLkZvm+usPxl3r7nsDl4VrwEBzt9jBYhF/79X2HZO33ft9HR02Pvwt9VPr7vY3OS52AtORn03QAvnT0vW8jJnODvf6D3Y8/BLnTk+bm/Gz+C9f4b/Jjs5X7E5hwf8yI4Per1HkQu2GcfRW9QV/6TPAjmb0JH5eQU71tpYQWjfYxOQW6nt+U0YYVBHbMqfZt5vWcKSwm+BTtHWGyK9/c8YZl3evsuRO8E37ehsPRN3uZLTujwc7ApWCPPS7qw/ID7tmDJXu9VwjLmebku2LI6wWHdhOXd5fX2AAt+F+8mYUUx70d//G3i5W7Fln1ebjBYsMYOF5bdO6j/Md6bJRw2Hr1pPm6TGS/YF9+Nb/U8VzOFpc33vuUQ82q+78PoCOqijwrLWub5ewr7qpV22LPkQfC7qn/Ht3u9H69i3yuel9cZb7SP21L0Xu39WIHNgS2rwF7y3H9IXuV4vR/DwVCfa5vBtvq830GutQ7qf9hygeevEO6D+bFHWOqDXu8PzKPqwfd/cDA72WG/wl+mH+8I+Rfs0Y8Ly5nmdZTopPFq+L5JwrIv8HLJwrJO83E7VVj+Ss99FWFp6zwHZwhLec7rqCGsMD+o/wlLv83H9wJhOdV83zRsfsTb11hY6lyfQ5dj33FvS0vkOnqsjbCivZUd1gEd3VMc1hnsdq+jK1h7b3N3YZnBPqw3nAbPvH70fcj7cQu2rPHxvV1Yxp/e5mHIXejn4B3oXettuRMdwXMhW1jsCx+3acRot/d3BvFo5nN3FvwN8X48hI5Rvu987Hvac/Ukfev4vs+QB7d6HS+Sa8E77ELyqklQ/yM3evvceAvfgrr8cvLgfN93JfbV9Xo/wI8n/Hjr0XGVxwrgZbLnbztYts+hz7DleZ8HX2LL9DiH/ZO4lfEx/x5bvvHYT8ToDB/LA3Aa1KAOg030thyD56C2Gd9Z9jX1vJQSlvOk97ecsJQUb3MFYemVPAeVhWWv9zpORy7gIFXYgGnevlrone3lzse+lj5GDcBG+by/WFhasDY1weZR3rcWYIFvrek7Jqj/4cdxj3USlhrE6FrGu9vbd4OwjHZeby9hmcG+ri9+FAT1P7hqE9T/kPu1gsOykHvVczUK+573vo2D02AfMQnfynnsLsar4/NqurDcwV7HA8IKgrr3g4z3kvftEfQGtc0nwDI9f0+jt4TX8QLjBd+qvSIsK9vreE1YUaBjCfYN874tE5a/3o+XD6fbgu//4O90n1cf0Td4l9yE3Eavdxs21/Q=
*/
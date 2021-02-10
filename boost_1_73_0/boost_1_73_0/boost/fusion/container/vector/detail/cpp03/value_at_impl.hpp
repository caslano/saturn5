/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_05052005_0232)
#define FUSION_VALUE_AT_IMPL_05052005_0232

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<typename Sequence::types, N>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
1m0PzPtfv4pau9PHeF/9zESyANNARUXxAzzxw1vQu+bSBtSNHKHDjQ7UjgZcXuhmuGnm4nZgtLNoUlP8G7/b1Qcf/LZIqOR1Qqk177goo1euTi801dNJJZYLOD45CQBF1L+ZtIE/RE355UluobCweoOCRzOOiMBkCyDTLziqjlVP0pT5Jgkk9gRbldqAfddWRfutiyu0P16yw+NeoWMRh67rgDW7xrc4aycGsTRl4wWpgJnaDWgE2E8D0HzopTAiizM+xWa3U5BUVMua+k6BbdMdgZ85Y9RX97lyXtT02O4/fuD9v8qUuKRcgXSkulEiAy25WrdhwwgzjGqUd4CTooNUW5LkXYRhJDp4ykEGE1gK4Mauo8V3BJZ+D9JQlCmQzYOo4ifQEDqYScPiMBr7tRIBT3pX56ddky6gswHOohSDtOCYi4HGRDjJlWSvJFRma8rtdkp8GuR/DgG55wAeGTOZTVXkkNqFnUwH+SCzBNaCUcQSU0S4M6qhwpVVFjmKtBzHMgoxjwVDfED8WV5nHGSjEkxmAe27FihDOnU3NCiUfyCiFG0lXI9kmqN5n+sJkHy7mEGrucQ4V+B2U/SefvmvpVzKZiF0lkTWyTjIk4DX7OI7NihQ1MovtXePT9QATgYdA2h2GTn6Weey
*/